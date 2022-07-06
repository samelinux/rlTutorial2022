
#ifndef _player_
#define _player_

#include <stdint.h>
#include "map.h"

struct player_t
{
 int16_t x;
 int16_t y;
};
typedef struct player_t player_t;

void playerInit(int16_t x,int16_t y);

void playerHandleInput(char input);

void playerRender(void);

void playerTeleportTo(int16_t x,int16_t y);

#endif

