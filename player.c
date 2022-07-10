
#include "player.h"

//declare a player
player_t player;

//setup a player_t structure
void playerInit(int16_t x,int16_t y)
{
 player.x=x;
 player.y=y;
 player.losLength=4;
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
 screenColorPut(player.x,player.y,WHITE_BRIGHT,BLACK,'@');
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

