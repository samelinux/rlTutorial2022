
#include <stdlib.h>
#include "stateMap.h"
#include "monster.h"
#include "tile.h"
#include "screen.h"
#include "main.h"
#include "map.h"
#include "player.h"

//handle the in examine map player input
bool stateExamineMapUpdate(char input)
{
 int8_t x=player.examineX;
 int8_t y=player.examineY;
 switch(input)
 {
  case 27:
   playerGotoState(STATE_MAP);
   break;
  case '7':
  case 'y':
   //up left
   y-=1;
   x-=1;
   break;
  case 'u':
  case '9':
   //up right
   y-=1;
   x+=1;
   break;
  case '4':
  case 'h':
   //left
   x-=1;
   break;
  case '2':
  case 'j':
   //down
   y+=1;
   break;
  case '8':
  case 'k':
   //up
   y-=1;
   break;
  case '6':
  case 'l':
   //right
   x+=1;
   break;
  case '1':
  case 'b':
   //down left
   y+=1;
   x-=1;
   break;
  case '3':
  case 'n':
   //down right
   y+=1;
   x+=1;
   break;
 }
 //if the player moved the selection
 if(x!=player.examineX || y!=player.examineY)
 {
  if(mapIsValid(x,y))
  {
   player.examineX=x;
   player.examineY=y;
  }
 }
 return false;
}

//render the examine map screen
void stateExamineMapRender(void)
{
 //clear the screen
 screenClear();
 //draw the map
 mapRender(player.examineX,player.examineY);
 //draw all items
 itemPoolRender(player.examineX,player.examineY);
 //draw all monsters
 monsterPoolRender(player.examineX,player.examineY);

 //draw the selection in pure bright white
 screenColorPut(MAP_VIEWPORT_WIDTH/2,MAP_VIEWPORT_HEIGHT/2,
   WHITE_BRIGHT,WHITE_BRIGHT,' ');

 //load tile info/monster/items
 monster_t* monster=monsterPoolAt(player.examineX,player.examineY);
 tile_t* tile=mapTileAt(player.examineX,player.examineY);
 int16_t itemCount=itemPoolCountAt(player.examineX,player.examineY);
 item_t* item=itemPoolAt(player.examineX,player.examineY,0);

 if(player.examineX==player.x && player.examineY==player.y)
 {
  //the player is under the selection, draw it with inverted colors
  playerRenderPlayer(player.examineX,player.examineY,BLACK,WHITE_BRIGHT);
 }
 else
 {
  //the player is not under the selection, draw it normally
  playerRenderPlayer(player.examineX,player.examineY,
    WHITE_BRIGHT,BLACK);
  //if a tile is under the selection
  if(tile!=NULL)
  {
   //if a monster is under the selection draw it with inverted color and print
   //it
   if(monster!=NULL && tile->visible==true)
   {
    monsterRender(monster,player.examineX,player.examineY,
         tile->bgColor,monster->color);
   }
   else
   {
    if(itemCount==0)
    {
     //if the tile is visible and there are no items draw it with inverted
     //colors and print its info
     if(tile->visible==true || tile->seen==true)
     {
      tileRender(tile,player.examineX,player.examineY,
        player.examineX,player.examineY,
        tile->bgColor,tile->fgColor);
     }
    }
    else
    {
     //if the tile is visible and there are some item/items print it/'some'
     if(tile->visible==true)
     {
      itemRender(item,player.examineX,player.examineY,
        tile->bgColor,item->color);
     }
    }
   }
  }
 }

 //print any usefull information the player can see on the examined tile
 //
 int16_t infoY=MAP_VIEWPORT_HEIGHT;
 if(tile!=NULL)
 {
  if(tile->visible==true || tile->seen==true)
  {
   //what tile it is
   screenPrint(0,infoY++,"Tile: %s",tile->name);
  }
  if(player.examineX==player.x && player.examineY==player.y)
  {
   //if the player is on that tile
   screenPrint(0,infoY++,"You");
  }
  if(monster!=NULL && tile->visible==true)
  {
   //any monster in that tile
   screenPrint(0,infoY++,"Monster: %s",monster->name);
  }
  if(itemCount>0 && tile->visible==true)
  {
   if(itemCount==1)
   {
    //an item on the tile if it is the only one
    screenPrint(0,infoY++,"Item: %s",item->name);
   }
   else
   {
    //if there are more than one item, just print that there are 'some'
    screenPrint(0,infoY++,"Item: some");
   }
  }
 }

 //print player stats
 int8_t statX=MAP_VIEWPORT_WIDTH+1;
 screenPrint(statX,0,"Turn: %lld",player.turn);
 screenPrint(statX,1,"HP: %d/%d",player.hitPoints,player.maxHitPoints);
 screenPrint(statX,2,"Attack: %d",player.attack);
 screenPrint(statX,3,"Defence: %d",player.defence);

}

