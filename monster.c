
#include <stdlib.h>
#include <string.h>
#include <sys/param.h>
#include "monster.h"
#include "map.h"
#include "screen.h"
#include "monsterAIHostile.h"
#include "monsterAIConfused.h"
#include "random.h"
#include "player.h"

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
 monster->maxHitPoints=monsterMaxHitPoints(type);
 monster->hitPoints=monster->maxHitPoints;
 monster->defence=monsterDefence(type);
 monster->attack=monsterAttack(type);
 monster->ai=monsterAI(type);
 monster->confusionDuration=0;
}

void monsterRender(monster_t* monster,int16_t fromX,int16_t fromY,
  int16_t fgColor,int16_t bgColor)
{
 int16_t screenX=monster->x+MAP_VIEWPORT_WIDTH/2-fromX;
 int16_t screenY=monster->y+MAP_VIEWPORT_HEIGHT/2-fromY;
 if(screenX>=0 && screenX<MAP_VIEWPORT_WIDTH &&
   screenY>=0 && screenY<MAP_VIEWPORT_HEIGHT)
 {
  screenColorPut(screenX,screenY,fgColor,bgColor,monster->glyph);
 }
}

void monsterCheckDeath(monster_t* monster)
{
 if(monster->hitPoints<=0)
  {
   //show monster death
   playerLog("%s dies.",monster->name);
   monster->type=MONSTER_NONE;
  }
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

//return each monsterType_t maximum hit points
int8_t monsterMaxHitPoints(monsterType_t type)
{
 switch(type)
 {
  case MONSTER_MAX:
  case MONSTER_NONE: return 0;
  case MONSTER_RAT: return 5;
  case MONSTER_ORC: return 10;
  case MONSTER_TROL: return 16;
 }
 return 0;
}

//return each monsterType_t defence
int8_t monsterDefence(monsterType_t type)
{
 switch(type)
 {
  case MONSTER_MAX:
  case MONSTER_NONE: return 0;
  case MONSTER_RAT: return 0;
  case MONSTER_ORC: return 1;
  case MONSTER_TROL: return 2;
 }
 return 0;
}

//return each monsterType_t attack
int8_t monsterAttack(monsterType_t type)
{
 switch(type)
 {
  case MONSTER_MAX:
  case MONSTER_NONE: return 0;
  case MONSTER_RAT: return 1;
  case MONSTER_ORC: return 3;
  case MONSTER_TROL: return 4;
 }
 return 0;
}
//return each monsterType_t ai
monsterAI_t monsterAI(monsterType_t type)
{
 switch(type)
 {
  case MONSTER_MAX:
  case MONSTER_NONE: return MONSTER_AI_NONE;
  case MONSTER_RAT: return MONSTER_AI_HOSTILE;
  case MONSTER_ORC: return MONSTER_AI_HOSTILE;
  case MONSTER_TROL: return MONSTER_AI_HOSTILE;
 }
 return MONSTER_AI_NONE;
}

void monsterAttackMonster(monster_t* attacker,monster_t* defender)
{
 int16_t damage=MAX(0,attacker->attack-defender->defence);
 if(damage>0)
 {
  playerLog("%s attacks %s for %d damage.",attacker->name,defender->name,
    damage);
  defender->hitPoints-=damage;
  monsterCheckDeath(defender);
 }
 else
 {
  playerLog("%s attacks %s but does no damage",attacker->name,defender->name);
 }
}

//initialize the monsters pool
void monsterPoolInit(void)
{
 //clear monsters list [MONSTER_NONE=0 so each monsterPool[i].type=MONSTER_NONE]
 memset(monsterPool,0,sizeof(monster_t)*MONSTER_POOL_SIZE);
}

//deinitialize the monster pool
void monsterPoolDeinit(void)
{
 //for now doed nothing, but if we decide to allocate the pool dynamically
 //here is the right place do deallocate it
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
  //search for any monster which occupy the position x,y and is alive
  if(monsterPool[i].x==x && monsterPool[i].y==y &&
    monsterPool[i].hitPoints>0)
  {
   return &monsterPool[i];
  }
 }
 return NULL;
}

//render all visible monsters
void monsterPoolRender(int16_t fromX,int16_t fromY)
{
 for(int i=0;i<MONSTER_POOL_SIZE;i++)
 {
  //render each alive monster
  if(monsterPool[i].type!=MONSTER_NONE && monsterPool[i].hitPoints>0)
  {
   tile_t* tile=mapTileAt(monsterPool[i].x,monsterPool[i].y);
   //render a monster only if the player can see the tile the monster is in
   if(tile!=NULL && tile->visible==true)
   {
    monsterRender(&(monsterPool[i]),fromX,fromY,
      monsterPool[i].color,tile->bgColor);
   }
  }
 }
}

//generate a new turn for all monsters
void monsterPoolHandleTurn(void)
{
 for(int i=0;i<MONSTER_POOL_SIZE;i++)
 {
  //if the monster is present and alive
  if(monsterPool[i].type!=MONSTER_NONE && monsterPool[i].hitPoints>0)
  {
   //reset the current dijkstra map
   mapResetDijkstraMap();
   //update the dijkstra map
   playerCalculateDijkstraMap();
   if(monsterPool[i].confusionDuration>0)
   {
    monsterAIConfusedAct(&(monsterPool[i]));
    monsterPool[i].confusionDuration--;
   }
   else
   {
    //use its ai to perform an action
    switch(monsterPool[i].ai)
    {
     case MONSTER_AI_NONE:
     case MONSTER_AI_MAX:
      break;
     case MONSTER_AI_HOSTILE:
      monsterAIHostileAct(&(monsterPool[i]));
      break;
     case MONSTER_AI_CONFUSED:
      monsterAIConfusedAct(&(monsterPool[i]));
      break;
    }
   }
  }
 }
}

void monsterBestMoveToReachPlayer(monster_t* monster)
{
 int8_t bestDx=0;
 int8_t bestDy=0;
 int16_t bestHazard=0;
 //calculate the best hazard to get to the player
 for(int8_t dy=-1;dy<=1;dy++)
 {
  for(int8_t dx=-1;dx<=1;dx++)
  {
   if(dx!=0 || dy!=0)
   {
    int16_t newHazard=mapDijkstraAt(monster->x+dx,monster->y+dy);
    monster_t* neighbour=monsterPoolAt(monster->x+dx,monster->y+dy);
    //if the move is to a walkable tile, if the hazard is better and if there
    //is no other monster there
    if(newHazard!=0 && newHazard>bestHazard && neighbour==NULL)
    {
     //save the best move and the new best hazard
     bestDx=dx;
     bestDy=dy;
     bestHazard=newHazard;
    }
   }
  }
 }
 //if we found a better hazard than staying still
 if(bestHazard!=0)
 {
  monster->x+=bestDx;
  monster->y+=bestDy;
 }
}

