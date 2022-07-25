
#include <sys/param.h>
#include "item.h"
#include "player.h"

//implement the behaviour of ITEM_HEALTH_POTION
void itemUseHealthPotion(item_t* item,int16_t x,int16_t y)
{
 //if the target is the player, heal him and write a log
 if(player.x==x && player.y==y)
 {
  if(player.hitPoints==player.maxHitPoints)
  {
   playerLog("Already at full hit points");
   return;
  }
  int16_t newValue=MIN(player.maxHitPoints,player.hitPoints+4);
  playerLog("You quaff health potion recovering %d hit points",
    newValue-player.hitPoints);
  player.hitPoints=newValue;
  item->type=ITEM_NONE;
 }
 else
 {
  //if the target is a monster, heal it and write a log
  //this is interesting because if we implement potion throwing then the player
  //can accidentally heal a monster by throwing it a health potion 8)))
  monster_t* monster=monsterPoolAt(x,y);
  if(monster!=NULL)
  {
   int16_t newValue=MIN(monster->maxHitPoints,monster->hitPoints+4);
   playerLog("%s quaff health potion recovering %d hit points",
     monster->name,newValue-monster->hitPoints);
   monster->hitPoints=newValue;
   item->type=ITEM_NONE;
  }
 }
}

