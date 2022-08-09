
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <sys/param.h>
#include "player.h"
#include "item.h"
#include "bresenham.h"
#include "macro.h"
#include "map.h"
#include "screen.h"
#include "disk.h"
#include "stateMap.h"
#include "stateBackpack.h"
#include "stateEquipment.h"
#include "stateExamineMap.h"
#include "stateChooseTarget.h"
#include "stateJournal.h"
#include "stateLevelUp.h"
#include "stateMainMenu.h"
#include "stateConfirmNewGame.h"
#include "stateGameOver.h"
#include "stateEndGame.h"

//declare a player
player_t player;

//set the player state to STATE_MAIN_MENU
void playerInit(void)
{
 //clear the player structure
 memset(&player,0,sizeof(player_t));
 //send the player to the main menu
 playerGotoState(STATE_MAIN_MENU);
}

//deinitialize the player
void playerDeinit(void)
{
 //for now doed nothing, but if we decide to allocate the player dynamically
 //here is the right place do deallocate it
}

//save the player to a file
bool playerSave(FILE* aFile)
{
 size_t written=fwrite(&player,sizeof(player_t),1,aFile);
 if(written==1)
 {
  return true;
 }
 return false;
}

//load the player from a file
bool playerLoad(FILE* aFile)
{
 size_t readed=fread(&player,sizeof(player_t),1,aFile);
 if(readed==1)
 {
  return true;
 }
 return false;
}

//setup the player for a new game
void playerNewGame(void)
{
 //setup the player for a new game
 player.menuSelection=0;
 player.x=0;
 player.y=0;
 player.turn=0;
 player.losLength=8;
 player.maxHitPoints=30;
 player.hitPoints=player.maxHitPoints;
 player.defence=1;
 player.attack=3;
 memset(player.journal,0,sizeof(char)*JOURNAL_LENGTH*JOURNAL_LINE_LENGTH);
 player.journalIndex=0;
 for(int i=0;i<BACKPACK_LENGTH;i++)
 {
  itemInit(&(player.backpack[i]),ITEM_NONE,0,0);
 }
 itemInit(&(player.backpack[0]),ITEM_DAGGER,0,0);
 itemInit(&(player.backpack[1]),ITEM_LEATHER_ARMOR,0,0);
 player.backpackSelected=true;
 player.backpackIndex=0;
 player.backpackStart=0;
 player.nearbyIndex=0;
 player.nearbyStart=0;
 player.examineX=0;
 player.examineY=0;
 player.itemToUse=NULL;
 player.dungeonLevel=0;
 player.level=1;
 for(int i=0;i<EQUIPMENT_MAX;i++)
 {
  itemInit(&(player.equipment[i]),ITEM_NONE,0,0);
 }
 player.equipmentIndex=0;
 player.equipmentStart=0;
 playerLog("Welcome to the dungeon!");
 //generate a new map
 mapGenerate(MAP_CAVE,0);
 //move the player to the map state
 playerGotoState(STATE_MAP);
 //save the game
 diskSaveGame();
}

//move the player to a new state setting/resetting variables used in the landing
//state
void playerGotoState(state_t newState)
{
 switch(newState)
 {
  case STATE_MAX:
  case STATE_MAP:
  case STATE_CONFIRM_NEW_GAME:
  case STATE_GAME_OVER:
  case STATE_END_GAME:
   break;
  case STATE_BACKPACK:
   //reset backpack and nearby selection
   player.backpackIndex=0;
   player.backpackStart=0;
   player.nearbyIndex=0;
   player.nearbyStart=0;
   break;
  case STATE_EQUIPMENT:
   player.equipmentIndex=0;
   player.equipmentStart=0;
   break;
  case STATE_EXAMINE_MAP:
  case STATE_CHOOSE_TARGET:
   //center the selection on the player
   player.examineX=player.x;
   player.examineY=player.y;
   break;
  case STATE_LEVEL_UP:
  case STATE_MAIN_MENU:
   //reset the selection
   player.menuSelection=0;
   break;
  case STATE_JOURNAL:
   //move to the last journal log
   player.journalIndex=JOURNAL_LENGTH-screenHeight+1;
   if(player.journalIndex<0)
   {
    player.journalIndex=0;
   }
   break;
 }
 //go to the new state
 player.state=newState;
}

