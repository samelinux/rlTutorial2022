
#include <stdlib.h>
#include "stateMap.h"
#include "stateBackpack.h"
#include "item.h"
#include "monster.h"
#include "tile.h"
#include "screen.h"
#include "main.h"
#include "map.h"
#include "player.h"

//handle the in map player input
bool stateMapUpdate(char input)
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
   case 'q':
    //close the program
    mainQuit();
    break;
   case 'x':
    //examine the map
    player.examineX=player.x;
    player.examineY=player.y;
    player.state=STATE_EXAMINE_MAP;
    break;
   case 'i':
    //go to the backpack
    player.backpackSelected=true;
    player.backpackIndex=0;
    player.backpackStart=0;
    player.nearbyIndex=0;
    player.nearbyStart=0;
    player.state=STATE_BACKPACK;
    break;
   case ',':
   case 'g':
    //pickup items
    player.backpackSelected=false;
    player.backpackIndex=0;
    player.backpackStart=0;
    player.nearbyIndex=0;
    player.nearbyStart=0;
    player.state=STATE_BACKPACK;
   break;
   case 'J':
    //read the full journal
    player.journalIndex=JOURNAL_LENGTH-screenHeight+1;
    if(player.journalIndex<0)
    {
     player.journalIndex=0;
    }
    player.state=STATE_JOURNAL;
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
  //if the player moved
  if(x!=player.x || y!=player.y)
  {
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
 }
 //return the newTurn value to the main loop so monsters can take a turn when
 //the player take a turn
 return newTurn;
}

//render the in map screen
void stateMapRender(void)
{
 //clear the screen
 screenClear();
 //calculate new field of view
 playerCalculateFOV();
 //draw the map
 mapRender(player.x,player.y);
 //draw all items
 itemPoolRender(player.x,player.y);
 //draw all monsters
 monsterPoolRender(player.x,player.y);
 //render the player
 screenColorPut(MAP_VIEWPORT_WIDTH/2,MAP_VIEWPORT_HEIGHT/2,
   WHITE_BRIGHT,BLACK,'@');

 //print player stats
 int8_t statX=MAP_VIEWPORT_WIDTH+1;
 screenPrint(statX,0,"Turn: %lld",player.turn);
 screenPrint(statX,1,"HP: %d/%d",player.hitPoints,player.maxHitPoints);
 screenPrint(statX,2,"Attack: %d",player.attack);
 screenPrint(statX,3,"Defence: %d",player.defence);

 //print the last journal lines
 int8_t maxLines=screenHeight-MAP_VIEWPORT_HEIGHT;
 int8_t start=JOURNAL_LENGTH-maxLines;
 if(start<0)
 {
  start+=JOURNAL_LENGTH;
 }
 for(int8_t i=0;i<maxLines;i++)
 {
  int8_t line=(start+i)%JOURNAL_LENGTH;
  screenPrint(0,MAP_VIEWPORT_HEIGHT+i,"%s",player.journal[line]);
 }
}

