
#include <sys/param.h>
#include "itemFireballScroll.h"
#include "item.h"
#include "monster.h"
#include "player.h"

//implement the behaviour of ITEM_FIREBALL_SCROLL
bool itemUseFireballScroll(item_t* item,int16_t x,int16_t y)
{
 //load the item range
 int8_t range=itemRangeFireballScroll();
 playerLog("You hurl a ball of fire ...");
 //for each tile in the range
 for(int8_t dy=-range;dy<=range;dy++)
 {
  for(int8_t dx=-range;dx<=range;dx++)
  {
   int16_t targetX=x+dx;
   int16_t targetY=y+dy;
   monster_t* monster=monsterPoolAt(targetX,targetY);
   //if there is a monster in that tile damage it
   if(monster!=NULL)
   {
    playerLog("%s is engulfed in a fiery explosion, taking 12 damage",
      monster->name);
    monster->hitPoints-=12;
    monsterCheckDeath(monster);
   }
   else
   {
    //if the player put himself in danger ... that's not our fault!
    if(targetX==player.x && targetY==player.y)
    {
     playerLog("You are engulfed in a fiery explosion, taking 12 damage");
     player.hitPoints-=12;
     playerCheckDeath();
    }
   }
  }
 }
 itemConsume(item);
 return true;
}

//return the fireball explosion range
int8_t itemRangeFireballScroll()
{
 return 3;
}

