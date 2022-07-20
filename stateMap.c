
#include <stdlib.h>
#include "stateMap.h"
#include "monster.h"
#include "tile.h"
#include "screen.h"
#include "main.h"
#include "map.h"

//handle the in map player input
bool stateMapUpdate(player_t* player,char input)
{
 bool newTurn=false;
 if(player->hitPoints>0)
 {
  tile_t* toTile=NULL;
  int8_t x=player->x;
  int8_t y=player->y;
  //each action can change newTurn to true to signal the main loop a net turn
  //has passed. You may want some actoins to not consume a turn, in that case
  //just leave newTurn to false
  switch(input)
  {
   case 'q':
    //close the program
    mainQuit();
    break;
   case '5':
   case '.':
    //wait a turn
    newTurn=true;
    break;
   case '7':
   case 'y':
    //up left
    y-=1;
    x-=1;
    newTurn=true;
    break;
   case 'u':
   case '9':
    //up right
    y-=1;
    x+=1;
    newTurn=true;
    break;
   case '4':
   case 'h':
    //left
    x-=1;
    newTurn=true;
    break;
   case '2':
   case 'j':
    //down
    y+=1;
    newTurn=true;
    break;
   case '8':
   case 'k':
    //up
    y-=1;
    newTurn=true;
    break;
   case '6':
   case 'l':
    //right
    x+=1;
    newTurn=true;
    break;
   case '1':
   case 'b':
    //down left
    y+=1;
    x-=1;
    newTurn=true;
    break;
   case '3':
   case 'n':
    //down right
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
     player->x=x;
     player->y=y;
    }
   }
  }
 }
 //return the newTurn value to the main loop so monsters can take a turn when
 //the player take a turn
 return newTurn;
}

//render the in map screen
void stateMapRender(player_t* player)
{
 //clear the screen
 screenClear();
 //calculate new field of view
 playerCalculateFOV();
 //draw the map
 mapRender();
 //draw all monsters
 monsterPoolRender();
 //render the player and his info
 screenColorPut(player->x,player->y,WHITE_BRIGHT,BLACK,'@');
 screenPrint(0,0,"HP: %d/%d",player->hitPoints,player->maxHitPoints);
}

