
#ifndef _tile_
#define _tile_

#include <stdint.h>
#include <stdbool.h>

#define TILE_NAME_LENGTH (16)

enum tileType_t
{
 TILE_NONE=0,
 TILE_FLOOR,
 TILE_WALL,
 TILE_STAIR_DOWN,
 TILE_STAIR_UP,
 TILE_MAX,
};
typedef enum tileType_t tileType_t;

struct tile_t
{
 tileType_t type;
 char name[TILE_NAME_LENGTH];
 char glyph;
 int8_t fgColor;
 int8_t bgColor;
 bool walkable;
 bool blockFOV;
 bool visible;
 bool seen;
};
typedef struct tile_t tile_t;

void tileInit(tile_t* tile,tileType_t type);

void tileRender(tile_t* tile,int16_t x,int16_t y,int16_t fromX,int16_t fromY,
  int16_t fgColor,int16_t bgColor);

char* tileName(tileType_t type);

char tileGlyph(tileType_t type);

int8_t tileFGColor(tileType_t type);

int8_t tileBGColor(tileType_t type);

bool tileWalkable(tileType_t type);

bool tileBlockFOV(tileType_t type);

bool tileRememberViewed(tileType_t type);

#endif

