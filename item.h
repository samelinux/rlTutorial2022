
#ifndef _item_
#define _item_

typedef enum itemType_t itemType_t;
typedef struct item_t item_t;

#include <stdint.h>

#define ITEM_POOL_SIZE (32)
#define ITEM_NAME_LENGTH (16)
#define ITEM_PILE_GLYPH ('%')
#define ITEM_PILE_COLOR (WHITE)

enum itemType_t
{
 ITEM_NONE=0,
 ITEM_HEALTH_POTION,
 ITEM_MAX,
};

struct item_t
{
 itemType_t type;
 char name[ITEM_NAME_LENGTH];
 int16_t x;
 int16_t y;
 char glyph;
 int16_t color;
};

void itemInit(item_t* item,itemType_t type,int16_t x,int16_t y);

void itemRender(item_t* item,int16_t fromX,int16_t fromY,
  int16_t fgColor,int16_t bgColor);

char* itemName(itemType_t type);

char itemGlyph(itemType_t type);

int8_t itemColor(itemType_t type);

void itemUse(item_t* item,int16_t x,int16_t y);

void itemPoolInit(void);

void itemPoolDeinit(void);

void itemPoolAdd(itemType_t type,int16_t x,int16_t y);

void itemPoolSpawn(int16_t maxItems);

int16_t itemPoolCountAt(int16_t x,int16_t y);

item_t* itemPoolAt(int16_t x,int16_t y,int index);

void itemPoolRender(int16_t fromX,int16_t fromY);

#endif

