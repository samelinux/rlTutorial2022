
#include <stdlib.h>
#include "stateMap.h"
#include "monster.h"
#include "tile.h"
#include "screen.h"
#include "main.h"
#include "map.h"

//handle the in examine map player input
bool stateExamineMapUpdate(player_t* player,char input)
{
 int8_t x=player->examineMapX;
 int8_t y=player->examineMapY;
 switch(input)
 {
  case 27:
   player->state=STATE_MAP;
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
 if(x!=player->examineMapX || y!=player->examineMapY)
 {
  if(mapIsValid(x,y))
  {
   player->examineMapX=x;
   player->examineMapY=y;
  }
 }
 return false;
}

//render the examine map screen
void stateExamineMapRender(player_t* player)
{
 //clear the screen
 screenClear();
 //draw the map
 mapRender(player->examineMapX,player->examineMapY);
 //draw all monsters
 monsterPoolRender(player->examineMapX,player->examineMapY);

 //draw the selection in pure bright white
 screenColorPut(MAP_VIEWPORT_WIDTH/2,MAP_VIEWPORT_HEIGHT/2,
   WHITE_BRIGHT,WHITE_BRIGHT,' ');

 monster_t* monster=monsterPoolAt(player->examineMapX,
   player->examineMapY);
 tile_t* tile=mapTileAt(player->examineMapX,player->examineMapY);

 if(player->examineMapX==player->x && player->examineMapY==player->y)
 {
  //the player is under the selection, draw it with inverted colors
  playerRenderPlayer(player->examineMapX,player->examineMapY,
    BLACK,WHITE_BRIGHT);
 }
 else
 {
  //the player is not under the selection, draw it normally
  playerRenderPlayer(player->examineMapX,player->examineMapY,
    WHITE_BRIGHT,BLACK);
  //if a tile is under the selection
  if(tile!=NULL)
  {
   //if a monster is under the selection draw it with inverted color and print
   //its info
   if(monster!=NULL && tile->visible==true)
   {
    monsterRender(monster,player->examineMapX,player->examineMapY,
         tile->bgColor,monster->color);
   }
   else
   {
    //if the tile is visible draw it with inverted colors and print its info
    if(tile->visible==true || tile->seen==true)
    {
     screenColorPut(MAP_VIEWPORT_WIDTH/2,MAP_VIEWPORT_HEIGHT/2,
       tile->bgColor,tile->fgColor,tile->glyph);
    }
   }
  }
 }

 int16_t infoY=MAP_VIEWPORT_HEIGHT;
 if(tile!=NULL)
 {
  if(tile->visible==true || tile->seen==true)
  {
   screenPrint(0,infoY++,"Tile: %s",tile->name);
  }
  if(player->examineMapX==player->x && player->examineMapY==player->y)
  {
   screenPrint(0,infoY++,"You");
  }
  if(monster!=NULL && tile->visible==true)
  {
   screenPrint(0,infoY++,"Monster: %s",monster->name);
  }
 }

 //print player stats
 int8_t statX=MAP_VIEWPORT_WIDTH+1;
 screenPrint(statX,0,"HP: %d/%d",player->hitPoints,player->maxHitPoints);
 screenPrint(statX,1,"Attack: %d",player->attack);
 screenPrint(statX,2,"Defence: %d",player->defence);

}

