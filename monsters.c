
#include "monsters.h"

monster_t monsters[MONSTERS_SIZE];

//initialize monsters structure
void monstersInit(void)
{
 //clear monsters list [MONSTER_NONE=0 so each monsters[i].type=MONSTER_NONE]
 memset(&monsters,0,sizeof(monster_t)*MONSTERS_SIZE);
}

//add a monster to the pool of monsters
void monstersAdd(monster_t monster)
{
 for(int i=0;i<MONSTERS_SIZE;i++)
 {
  //search for an ampty monster position and add it
  if(monsters[i].type==MONSTER_NONE)
  {
   monsters[i]=monster;
   return;
  }
 }
}

//render all visible monsters
void monstersRender(void)
{
 for(int i=0;i<MONSTERS_SIZE;i++)
 {
  //render each monster
  if(monsters[i].type!=MONSTER_NONE)
  {
   screenColorPut(monsters[i].x,monsters[i].y,monsters[i].color,BLACK,monsters[i].glyph);
  }
 }
}

