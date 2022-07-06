
#include "monster.h"

//setup a monster_t structure
void monsterInit(monster_t* monster,monsterType_t type)
{
 int16_t x=0;
 int16_t y=0;
 monster->type=type;
 //get a random walkable position and place the monster there
 mapRandomWalkablePosition(&x,&y);
 monster->x=x;
 monster->y=y;
 //get standard values for monsterType_t
 monster->glyph=monsterGlyph(type);
 monster->color=monsterColor(type);
}

//return each monsterType_t character representation
char monsterGlyph(monsterType_t type)
{
 switch(type)
 {
  case MONSTER_MAX:
  case MONSTER_NONE: return ' ';
  case MONSTER_RAT: return 'r';
 }
 return ' ';
}

//return each monsterType_t color
int8_t monsterColor(monsterType_t type)
{
 switch(type)
 {
  case MONSTER_MAX:
  case MONSTER_NONE: return BLACK;
  case MONSTER_RAT: return RED;
 }
 return BLACK;
}
