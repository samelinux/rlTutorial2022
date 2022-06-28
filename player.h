
#ifndef _player_
#define _player_

struct player_t
{
 int x;
 int y;
};
typedef struct player_t player_t;

void playerInit(player_t* player);

void playerHandleInput(player_t* player,char input);

#endif

