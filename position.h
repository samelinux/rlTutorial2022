
#ifndef _position_
#define _position_

#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>

struct position_t
{
 int16_t x;
 int16_t y;
};
typedef struct position_t position_t;

#define POSITION(X,Y) ((position_t){.x=(X),.y=(Y)})

position_t positionXYDistances(position_t p0,position_t p1);

uint64_t positionDistance(position_t p0,position_t p1);

position_t positionSum(position_t p0,position_t p1);

bool positionEquals(position_t p0,position_t p1);

#endif

