
#ifndef _map_
#define _map_

#include <string.h>
#include <stdint.h>
#include "tile.h"
#include "screen.h"
#include "mapSample.h"
#include "mapCave.h"
#include "player.h"

#define MAP_WIDTH (80)
#define MAP_HEIGHT (24)

enum mapType_t
{
 MAP_NONE=0,
 MAP_EMPTY,
 MAP_SAMPLE,
 MAP_CAVE,
 MAP_MAX,
};
typedef enum mapType_t mapType_t;

struct map_t
{
 mapType_t type;
 tile_t tiles[MAP_WIDTH*MAP_HEIGHT];
};
typedef struct map_t map_t;

void mapInit(mapType_t type);

bool mapIsValid(int16_t x,int16_t y);

void mapRandomWalkablePosition(int16_t* x,int16_t* y);

bool mapIsConnected(void);

void mapRender();

tile_t* mapTileAt(int16_t x,int16_t y);

#endif

