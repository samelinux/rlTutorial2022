
#include <string.h>
#include <stdlib.h>
#include "stateGameOver.h"
#include "screen.h"

//handle the game over screen input
bool stateGameOverUpdate(player_t* player,char input)
{
 switch(input)
 {
  case 10:
   //move the player to the main menu
   player->state=STATE_MAIN_MENU;
   break;
 }
 return false;
}

//render the game over screen
void stateGameOverRender(player_t* player)
{
 //we do not need to use player for now, avoid unused variable compile error
 (void)player;
 //for now lets just print a "Dark Souls style" death screen
 screenPrint((screenWidth-strlen("You died"))/2,screenHeight/2,"You died");
 screenPrint(screenWidth-strlen("Press enter to continue")-1,screenHeight,
   "Press enter to continue");
}

