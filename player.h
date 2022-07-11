
#ifndef _player_
#define _player_

#include <stdint.h>
#include "bresenham.h"
#include "macro.h"
#include "map.h"

struct player_t
{
 int16_t x;
 int16_t y;
 int16_t losLength;
};
typedef struct player_t player_t;

void playerInit(int16_t x,int16_t y);

bool playerHandleInput(char input);

void playerRender(void);

void playerTeleportTo(int16_t x,int16_t y);

void playerCalculateFOV(void);

#endif

