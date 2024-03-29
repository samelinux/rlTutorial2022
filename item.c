
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/param.h>
#include "item.h"
#include "itemHealthPotion.h"
#include "itemLightningScroll.h"
#include "map.h"
#include "random.h"
#include "screen.h"
#include "player.h"

item_t itemPool[ITEM_POOL_SIZE];

//setup an item_t struct
void itemInit(item_t* item,itemType_t type,int16_t x,int16_t y)
{
 item->type=type;
 item->equipmentType=itemEquipmentType(type);
 item->x=x;
 item->y=y;
 memset(item->name,0,sizeof(char)*ITEM_NAME_LENGTH);
 strncpy(item->name,itemName(type),ITEM_NAME_LENGTH);
 item->glyph=itemGlyph(type);
 item->color=itemColor(type);
 item->attackBonus=itemAttackBonus(type);
 item->defenceBonus=itemDefenceBonus(type);
}

//render an item from fromX,fromY point of view
void itemRender(item_t* item,int16_t fromX,int16_t fromY,
  int16_t fgColor,int16_t bgColor)
{
 int16_t screenX=item->x+MAP_VIEWPORT_WIDTH/2-fromX;
 int16_t screenY=item->y+MAP_VIEWPORT_HEIGHT/2-fromY;
 if(screenX>=0 && screenX<MAP_VIEWPORT_WIDTH &&
   screenY>=0 && screenY<MAP_VIEWPORT_HEIGHT)
 {
  item_t* otherItem=itemPoolAt(item->x,item->y,1);
  //if there are more than on item, print the 'item pile' glyph
  if(otherItem!=NULL)
  {
   screenColorPut(screenX,screenY,ITEM_PILE_COLOR,bgColor,ITEM_PILE_GLYPH);
  }
  else
  {
   screenColorPut(screenX,screenY,fgColor,bgColor,item->glyph);
  }
 }
}

equipmentType_t itemEquipmentType(itemType_t type)
{
 switch(type)
 {
  case ITEM_MAX:
  case ITEM_NONE:
  case ITEM_HEALTH_POTION:
  case ITEM_LIGHTNING_SCROLL:
  case ITEM_CONFUSION_SCROLL:
  case ITEM_FIREBALL_SCROLL:
   return EQUIPMENT_NONE;
  case ITEM_DAGGER:
  case ITEM_SWORD:
   return EQUIPMENT_WEAPON;
  case ITEM_LEATHER_ARMOR:
  case ITEM_CHAIN_MAIL:
   return EQUIPMENT_ARMOR;
 }
 return EQUIPMENT_NONE;
}

//return each itemType_t name
char* itemName(itemType_t type)
{
 switch(type)
 {
  case ITEM_MAX:
  case ITEM_NONE: return "no name";
  case ITEM_HEALTH_POTION: return "health potion";
  case ITEM_LIGHTNING_SCROLL: return "lightning scroll";
  case ITEM_CONFUSION_SCROLL: return "confusion scroll";
  case ITEM_FIREBALL_SCROLL: return "fireball scroll";
  case ITEM_DAGGER: return "dagger";
  case ITEM_SWORD: return "sword";
  case ITEM_LEATHER_ARMOR: return "leather armor";
  case ITEM_CHAIN_MAIL: return "chain mail";
 }
 return "no name";
}

//return each itemType_t character representation
char itemGlyph(itemType_t type)
{
 switch(type)
 {
  case ITEM_MAX:
  case ITEM_NONE: return '?';
  case ITEM_HEALTH_POTION: return '!';
  case ITEM_LIGHTNING_SCROLL:
  case ITEM_CONFUSION_SCROLL:
  case ITEM_FIREBALL_SCROLL: return '~';
  case ITEM_DAGGER: return '/';
  case ITEM_SWORD: return '/';
  case ITEM_LEATHER_ARMOR: return '[';
  case ITEM_CHAIN_MAIL: return '[';
 }
 return '?';
}

