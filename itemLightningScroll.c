
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
 for(int8_t dy=-range;dy<=range;dy++)
 {
  for(int8_t dx=-range;dx<=range;dx++)
  {
   int16_t targetX=x+dx;
   int16_t targetY=y+dy;
   int16_t distance=distance(player.x,player.y,targetX,targetY);
   if(distance<=range && distance<minDistance)
   {
    tile_t* tile=mapTileAt(targetX,targetY);
    monster_t* monster=monsterPoolAt(targetX,targetY);
    if(tile!=NULL && tile->visible && monster!=NULL)
    {
     target=monster;
     minDistance=distance;
    }
   }
  }
 }
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
  playerLog("No monster in sight");
 }
 return false;
}

