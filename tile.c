
#include "tile.h"

//setup a tile_t structure
void tileInit(tile_t* tile,tileType_t type)
{
 tile->type=type;
 //get standard values for tileType_t
 tile->glyph=tileGlyph(type);
 tile->fgColor=tileFGColor(type);
 tile->bgColor=tileBGColor(type);
 tile->walkable=tileWalkable(type);
 tile->blockFOV=tileBlockFOV(type);
 tile->visible=false;
 tile->seen=false;
}

//return each tileType_t character representation
char tileGlyph(tileType_t type)
{
 switch(type)
 {
  case TILE_MAX:
  case TILE_NONE: return ' ';
  case TILE_FLOOR: return '.';
  case TILE_WALL: return '#';
 }
 return ' ';
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
 }
 return false;
}

