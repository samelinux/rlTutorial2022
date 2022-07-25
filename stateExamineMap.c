
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
 int8_t x=player.examineMapX;
 int8_t y=player.examineMapY;
 switch(input)
 {
  case 27:
   player.state=STATE_MAP;
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
 if(x!=player.examineMapX || y!=player.examineMapY)
 {
  if(mapIsValid(x,y))
  {
   player.examineMapX=x;
   player.examineMapY=y;
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
 mapRender(player.examineMapX,player.examineMapY);
 //draw all items
 itemPoolRender(player.examineMapX,player.examineMapY);
 //draw all monsters
 monsterPoolRender(player.examineMapX,player.examineMapY);

 //draw the selection in pure bright white
 screenColorPut(MAP_VIEWPORT_WIDTH/2,MAP_VIEWPORT_HEIGHT/2,
   WHITE_BRIGHT,WHITE_BRIGHT,' ');

 //load tile info/monster/items
 monster_t* monster=monsterPoolAt(player.examineMapX,
   player.examineMapY);
 tile_t* tile=mapTileAt(player.examineMapX,player.examineMapY);
 int16_t itemCount=itemPoolCountAt(player.examineMapX,player.examineMapY);
 item_t* item=itemPoolAt(player.examineMapX,player.examineMapY,0);

 if(player.examineMapX==player.x && player.examineMapY==player.y)
 {
  //the player is under the selection, draw it with inverted colors
  playerRenderPlayer(player.examineMapX,player.examineMapY,
    BLACK,WHITE_BRIGHT);
 }
 else
 {
  //the player is not under the selection, draw it normally
  playerRenderPlayer(player.examineMapX,player.examineMapY,
    WHITE_BRIGHT,BLACK);
  //if a tile is under the selection
  if(tile!=NULL)
  {
   //if a monster is under the selection draw it with inverted color and print
   //it
   if(monster!=NULL && tile->visible==true)
   {
    monsterRender(monster,player.examineMapX,player.examineMapY,
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
      screenColorPut(MAP_VIEWPORT_WIDTH/2,MAP_VIEWPORT_HEIGHT/2,
        tile->bgColor,tile->fgColor,tile->glyph);
     }
    }
    else
    {
     //if there are some item/items print it/'some'
     if(itemCount>1)
     {
      screenColorPut(MAP_VIEWPORT_WIDTH/2,MAP_VIEWPORT_HEIGHT/2,
        tile->bgColor,ITEM_PILE_COLOR,ITEM_PILE_GLYPH);
     }
     else
     {
      screenColorPut(MAP_VIEWPORT_WIDTH/2,MAP_VIEWPORT_HEIGHT/2,
        tile->bgColor,item->color,item->glyph);
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
  if(player.examineMapX==player.x && player.examineMapY==player.y)
  {
   //if the player is on that tile
   screenPrint(0,infoY++,"You");
  }
  if(monster!=NULL && tile->visible==true)
  {
   //any monster in that tile
   screenPrint(0,infoY++,"Monster: %s",monster->name);
  }
  if(itemCount>0)
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
 screenPrint(statX,0,"HP: %d/%d",player.hitPoints,player.maxHitPoints);
 screenPrint(statX,1,"Attack: %d",player.attack);
 screenPrint(statX,2,"Defence: %d",player.defence);

}

