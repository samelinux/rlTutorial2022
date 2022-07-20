
#ifndef _player_
#define _player_

#include <stdint.h>
#include <stdbool.h>
#include "monster.h"

#define JOURNAL_LENGTH (100)
#define JOURNAL_LINE_LENGTH (80)

enum state_t
{
 STATE_MAIN_MENU=0,
 STATE_MAP,
 STATE_EXAMINE_MAP,
 STATE_JOURNAL,
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
 char journal[JOURNAL_LENGTH][JOURNAL_LINE_LENGTH];
 int16_t journalIndex;
 int16_t examineMapX;
 int16_t examineMapY;
};
typedef struct player_t player_t;

void playerInit(void);

void playerDeinit(void);

void playerNewGame(void);

bool playerUpdate(char input);

void playerRender(void);

void playerRenderPlayer(int16_t fromX,int16_t fromY,
  int16_t fgColor,int16_t bgColor);

void playerLog(char* format,...);

void playerTeleportTo(int16_t x,int16_t y);

void playerCalculateFOV(void);

void playerCalculateDijkstraMap(void);

bool playerIsInAttackRange(monster_t* monster,int16_t range);

void playerAttack(monster_t* monster);

void playerAttackedBy(monster_t* monster);

#endif

