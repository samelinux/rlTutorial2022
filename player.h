
#ifndef _player_
#define _player_

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "item.h"
#include "monster.h"

#define JOURNAL_LENGTH (100)
#define JOURNAL_LINE_LENGTH (80)
#define BACKPACK_LENGTH (10)

enum state_t
{
 STATE_MAIN_MENU=0,
 STATE_CONFIRM_NEW_GAME,
 STATE_MAP,
 STATE_BACKPACK,
 STATE_EXAMINE_MAP,
 STATE_CHOOSE_TARGET,
 STATE_JOURNAL,
 STATE_GAME_OVER,
 STATE_MAX,
};
typedef enum state_t state_t;

struct player_t
{
 state_t state;
 int16_t mainMenuSelection;
 int16_t x;
 int16_t y;
 int64_t turn;
 int16_t losLength;
 int8_t maxHitPoints;
 int8_t hitPoints;
 int8_t defence;
 int8_t attack;
 char journal[JOURNAL_LENGTH][JOURNAL_LINE_LENGTH];
 int16_t journalIndex;
 item_t backpack[BACKPACK_LENGTH];
 bool backpackSelected;
 int16_t backpackIndex;
 int16_t backpackStart;
 int16_t nearbyIndex;
 int16_t nearbyStart;
 int16_t examineX;
 int16_t examineY;
 item_t* itemToUse;
 int8_t dungeonLevel;
};
typedef struct player_t player_t;

extern player_t player;

void playerInit(void);

void playerDeinit(void);

bool playerSave(FILE* aFile);

bool playerLoad(FILE* aFile);

void playerNewGame(void);

void playerGotoState(state_t newState);

bool playerUpdate(char input);

void playerRender(void);

void playerRenderPlayer(int16_t fromX,int16_t fromY,
  int16_t fgColor,int16_t bgColor);

void playerCheckDeath();

void playerLog(char* format,...);

void playerTeleportTo(int16_t x,int16_t y);

void playerCalculateFOV(void);

void playerCalculateDijkstraMap(void);

bool playerIsInAttackRange(monster_t* monster,int16_t range);

void playerAttack(monster_t* monster);

void playerAttackedBy(monster_t* monster);

int16_t playerBackpackCount(void);

void playerPackBackpack(void);

void playerPickup(item_t* item);

bool playerUseSelectedItem(void);

void playerDropSelectedItem(void);

#endif

