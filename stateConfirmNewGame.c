
#include <string.h>
#include <stdlib.h>
#include "stateMainMenu.h"
#include "screen.h"
#include "main.h"
#include "map.h"
#include "player.h"
#include "disk.h"

//handle the Confirm new game input
bool stateConfirmNewGameUpdate(char input)
{
 switch(input)
 {
  case 27:
   playerGotoState(STATE_MAIN_MENU);
   break;
  case 10:
   diskDeleteGame();
   //setup the player for a new game
   playerNewGame();
   break;
 }
 return false;
}

//draw the Confirm new game screen
void stateConfirmNewGameRender(void)
{
 screenClear();
 screenPrint(
   (screenWidth-strlen("Are you sure you want to start a new game?"))/2,
   screenHeight/2,"Are you sure you want to start a new game?");

 screenPrint(screenWidth-strlen("Press enter to continue or ESC to go back")-1,
   screenHeight,"Press enter to continue or ESC to go back");
}