//return each itemType_t color
int8_t itemColor(itemType_t type)
{
 switch(type)
 {
  case ITEM_MAX:
  case ITEM_NONE: return BLACK;
  case ITEM_HEALTH_POTION: return GREEN;
  case ITEM_LIGHTNING_SCROLL:
  case ITEM_CONFUSION_SCROLL:
  case ITEM_FIREBALL_SCROLL: return MAGENTA;
  case ITEM_DAGGER:
  case ITEM_SWORD: return CYAN;
  case ITEM_LEATHER_ARMOR:
  case ITEM_CHAIN_MAIL: return RED;
 }
 return BLACK;
}

int8_t itemAttackBonus(itemType_t type)
{
 switch(type)
 {
  case ITEM_MAX:
  case ITEM_NONE:
  case ITEM_HEALTH_POTION:
  case ITEM_LIGHTNING_SCROLL:
  case ITEM_CONFUSION_SCROLL:
  case ITEM_FIREBALL_SCROLL:
  case ITEM_LEATHER_ARMOR:
  case ITEM_CHAIN_MAIL:
   return 0;
  case ITEM_DAGGER: return 2;
  case ITEM_SWORD: return 4;
 }
 return 0;
}

int8_t itemDefenceBonus(itemType_t type)
{
 switch(type)
 {
  case ITEM_MAX:
  case ITEM_NONE:
  case ITEM_HEALTH_POTION:
  case ITEM_LIGHTNING_SCROLL:
  case ITEM_CONFUSION_SCROLL:
  case ITEM_FIREBALL_SCROLL:
  case ITEM_DAGGER:
  case ITEM_SWORD:
   return 0;
  case ITEM_LEATHER_ARMOR: return 1;
  case ITEM_CHAIN_MAIL: return 3;
 }
 return 0;
}

int16_t itemMaxAtDepth(int16_t depth)
{
 int8_t maxItemPerDepth[7]={
   6,
   6,
   6,
   8,
   8,
   8,
  12,
 };
 depth=MIN(depth,6);
 return maxItemPerDepth[MIN(depth,6)];
}

itemType_t itemRandomAtDepth(int16_t depth)
{
 int16_t chances[7][ITEM_MAX-1]={
  //HEALTH_POTION, LIGHTNING_SCROLL, CONFUSION_SCROLL, FIREBALL_SCROLL
  //DAGGER, SWORD, LEATHER_ARMOR, CHAIN_MAIL
  {           100,                0,                0,               0,
         0,     0,             0,          0},
  {            80,                0,               80,               0,
         0,     0,             0,          0},
  {            60,                0,              100,              60,
         0,     0,             0,          0},
  {             0,              100,                0,               0,
         0,     0,             0,          0},
  {            60,                0,                0,               0,
         0,    50,             0,         50},
  {            80,               60,               80,              80,
         0,     0,             0,          0},
  {             0,                0,                0,             100,
         0,    80,             0,         80},
 };
 depth=MIN(depth,6);
 uint64_t maxCance=0;
 uint64_t cumulativeChance=0;
 for(int i=1;i<ITEM_MAX;i++)
 {
  maxCance+=chances[depth][i-1];
 }
 uint64_t pick=randomGet(0,maxCance);
 for(int i=1;i<ITEM_MAX;i++)
 {
  if(chances[depth][i-1]>0)
  {
   cumulativeChance+=chances[depth][i-1];
   if(pick<cumulativeChance)
   {
    return i;
   }
  }
 }
 return ITEM_NONE;
}

