
#include <sys/param.h>
#include "itemConfusionScroll.h"
#include "item.h"
#include "monster.h"
#include "player.h"

//implement the behaviour of ITEM_CONFUSION_SCROLL
bool itemUseConfusionScroll(item_t* item,int16_t x,int16_t y)
{
 monster_t* monster=monsterPoolAt(x,y);
 //if there is a monster at the target location
 if(monster!=NULL)
 {
  playerLog("%s looks confused as it starts to stumble around",monster->name);
  //confuse it for 10 turns
  monster->confusionDuration=10;
  itemConsume(item);
  return true;
 }
 else
 {
  //are you targeting yourself with a confision scroll? BUT WHY?
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

