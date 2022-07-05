
#ifndef _monsters_
#define _monsters_

#include <string.h>
#include "monster.h"
#include "screen.h"

#define MONSTERS_SIZE (32)

void monstersInit(void);

void monstersAdd(monster_t monster);

void monstersRender(void);

#endif

