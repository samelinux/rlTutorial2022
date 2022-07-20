
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <sys/param.h>
#include "player.h"
#include "bresenham.h"
#include "macro.h"
#include "map.h"
#include "screen.h"
#include "stateMap.h"
#include "stateExamineMap.h"
#include "stateJournal.h"
#include "stateMainMenu.h"
#include "stateGameOver.h"

//declare a player
player_t player;

//set the player state to STATE_MAIN_MENU
void playerInit(void)
{
 player.state=STATE_MAIN_MENU;
}

//deinitialize the player
void playerDeinit(void)
{
 //for now doed nothing, but if we decide to allocate the player dynamically
 //here is the right player do deallocate it
}

//setup the player for a new game
void playerNewGame(void)
{
 player.x=0;
 player.y=0;
 player.losLength=4;
 player.maxHitPoints=30;
 player.hitPoints=player.maxHitPoints;
 player.defence=2;
 player.attack=5;
 memset(&(player.journal),0,
   sizeof(char)*JOURNAL_LENGTH*JOURNAL_LINE_LENGTH);
 player.journalIndex=0;
 player.examineMapX=0;
 player.examineMapY=0;
}

//call the states update function based on the actual player state
bool playerUpdate(char input)
{
 switch(player.state)
 {
  case STATE_MAX:
   return false;
  case STATE_MAP:
   return stateMapUpdate(&player,input);
  case STATE_EXAMINE_MAP:
   return stateExamineMapUpdate(&player,input);
  case STATE_MAIN_MENU:
   return stateMainMenuUpdate(&player,input);
  case STATE_JOURNAL:
   return stateJournalUpdate(&player,input);
  case STATE_GAME_OVER:
   return stateGameOverUpdate(&player,input);
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
   stateMapRender(&player);
   break;
  case STATE_EXAMINE_MAP:
   stateExamineMapRender(&player);
   break;
  case STATE_MAIN_MENU:
   stateMainMenuRender(&player);
   break;
  case STATE_JOURNAL:
   stateJournalRender(&player);
   break;
  case STATE_GAME_OVER:
   stateGameOverRender(&player);
   break;
 }
}

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
   if(mapIsValid(x,y) && distance(player.x,player.y,x,y)<player.losLength &&
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
 //simple damage formula
 int16_t damage=MAX(0,player.attack-monster->defence);
 if(damage>0)
 {
  //show the attack action
  playerLog("You attack %s for %d damage.",monster->name,damage);
  monster->hitPoints-=damage;
  if(monster->hitPoints<=0)
  {
   //show monster death
   playerLog("%s dies.",monster->name);
   monster->type=MONSTER_NONE;
  }
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
  //simple damage formula
  int16_t damage=MAX(0,monster->attack-player.defence);
  if(damage>0)
  {
   //show the attack action
   playerLog("%s attacks you for %d damage.",monster->name,damage);
   player.hitPoints-=damage;
   if(player.hitPoints<=0)
   {
    //show player death
    playerLog("Your die.");
    player.state=STATE_GAME_OVER;
   }
  }
  else
  {
   //show monster misses
   playerLog("%s attacks you but does no damage.",monster->name);
  }
 }
}

