
#ifndef _monster_
#define _monster_

#include <stdint.h>

#define MONSTER_POOL_SIZE (32)
#define MONSTER_NAME_LENGTH (16)

enum monsterType_t
{
 MONSTER_NONE=0,
 MONSTER_RAT,
 MONSTER_ORC,
 MONSTER_TROL,
 MONSTER_MAX,
};
typedef enum monsterType_t monsterType_t;

enum monsterAI_t
{
 MONSTER_AI_NONE=0,
 MONSTER_AI_HOSTILE,
 MONSTER_AI_MAX,
};
typedef enum monsterAI_t monsterAI_t;

struct monster_t
{
 monsterType_t type;
 char name[MONSTER_NAME_LENGTH];
 int16_t x;
 int16_t y;
 char glyph;
 int8_t color;
 int8_t maxHitPoints;
 int8_t hitPoints;
 int8_t defence;
 int8_t attack;
 monsterAI_t ai;
};
typedef struct monster_t monster_t;

void monsterInit(monster_t* monster,monsterType_t type);

char* monsterName(monsterType_t type);

char monsterGlyph(monsterType_t type);

int8_t monsterColor(monsterType_t type);

int8_t monsterMaxHitPoints(monsterType_t type);

int8_t monsterDefence(monsterType_t type);

int8_t monsterAttack(monsterType_t type);

monsterAI_t monsterAI(monsterType_t type);

void monsterPoolInit(void);

void monsterPoolAdd(monsterType_t type);

void monsterPoolSpawn(int16_t maxMonsters);

monster_t* monsterPoolAt(int16_t x,int16_t y);

void monsterPoolRender(void);

void monsterPoolHandleTurn(void);

void monsterBestMoveToReachPlayer(monster_t* monster);

#endif

