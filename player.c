
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <sys/param.h>
#include "player.h"
#include "bresenham.h"
#include "macro.h"
#include "map.h"
#include "screen.h"

//declare a player
player_t player;

//setup a player_t structure
void playerInit(int16_t x,int16_t y)
{
 player.x=x;
 player.y=y;
 player.losLength=4;
 player.maxHitPoints=30;
 player.hitPoints=player.maxHitPoints;
 player.defence=2;
 player.attack=5;
}

//handle one input from the player
bool playerHandleInput(char input)
{
 bool newTurn=false;
 if(player.hitPoints>0)
 {
  tile_t* toTile=NULL;
  int8_t x=player.x;
  int8_t y=player.y;
  //each action can change newTurn to true to signal the main loop a net turn
  //has passed. You may want some actoins to not consume a turn, in that case
  //just leave newTurn to false
  switch(input)
  {
   case '5':
   case '.':
    newTurn=true;
    break;
   case '7':
   case 'y':
    y-=1;
    x-=1;
    newTurn=true;
    break;
   case 'u':
   case '9':
    y-=1;
    x+=1;
    newTurn=true;
    break;
   case '4':
   case 'h':
    x-=1;
    newTurn=true;
    break;
   case '2':
   case 'j':
    y+=1;
    newTurn=true;
    break;
   case '8':
   case 'k':
    y-=1;
    newTurn=true;
    break;
   case '6':
   case 'l':
    x+=1;
    newTurn=true;
    break;
   case '1':
   case 'b':
    y+=1;
    x-=1;
    newTurn=true;
    break;
   case '3':
   case 'n':
    y+=1;
    x+=1;
    newTurn=true;
    break;
  }
  //if a tile exists at the new location [avoid goind off the map boundaries]
  toTile=mapTileAt(x,y);
  if(toTile!=NULL)
  {
   monster_t* monster=monsterPoolAt(x,y);
   //if a monster is present where the player wants to move, attack it
   if(monster!=NULL)
   {
    playerAttack(monster);
   }
   else
   {
    //if the tile is walkable
    if(toTile->walkable==true)
    {
     player.x=x;
     player.y=y;
    }
   }
  }
 }
 //return the newTurn value to the main loop so monsters can take a turn when
 //the player take a turn
 return newTurn;
}

void playerRender(void)
{
 screenColorPut(player.x,player.y,WHITE_BRIGHT,BLACK,'@');
 screenPrint(0,0,"HP: %d/%d",player.hitPoints,player.maxHitPoints);
}

//teleport the player to a specific position (this is usefull to place the
//player in newly created maps or for teleport traps for example)
void playerTeleportTo(int16_t x,int16_t y)
{
 if(mapIsValid(x,y)==true)
 {
  player.x=x;
  player.y=y;
 }
}

//calculate player field of view inside the actual map
void playerCalculateFOV(void)
{
 //reset map field of view from previous turn
 mapResetFOV();
 //loop through all tile in line of site range
 for(int16_t y=player.y-player.losLength;y<=player.y+player.losLength;y++)
 {
  for(int16_t x=player.x-player.losLength;x<=player.x+player.losLength;x++)
  {
   //if the tile is valid, is in line of sight "real" distance and we can
   //trace an unobstructed line from the player position to that tile
   if(mapIsValid(x,y) && distance(player.x,player.y,x,y)<player.losLength &&
     bresenhamLos(player.x,player.y,x,y)==true)
   {
    //mark the tile visible
    tile_t* tile=mapTileAt(x,y);
    tile->visible=true;
    if(tileRememberViewed(tile->type)==true)
    {
     //mark it seen if the tileType_t should be remembered by the player
     //this is usefull to show [for example] walls that are not in sight
     //so the player can see the shape of the map as if the character roughly
     //remember it
     tile->seen=true;
    }
   }
  }
 }
}

//calculate the dijkstra map from the player point of view point of view
void playerCalculateDijkstraMap(void)
{
 mapCalculateDijkstraMap(player.x,player.y);
}

//return the distance from x,y to player.x,player.y
bool playerIsInAttackRange(monster_t* monster,int16_t range)
{
 return distance(monster->x,monster->y,player.x,player.y)<=range;
}

//handle an attack from the player to a monster
void playerAttack(monster_t* monster)
{
 //simple damage formula
 int16_t damage=MAX(0,player.attack-monster->defence);
 if(damage>0)
 {
  //show the attack action
  print("You attack %s for %d damage.\n",monster->name,damage);
  monster->hitPoints-=damage;
  if(monster->hitPoints<=0)
  {
   //show monster death
   print("%s dies.\n",monster->name);
   monster->type=MONSTER_NONE;
  }
 }
 else
 {
  //show attack misses
  print("You attack %s but do no damage.\n",monster->name);
 }
}

//handle an attack from a monster to the player
void playerAttackedBy(monster_t* monster)
{
 //simple damage formula
 int16_t damage=MAX(0,monster->attack-player.defence);
 if(damage>0)
 {
  //show the attack action
  print("%s attacks you for %d damage.\n",monster->name,damage);
  player.hitPoints-=damage;
  if(player.hitPoints<=0)
  {
   //show player death
   print("Your die.\n");
  }
 }
 else
 {
  //show monster misses
  print("%s attacks you but does no damage.\n",monster->name);
 }
}

