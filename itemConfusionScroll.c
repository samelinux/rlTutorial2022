
#include <sys/param.h>
#include "itemConfusionScroll.h"
#include "item.h"
#include "monster.h"
#include "player.h"

//implement the behaviour of ITEM_CONFUSION_SCROLL
bool itemUseConfusionScroll(item_t* item,int16_t x,int16_t y)
{
 monster_t* monster=monsterPoolAt(x,y);
 if(monster!=NULL)
 {
  playerLog("%s looks confused as it starts to stumble around",monster->name);
  monster->confusionDuration=10;
  itemConsume(item);
  return true;
 }
 else
 {
  if(x==player.x && y==player.y)
  {
   playerLog("You can't target yourself");
  }
  else
  {
   playerLog("You must target a monster");
  }
  return false;
 }
}

