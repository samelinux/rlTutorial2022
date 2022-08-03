
#include <string.h>
#include "tile.h"
#include "screen.h"
#include "map.h"

//setup a tile_t structure
void tileInit(tile_t* tile,tileType_t type)
{
 tile->type=type;
 //get standard values for tileType_t
 memset(tile->name,0,sizeof(char)*TILE_NAME_LENGTH);
 strncpy(tile->name,tileName(type),TILE_NAME_LENGTH);
 tile->glyph=tileGlyph(type);
 tile->fgColor=tileFGColor(type);
 tile->bgColor=tileBGColor(type);
 tile->walkable=tileWalkable(type);
 tile->blockFOV=tileBlockFOV(type);
 tile->visible=false;
 tile->seen=false;
}

void tileRender(tile_t* tile,int16_t x,int16_t y,int16_t fromX,int16_t fromY,
  int16_t fgColor,int16_t bgColor)
{
 int16_t screenX=x+MAP_VIEWPORT_WIDTH/2-fromX;
 int16_t screenY=y+MAP_VIEWPORT_HEIGHT/2-fromY;
 if(screenX>=0 && screenX<MAP_VIEWPORT_WIDTH &&
   screenY>=0 && screenY<MAP_VIEWPORT_HEIGHT)
 {
  screenColorPut(screenX,screenY,fgColor,bgColor,tile->glyph);
 }
}

char* tileName(tileType_t type)
{
 switch(type)
 {
  case TILE_MAX:
  case TILE_NONE: return "no name";
  case TILE_FLOOR: return "floor";
  case TILE_WALL: return "wall";
  case TILE_STAIR_DOWN: return "stair down";
  case TILE_STAIR_UP: return "stair up";
 }
 return "no name";
}

//return each tileType_t character representation
char tileGlyph(tileType_t type)
{
 switch(type)
 {
  case TILE_MAX:
  case TILE_NONE: return '?';
  case TILE_FLOOR: return '.';
  case TILE_WALL: return '#';
  case TILE_STAIR_DOWN: return '>';
  case TILE_STAIR_UP: return '<';
 }
 return '?';
}

//return each tileType_t foreground color
int8_t tileFGColor(tileType_t type)
{
 switch(type)
 {
  case TILE_MAX:
  case TILE_NONE: return BLACK;
  case TILE_FLOOR: return WHITE;
  case TILE_WALL: return WHITE;
  case TILE_STAIR_DOWN: return WHITE;
  case TILE_STAIR_UP: return WHITE;
 }
 return BLACK;
}

//return each tileType_t background color
int8_t tileBGColor(tileType_t type)
{
 switch(type)
 {
  case TILE_MAX:
  case TILE_NONE: return BLACK;
  case TILE_FLOOR: return BLACK;
  case TILE_WALL: return BLACK;
  case TILE_STAIR_DOWN: return BLACK;
  case TILE_STAIR_UP: return BLACK;
 }
 return BLACK;
}

//return true for each tileType_t that can be walked, false otherwise
bool tileWalkable(tileType_t type)
{
 switch(type)
 {
  case TILE_MAX:
  case TILE_NONE: return false;
  case TILE_FLOOR: return true;
  case TILE_WALL: return false;
  case TILE_STAIR_DOWN: return true;
  case TILE_STAIR_UP: return true;
 }
 return false;
}

//return true for each tileType_t that blocks field of view, false otherwise
bool tileBlockFOV(tileType_t type)
{
 switch(type)
 {
  case TILE_MAX:
  case TILE_NONE: return true;
  case TILE_FLOOR: return false;
  case TILE_WALL: return true;
  case TILE_STAIR_DOWN: return false;
  case TILE_STAIR_UP: return false;
 }
 return true;
}

//return true for all tileType_t that should be remembered when seen by the
//player [see playerCalculateFOV function in player.c for more datails]
bool tileRememberViewed(tileType_t type)
{
 switch(type)
 {
  case TILE_MAX:
  case TILE_NONE: return false;
  case TILE_FLOOR: return false;
  case TILE_WALL: return true;
  case TILE_STAIR_DOWN: return true;
  case TILE_STAIR_UP: return true;
 }
 return false;
}

