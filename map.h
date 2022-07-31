
#ifndef _map_
#define _map_

#include <stdio.h>
#include <stdint.h>
#include "tile.h"

#define MAP_WIDTH (80)
#define MAP_HEIGHT (24)
#define MAP_VIEWPORT_WIDTH (60)
#define MAP_VIEWPORT_HEIGHT (20)

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

void mapInit(void);

void mapDeinit(void);

bool mapSave(FILE* aFile);

bool mapLoad(FILE* aFile);

void mapGenerate(mapType_t type);

bool mapIsValid(int16_t x,int16_t y);

void mapRandomWalkablePosition(int16_t* x,int16_t* y);

bool mapIsConnected(void);

void mapRender(int16_t fromX,int16_t fromY);

tile_t* mapTileAt(int16_t x,int16_t y);

void mapResetFOV(void);

void mapResetDijkstraMap(void);

void mapCalculateDijkstraMap(int16_t x,int16_t y);

int16_t mapDijkstraAt(int16_t x,int16_t y);

#endif

