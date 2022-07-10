
#ifndef _tile_
#define _tile_

#include <stdint.h>
#include <stdbool.h>
#include "screen.h"

enum tileType_t
{
 TILE_NONE=0,
 TILE_FLOOR,
 TILE_WALL,
 TILE_MAX,
};
typedef enum tileType_t tileType_t;

struct tile_t
{
 tileType_t type;
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

char tileGlyph(tileType_t type);

int8_t tileFGColor(tileType_t type);

int8_t tileBGColor(tileType_t type);

bool tileWalkable(tileType_t type);

bool tileBlockFOV(tileType_t type);

bool tileRememberViewed(tileType_t type);

#endif

