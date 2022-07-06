
#ifndef _monster_
#define _monster_

#include <stdint.h>
#include "map.h"
#include "screen.h"

enum monsterType_t
{
 MONSTER_NONE=0,
 MONSTER_RAT,
 MONSTER_MAX,
};
typedef enum monsterType_t monsterType_t;

struct monster_t
{
 monsterType_t type;
 int16_t x;
 int16_t y;
 char glyph;
 int8_t color;
};
typedef struct monster_t monster_t;

void monsterInit(monster_t* monster,monsterType_t type);

char monsterGlyph(monsterType_t type);

int8_t monsterColor(monsterType_t type);

#endif