//wrapper to implement item usage since every items has its own functionality
bool itemUse(item_t* item,int16_t x,int16_t y)
{
 bool newTurn=false;
 switch(item->type)
 {
  case ITEM_NONE:
  case ITEM_MAX:
   break;
  //health potion use is immediate
  case ITEM_HEALTH_POTION:
   newTurn=itemUseHealthPotion(item,x,y);
   playerGotoState(STATE_MAP);
   break;
  //lightning scroll use is immediate
  case ITEM_LIGHTNING_SCROLL:
   newTurn=itemUseLightningScroll(item,x,y);
   playerGotoState(STATE_MAP);
   break;
  //confusion and fireball scrolls use need a target
  case ITEM_CONFUSION_SCROLL:
  case ITEM_FIREBALL_SCROLL:
   player.itemToUse=item;
   playerGotoState(STATE_CHOOSE_TARGET);
   break;
  //these item are not usable
  case ITEM_DAGGER:
  case ITEM_SWORD:
  case ITEM_LEATHER_ARMOR:
  case ITEM_CHAIN_MAIL:
   break;
 }
 return newTurn;
}

//initialize the item pool
void itemPoolInit(void)
{
 memset(itemPool,0,sizeof(item_t)*ITEM_POOL_SIZE);
}

//deinitialize the item pool
void itemPoolDeinit(void)
{
 //for now doed nothing, but if we decide to allocate the pool dynamically
 //here is the right place do deallocate it
}

//save the itemPool to a file
bool itemPoolSave(FILE* aFile)
{
 size_t written=fwrite(itemPool,sizeof(item_t)*ITEM_POOL_SIZE,1,aFile);
 if(written==1)
 {
  return true;
 }
 return false;
}

//load the itemPool from a file
bool itemPoolLoad(FILE* aFile)
{
 size_t readed=fread(itemPool,sizeof(item_t)*ITEM_POOL_SIZE,1,aFile);
 if(readed==1)
 {
  return true;
 }
 return false;
}

//add an item to the pool of items
void itemPoolAdd(itemType_t type,int16_t x,int16_t y)
{
 for(int i=0;i<ITEM_POOL_SIZE;i++)
 {
  //search for an empty item position and add it
  if(itemPool[i].type==ITEM_NONE)
  {
   itemInit(&itemPool[i],type,x,y);
   return;
  }
 }
}

//spawn up t maxItems item in the map
void itemPoolSpawn(void)
{
 int16_t x;
 int16_t y;
 //randomize the number of items
 int16_t count=randomGet(0,itemMaxAtDepth(mapDepth()));
 while(count>0)
 {
  //generate a random item type and add it to the pool
  itemType_t type=itemRandomAtDepth(mapDepth());
  mapRandomWalkablePosition(&x,&y);
  itemPoolAdd(type,x,y);
  count--;
 }
}

//return the number of items at x,y in the map
int16_t itemPoolCountAt(int16_t x,int16_t y)
{
 int16_t count=0;
 for(int i=0;i<ITEM_POOL_SIZE;i++)
 {
  //count only real items which are at x,y
  if(itemPool[i].type!=ITEM_NONE && itemPool[i].x==x && itemPool[i].y==y)
  {
   count++;
  }
 }
 return count;
}

//return the item at position index at x,y in the map
item_t* itemPoolAt(int16_t x,int16_t y,int index)
{
 for(int i=0;i<ITEM_POOL_SIZE;i++)
 {
  //search for any real item which occupy the position x,y until we count index
  //items
  if(itemPool[i].x==x && itemPool[i].y==y &&
    itemPool[i].type!=ITEM_NONE && index--==0)
  {
   return &itemPool[i];
  }
 }
 return NULL;
}

//render all visible items
void itemPoolRender(int16_t fromX,int16_t fromY)
{
 for(int i=0;i<ITEM_POOL_SIZE;i++)
 {
  //render each item
  if(itemPool[i].type!=ITEM_NONE)
  {
   tile_t* tile=mapTileAt(itemPool[i].x,itemPool[i].y);
   //render a item only if the player can see the tile the item is in
   if(tile!=NULL && tile->visible==true)
   {
    itemRender(&(itemPool[i]),fromX,fromY,itemPool[i].color,tile->bgColor);
   }
  }
 }
}

//consume an item and pack the player backpack in case the item was in his
//backpack
void itemConsume(item_t* item)
{
 item->type=ITEM_NONE;
 playerPackBackpack();
}

