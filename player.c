
#include "player.h"

//declare a player
player_t player;

//setup a player_t structure
void playerInit(int16_t x,int16_t y)
{
 player.x=x;
 player.y=y;
}

//handle one input from the player
void playerHandleInput(char input)
{
 tile_t* toTile=NULL;
 int8_t x=player.x;
 int8_t y=player.y;
 switch(input)
 {
  case 'h':
   x-=1;
   break;
  case 'j':
   y+=1;
   break;
  case 'k':
   y-=1;
   break;
  case 'l':
   x+=1;
   break;
 }
 //if a tile exists at the new location [avoid goind off the map boundaries]
 if((toTile=mapTileAt(x,y))!=NULL)
 {
  //if the tile is walkable
  if(toTile->walkable)
  {
   player.x=x;
   player.y=y;
  }
 }
}

void playerRender(void)
{
 screenPut(player.x,player.y,'@');
}