//call the states update function based on the actual player state
bool playerUpdate(char input)
{
 switch(player.state)
 {
  case STATE_MAX:
   return false;
  case STATE_MAP:
   return stateMapUpdate(input);
  case STATE_BACKPACK:
   return stateBackpackUpdate(input);
  case STATE_EQUIPMENT:
   return stateEquipmentUpdate(input);
  case STATE_EXAMINE_MAP:
   return stateExamineMapUpdate(input);
  case STATE_CHOOSE_TARGET:
   return stateChooseTargetUpdate(input);
  case STATE_MAIN_MENU:
   return stateMainMenuUpdate(input);
  case STATE_CONFIRM_NEW_GAME:
   return stateConfirmNewGameUpdate(input);
  case STATE_JOURNAL:
   return stateJournalUpdate(input);
  case STATE_LEVEL_UP:
   return stateLevelUpUpdate(input);
  case STATE_GAME_OVER:
   return stateGameOverUpdate(input);
  case STATE_END_GAME:
   return stateEndGameUpdate(input);
 }
 return false;
}

//call the states render function based on the actual player state
void playerRender(void)
{
 switch(player.state)
 {
  case STATE_MAX:
   break;
  case STATE_MAP:
   stateMapRender();
   break;
  case STATE_BACKPACK:
   stateBackpackRender();
   break;
  case STATE_EQUIPMENT:
   stateEquipmentRender();
   break;
  case STATE_EXAMINE_MAP:
   stateExamineMapRender();
   break;
  case STATE_CHOOSE_TARGET:
   stateChooseTargetRender();
   break;
  case STATE_MAIN_MENU:
   stateMainMenuRender();
   break;
  case STATE_CONFIRM_NEW_GAME:
   stateConfirmNewGameRender();
   break;
  case STATE_JOURNAL:
   stateJournalRender();
   break;
  case STATE_LEVEL_UP:
   stateLevelUpRender();
   break;
  case STATE_GAME_OVER:
   stateGameOverRender();
   break;
  case STATE_END_GAME:
   stateEndGameRender();
   break;
 }
}

char* playerEquipmentName(equipmentType_t type)
{
 switch(type)
 {
  case EQUIPMENT_MAX:
  case EQUIPMENT_NONE:
   return "no name";
  case EQUIPMENT_WEAPON: return "Weapon";
  case EQUIPMENT_ARMOR: return "Armor";
 }
 return "no name";
}

//render the player form fromX,fromY point of view
void playerRenderPlayer(int16_t fromX,int16_t fromY,
  int16_t fgColor,int16_t bgColor)
{
 int16_t screenX=player.x+MAP_VIEWPORT_WIDTH/2-fromX;
 int16_t screenY=player.y+MAP_VIEWPORT_HEIGHT/2-fromY;
 if(screenX>=0 && screenX<MAP_VIEWPORT_WIDTH &&
   screenY>=0 && screenY<MAP_VIEWPORT_HEIGHT)
 {
  screenColorPut(screenX,screenY,fgColor,bgColor,'@');
 }
}

int16_t playerActualAttack(void)
{
 int16_t attack=player.attack;
 for(int i=0;i<EQUIPMENT_MAX;i++)
 {
  if(player.equipment[i].type!=ITEM_NONE)
  {
   attack+=player.equipment[i].attackBonus;
  }
 }
 return attack;
}

