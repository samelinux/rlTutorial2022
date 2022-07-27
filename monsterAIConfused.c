
#include <stdlib.h>
#include "monsterAIConfused.h"
#include "player.h"
#include "monster.h"
#include "map.h"
#include "random.h"

//perform one action using MONSTER_AI_CONFUSE for monster
void monsterAIConfusedAct(monster_t* monster)
{
 int8_t dx=randomGet(0,2)-1;
 int8_t dy=randomGet(0,2)-1;
 if(dx!=0 || dy!=0)
 {
  int16_t x=monster->x+dx;
  int16_t y=monster->y+dy;
  tile_t* tile=mapTileAt(x,y);
  monster_t* target=monsterPoolAt(x,y);
  if(tile!=NULL)
  {
   if(target!=NULL)
   {
    monsterAttackMonster(monster,target);
   }
   else
   {
    if(x==player.x && y==player.y)
    {
     playerAttackedBy(monster);
    }
    else
    {
     monster->x=x;
     monster->y=y;
    }
   }
  }
 }
}

