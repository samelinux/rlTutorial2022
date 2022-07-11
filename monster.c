
#include "monster.h"

monster_t monsterPool[MONSTER_POOL_SIZE];

//setup a monster_t structure
void monsterInit(monster_t* monster,monsterType_t type)
{
 int16_t x=0;
 int16_t y=0;
 monster->type=type;
 //get a random walkable position and place the monster there
 mapRandomWalkablePosition(&x,&y);
 monster->x=x;
 monster->y=y;
 //get standard values for monsterType_t
 memset(monster->name,0,sizeof(char)*MONSTER_NAME_LENGTH);
 strncpy(monster->name,monsterName(type),MONSTER_NAME_LENGTH);
 monster->glyph=monsterGlyph(type);
 monster->color=monsterColor(type);
}

//return each monsterType_t name
char* monsterName(monsterType_t type)
{
 switch(type)
 {
  case MONSTER_MAX:
  case MONSTER_NONE: return "no name";
  case MONSTER_RAT: return "rat";
  case MONSTER_ORC: return "orc";
  case MONSTER_TROL: return "trol";
 }
 return "no name";
}

//return each monsterType_t character representation
char monsterGlyph(monsterType_t type)
{
 switch(type)
 {
  case MONSTER_MAX:
  case MONSTER_NONE: return '?';
  case MONSTER_RAT: return 'r';
  case MONSTER_ORC: return 'o';
  case MONSTER_TROL: return 'T';
 }
 return '?';
}

//return each monsterType_t color
int8_t monsterColor(monsterType_t type)
{
 switch(type)
 {
  case MONSTER_MAX:
  case MONSTER_NONE: return BLACK;
  case MONSTER_RAT: return RED;
  case MONSTER_ORC: return GREEN;
  case MONSTER_TROL: return GREEN;
 }
 return BLACK;
}

//initialize monsters structure
void monsterPoolInit(void)
{
 //clear monsters list [MONSTER_NONE=0 so each monsterPool[i].type=MONSTER_NONE]
 memset(&monsterPool,0,sizeof(monster_t)*MONSTER_POOL_SIZE);
}

//add a monster to the pool of monsters
void monsterPoolAdd(monsterType_t type)
{
 for(int i=0;i<MONSTER_POOL_SIZE;i++)
 {
  //search for an ampty monster position and add it
  if(monsterPool[i].type==MONSTER_NONE)
  {
   monsterInit(&monsterPool[i],type);
   return;
  }
 }
}

//spawn up to maxMonsters monsters in the map
void monsterPoolSpawn(int16_t maxMonsters)
{
 //randomize the number of monsters
 int16_t count=randomGet(0,maxMonsters);
 while(count>0)
 {
  //generate a random monster type and add it to the pool
  monsterType_t type=randomGet(MONSTER_NONE+1,MONSTER_MAX-1);
  monsterPoolAdd(type);
  count--;
 }
}

//return the pointer to a monster at x,y if there is any, NULL otherwise
monster_t* monsterPoolAt(int16_t x,int16_t y)
{
 for(int i=0;i<MONSTER_POOL_SIZE;i++)
 {
  //search for any monster which occupy the position x,y
  if(monsterPool[i].x==x && monsterPool[i].y==y)
  {
   return &monsterPool[i];
  }
 }
 return NULL;
}

//render all visible monsters
void monsterPoolRender(void)
{
 for(int i=0;i<MONSTER_POOL_SIZE;i++)
 {
  //render each monster
  if(monsterPool[i].type!=MONSTER_NONE)
  {
   tile_t* tile=mapTileAt(monsterPool[i].x,monsterPool[i].y);
   //render a monster only if the player can see the tile the monster is in
   if(tile!=NULL && tile->visible==true)
   {
    screenColorPut(monsterPool[i].x,monsterPool[i].y,
      monsterPool[i].color,tile->bgColor,monsterPool[i].glyph);
   }
  }
 }
}

//generate a new turn for all monsters
void monsterPoolHandleTurn(void)
{
 for(int i=0;i<MONSTER_POOL_SIZE;i++)
 {
  if(monsterPool[i].type!=MONSTER_NONE)
  {
   fprintf(stderr,"The %s contemplates the meaning of life.\n",
     monsterPool[i].name);
  }
 }
}