int16_t playerActualDefence(void)
{
 int16_t defence=player.defence;
 for(int i=0;i<EQUIPMENT_MAX;i++)
 {
  if(player.equipment[i].type!=ITEM_NONE)
  {
   defence+=player.equipment[i].defenceBonus;
  }
 }
 return defence;
}

//automate player death check and, if needed, the change to the game over screen
void playerCheckDeath()
{
 if(player.hitPoints<=0)
 {
  //show player death
  playerLog("Your die.");
  playerGotoState(STATE_GAME_OVER);
 }
}

//add a line to the player journal
void playerLog(char* format,...)
{
 va_list argumentList;
 //get the variadic function arguments
 va_start(argumentList,format);
 memmove(&(player.journal[0]),&(player.journal[1]),
   JOURNAL_LENGTH*JOURNAL_LINE_LENGTH);
 vsnprintf(player.journal[JOURNAL_LENGTH-1],JOURNAL_LINE_LENGTH,
   format,argumentList);
 va_end(argumentList);
}

//teleport the player to a specific position (this is usefull to place the
//player in newly created maps or for teleport traps for example)
void playerTeleportTo(int16_t x,int16_t y)
{
 if(mapIsValid(x,y)==true)
 {
  player.x=x;
  player.y=y;
 }
}

//calculate player field of view inside the actual map
void playerCalculateFOV(void)
{
 //reset map field of view from previous turn
 mapResetFOV();
 //loop through all tile in line of site range
 for(int16_t y=player.y-player.losLength;y<=player.y+player.losLength;y++)
 {
  for(int16_t x=player.x-player.losLength;x<=player.x+player.losLength;x++)
  {
   //if the tile is valid, is in line of sight "real" distance and we can
   //trace an unobstructed line from the player position to that tile
   if(mapIsValid(x,y) && distance(player.x,player.y,x,y)<=player.losLength &&
     bresenhamLos(player.x,player.y,x,y)==true)
   {
    //mark the tile visible
    tile_t* tile=mapTileAt(x,y);
    tile->visible=true;
    if(tileRememberViewed(tile->type)==true)
    {
     //mark it seen if the tileType_t should be remembered by the player
     //this is usefull to show [for example] walls that are not in sight
     //so the player can see the shape of the map as if the character roughly
     //remember it
     tile->seen=true;
    }
   }
  }
 }
}

//calculate the dijkstra map from the player point of view point of view
void playerCalculateDijkstraMap(void)
{
 mapCalculateDijkstraMap(player.x,player.y);
}

//return the distance from x,y to player.x,player.y
bool playerIsInAttackRange(monster_t* monster,int16_t range)
{
 return distance(monster->x,monster->y,player.x,player.y)<=range;
}

//handle an attack from the player to a monster
void playerAttack(monster_t* monster)
{
 int16_t playerAttack=playerActualAttack();
 //simple damage formula
 int16_t damage=MAX(0,playerAttack-monster->defence);
 if(damage>0)
 {
  //show the attack action
  playerLog("You attack %s for %d damage.",monster->name,damage);
  monster->hitPoints-=damage;
  monsterCheckDeath(monster);
 }
 else
 {
  //show attack misses
  playerLog("You attack %s but do no damage.",monster->name);
 }
}

//handle an attack from a monster to the player
void playerAttackedBy(monster_t* monster)
{
 //since monsters turn does not end with player death ... do not "beat a dead
 //player"
 if(player.hitPoints>0)
 {
  int16_t playerDefence=playerActualDefence();
  //simple damage formula
  int16_t damage=MAX(0,monster->attack-playerDefence);
  if(damage>0)
  {
   //show the attack action
   playerLog("%s attacks you for %d damage.",monster->name,damage);
   player.hitPoints-=damage;
   playerCheckDeath();
  }
  else
  {
   //show monster misses
   playerLog("%s attacks you but does no damage.",monster->name);
  }
 }
}

