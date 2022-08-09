
#ifndef _item_
#define _item_

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

#define ITEM_POOL_SIZE (32)
#define ITEM_NAME_LENGTH (32)
#define ITEM_PILE_GLYPH ('%')
#define ITEM_PILE_COLOR (WHITE)

enum itemType_t
{
 ITEM_NONE=0,
 ITEM_HEALTH_POTION,
 ITEM_LIGHTNING_SCROLL,
 ITEM_CONFUSION_SCROLL,
 ITEM_FIREBALL_SCROLL,
 ITEM_DAGGER,
 ITEM_SWORD,
 ITEM_LEATHER_ARMOR,
 ITEM_CHAIN_MAIL,
 ITEM_MAX,
};
typedef enum itemType_t itemType_t;

enum equipmentType_t
{
 EQUIPMENT_WEAPON,
 EQUIPMENT_ARMOR,
 EQUIPMENT_MAX,
 EQUIPMENT_NONE,
};
typedef enum equipmentType_t equipmentType_t;

struct item_t
{
 itemType_t type;
 equipmentType_t equipmentType;
 char name[ITEM_NAME_LENGTH];
 int16_t x;
 int16_t y;
 char glyph;
 int16_t color;
 int8_t attackBonus;
 int8_t defenceBonus;
};
typedef struct item_t item_t;

void itemInit(item_t* item,itemType_t type,int16_t x,int16_t y);

void itemRender(item_t* item,int16_t fromX,int16_t fromY,
  int16_t fgColor,int16_t bgColor);

equipmentType_t itemEquipmentType(itemType_t type);

char* itemName(itemType_t type);

char itemGlyph(itemType_t type);

int8_t itemColor(itemType_t type);

int8_t itemAttackBonus(itemType_t type);

int8_t itemDefenceBonus(itemType_t type);

bool itemUse(item_t* item,int16_t x,int16_t y);

void itemPoolInit(void);

void itemPoolDeinit(void);

bool itemPoolSave(FILE* aFile);

bool itemPoolLoad(FILE* aFile);

void itemPoolAdd(itemType_t type,int16_t x,int16_t y);

void itemPoolSpawn(void);

int16_t itemPoolCountAt(int16_t x,int16_t y);

item_t* itemPoolAt(int16_t x,int16_t y,int index);

void itemPoolRender(int16_t fromX,int16_t fromY);

void itemConsume(item_t* item);

#endif

