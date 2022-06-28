
#include "player.h"

//setup a player_t structure
void playerInit(player_t* player)
{
 player->x=0;
 player->y=0;
}

//handle one input from the player
void playerHandleInput(player_t* player,char input)
{
 switch(input)
 {
  case 'h':
   player->x-=1;
   break;
  case 'j':
   player->y+=1;
   break;
  case 'k':
   player->y-=1;
   break;
  case 'l':
   player->x+=1;
   break;
 }
}