//return the number of items in the player backpack
int16_t playerBackpackCount(void)
{
 int16_t count=0;
 for(int16_t i=0;i<BACKPACK_LENGTH;i++)
 {
  //count only real items
  if(player.backpack[i].type!=ITEM_NONE)
  {
   count++;
  }
 }
 return count;
}

//pack the player backpack towards index 0, but since we always keep the
//backpackpacked, we just have to find the only empty spot that we might have
void playerPackBackpack(void)
{
 int lastItemIndex=-1;
 int firstEmpty=0;
 //search the first free spot
 while(player.backpack[firstEmpty].type!=ITEM_NONE)
 {
  firstEmpty++;
 }
 //pack items from firstEmpty to the backpack length
 for(int16_t i=firstEmpty;i<BACKPACK_LENGTH-1;i++)
 {
  player.backpack[i]=player.backpack[i+1];
  if(lastItemIndex<0 && player.backpack[i].type==ITEM_NONE)
  {
   lastItemIndex=i;
  }
 }
 //remove the last item
 itemInit(&(player.backpack[BACKPACK_LENGTH-1]),ITEM_NONE,0,0);
 //if the player had his selection at the end, move it one back
 if(player.backpackIndex>=lastItemIndex && player.backpackIndex>0)
 {
  player.backpackIndex--;
 }
}

//pickup an item: copy it to the player backpack first free spot and mark the
//original one as not an item [ITEM_NONE]
bool playerPickup(item_t* item)
{
 if(item!=NULL)
 {
  for(int16_t i=0;i<BACKPACK_LENGTH;i++)
  {
   if(player.backpack[i].type==ITEM_NONE)
   {
    player.backpack[i]=*item;
    itemInit(item,ITEM_NONE,0,0);
    playerLog("You pick up %s",item->name);
    return true;
   }
  }
  playerLog("Cannot pick up %s, backpack full",item->name);
 }
 return false;
}

//use the item currently selected being it in hte player backpack or at his foot
bool playerUseSelectedBackpackItem(void)
{
 bool newTurn=false;
 item_t* item=NULL;
 //if the selection is on the backpack, the item is in the backpack
 if(player.backpackSelected==true)
 {
  item=&(player.backpack[player.backpackIndex]);
 }
 else
 {
  //otherwise is on the ground
  item=itemPoolAt(player.x,player.y,player.nearbyIndex);
 }
 if(item!=NULL)
 {
  newTurn=itemUse(item,player.x,player.y);
 }
 return newTurn;
}

bool playerEquipSelectedBackpackItem(void)
{
 equipmentType_t slot=player.backpack[player.backpackIndex].equipmentType;
 if(slot!=EQUIPMENT_NONE)
 {
  item_t equippedItem;
  itemInit(&equippedItem,ITEM_NONE,0,0);
  if(player.equipment[slot].type!=ITEM_NONE)
  {
   equippedItem=player.equipment[slot];
  }
  player.equipment[slot]=player.backpack[player.backpackIndex];
  if(equippedItem.type!=ITEM_NONE)
  {
   playerLog("You take off/unequip %s",equippedItem.name);
   player.backpack[player.backpackIndex]=equippedItem;
  }
  else
  {
   itemInit(&(player.backpack[player.backpackIndex]),ITEM_NONE,0,0);
   playerPackBackpack();
  }
  playerLog("You wear/wield %s",player.equipment[slot].name);
  return true;
 }
 else
 {
  if(player.backpack[player.backpackIndex].type!=ITEM_NONE)
  {
   playerLog("You can't wear/wield %s",
     player.backpack[player.backpackIndex].name);
  }
 }
 return false;
}

