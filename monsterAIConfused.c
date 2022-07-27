
#include <stdlib.h>
#include "monsterAIConfused.h"
#include "player.h"
#include "monster.h"
#include "map.h"
#include "random.h"

//perform one action using MONSTER_AI_CONFUSE for monster
void monsterAIConfusedAct(monster_t* monster)
{
 //randomize the monster movement
 int8_t dx=randomGet(0,2)-1;
 int8_t dy=randomGet(0,2)-1;
 //if the moster randomized a valid move [standing still is not a move]
 if(dx!=0 || dy!=0)
 {
  int16_t x=monster->x+dx;
  int16_t y=monster->y+dy;
  tile_t* tile=mapTileAt(x,y);
  monster_t* target=monsterPoolAt(x,y);
  //if the movement would place the monster in a valid tile
  if(tile!=NULL)
  {
   //if the tile is occupied by another monster, attack it
   if(target!=NULL)
   {
    monsterAttackMonster(monster,target);
   }
   else
   {
    //if the monster wants to move where the player is, attack him
    if(x==player.x && y==player.y)
    {
     playerAttackedBy(monster);
    }
    else
    {
     //otherwise move
     monster->x=x;
     monster->y=y;
    }
   }
  }
 }
}

