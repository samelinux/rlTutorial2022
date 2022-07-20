
#ifndef _player_
#define _player_

#include <stdint.h>
#include <stdbool.h>
#include "monster.h"

enum state_t
{
 STATE_MAIN_MENU=0,
 STATE_MAP,
 STATE_GAME_OVER,
 STATE_MAX,
};
typedef enum state_t state_t;

struct player_t
{
 state_t state;
 int16_t x;
 int16_t y;
 int16_t losLength;
 int8_t maxHitPoints;
 int8_t hitPoints;
 int8_t defence;
 int8_t attack;
};
typedef struct player_t player_t;

void playerInit(void);

void playerDeinit(void);

void playerNewGame(void);

bool playerUpdate(char input);

void playerRender(void);

void playerTeleportTo(int16_t x,int16_t y);

void playerCalculateFOV(void);

void playerCalculateDijkstraMap(void);

bool playerIsInAttackRange(monster_t* monster,int16_t range);

void playerAttack(monster_t* monster);

void playerAttackedBy(monster_t* monster);

#endif