bool playerUnequipSelectedEquipmentItem(void)
{
 if(player.equipment[player.equipmentIndex].type!=ITEM_NONE)
 {
  for(int16_t i=0;i<BACKPACK_LENGTH;i++)
  {
   if(player.backpack[i].type==ITEM_NONE)
   {
    player.backpack[i]=player.equipment[player.equipmentIndex];
    itemInit(&(player.equipment[player.equipmentIndex]),ITEM_NONE,0,0);
    playerLog("You take off/unequip %s",player.backpack[i].name);
    return true;
   }
  }
  playerDropSelectedEquipmentItem();
 }
 return false;
}

//drop backpack selected item to the player foot
bool playerDropSelectedBackpackItem(void)
{
 if(player.backpackSelected==true)
 {
  playerLog("You drop %s",player.backpack[player.backpackIndex].name);
  itemPoolAdd(player.backpack[player.backpackIndex].type,player.x,player.y);
  itemInit(&(player.backpack[player.backpackIndex]),ITEM_NONE,0,0);
  playerPackBackpack();
  return true;
 }
 return false;
}

bool playerDropSelectedEquipmentItem(void)
{
 if(player.equipment[player.equipmentIndex].type!=ITEM_NONE)
 {
  playerLog("You drop %s",player.equipment[player.equipmentIndex].name);
  itemPoolAdd(player.equipment[player.equipmentIndex].type,player.x,player.y);
  itemInit(&(player.equipment[player.equipmentIndex]),ITEM_NONE,0,0);
  return true;
 }
 return false;
}

//move the player to the next dungeon level if necessary, return false if
//the action cannot be performed
bool playerDescendStair(void)
{
 int16_t x=0;
 int16_t y=0;
 tile_t* toTile=mapTileAt(player.x,player.y);
 if(toTile!=NULL && toTile->type==TILE_STAIR_DOWN)
 {
  //move the player to the next dungeon level
  player.dungeonLevel++;
  if(diskCanLoadMap(player.dungeonLevel)==true)
  {
   //if the dungeon level can be loaded, load it and move the player to the
   //stair up tile
   diskSavePlayer(PLAYER_SAVE_FILE);
   diskLoadGame();
   mapTilePosition(&x,&y,TILE_STAIR_UP);
   player.x=x;
   player.y=y;
   diskSavePlayer(PLAYER_SAVE_FILE);
  }
  else
  {
   //otherwise generate a new level
   mapGenerate(MAP_CAVE,player.dungeonLevel);
  }
  playerLog("You descend the stair...");
  return true;
 }
 return false;
}

//move the player to the previous dungeon level if necessary, return false if
//the action cannot be performed
bool playerAscendStair(void)
{
 int16_t x=0;
 int16_t y=0;
 tile_t* toTile=mapTileAt(player.x,player.y);
 if(toTile!=NULL && toTile->type==TILE_STAIR_UP)
 {
  if(player.dungeonLevel==0)
  {
   //if the previous level is 0, then the player escaped the dungeon
   playerGotoState(STATE_END_GAME);
  }
  else
  {
   //move the player to the previous level
   player.dungeonLevel--;
   if(diskCanLoadMap(player.dungeonLevel)==true)
   {
    //if the dungeon level can be loaded, load it and move the player to the
    //stair down tile
    diskSavePlayer(PLAYER_SAVE_FILE);
    diskLoadGame();
    mapTilePosition(&x,&y,TILE_STAIR_DOWN);
    player.x=x;
    player.y=y;
    diskSavePlayer(PLAYER_SAVE_FILE);
   }
   else
   {
    //otherwise generate a new level
    mapGenerate(MAP_CAVE,player.dungeonLevel);
   }
   playerLog("You ascend the stair...");
   return true;
  }
  return false;
 }
 return false;
}

//return the required experience to level up
int32_t playerExperienceForNextLevel(void)
{
 return 200+player.level*150;
}

//check if the player gained a level and if necessary move him to the level up
//screen
void playerCheckLevelUp(void)
{
 if(player.experience>playerExperienceForNextLevel())
 {
  player.experience=0;
  player.level++;
  playerGotoState(STATE_LEVEL_UP);
 }
}

