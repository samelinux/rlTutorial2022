
#include <sys/param.h>
#include "itemLightningScroll.h"
#include "item.h"
#include "macro.h"
#include "map.h"
#include "monster.h"
#include "player.h"

//implement the behaviour of ITEM_LIGHTNING_SCROLL
bool itemUseLightningScroll(item_t* item,int16_t x,int16_t y)
{
 int8_t range=player.losLength;
 int16_t minDistance=range+1;
 monster_t* target=NULL;
 //search for the nearest mosnter
 for(int8_t dy=-range;dy<=range;dy++)
 {
  for(int8_t dx=-range;dx<=range;dx++)
  {
   int16_t targetX=x+dx;
   int16_t targetY=y+dy;
   int16_t distance=distance(player.x,player.y,targetX,targetY);
   //distance is in trange and better the the one before
   if(distance<=range && distance<minDistance)
   {
    tile_t* tile=mapTileAt(targetX,targetY);
    monster_t* monster=monsterPoolAt(targetX,targetY);
    //the player is targeting a visible tile with a monster in it
    if(tile!=NULL && tile->visible && monster!=NULL)
    {
     target=monster;
     minDistance=distance;
    }
   }
  }
 }
 //if we found a valid target damage it
 if(target!=NULL)
 {
  playerLog("A lightning bolt strike %s for 20 damage",target->name);
  target->hitPoints-=20;
  monsterCheckDeath(target);
  itemConsume(item);
  return true;
 }
 else
 {
  //otherwise inform the player
  playerLog("No monster in sight");
 }
 return false;
}

