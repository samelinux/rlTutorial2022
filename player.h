
#ifndef _player_
#define _player_

#include <stdint.h>
#include <stdbool.h>
#include "monster.h"

struct player_t
{
 int16_t x;
 int16_t y;
 int16_t losLength;
 int8_t maxHitPoints;
 int8_t hitPoints;
 int8_t defence;
 int8_t attack;
};
typedef struct player_t player_t;

void playerInit(int16_t x,int16_t y);

bool playerHandleInput(char input);

void playerRender(void);

void playerTeleportTo(int16_t x,int16_t y);

void playerCalculateFOV(void);

void playerCalculateDijkstraMap(void);

bool playerIsInAttackRange(monster_t* monster,int16_t range);

void playerAttack(monster_t* monster);

void playerAttackedBy(monster_t* monster);

#endif

