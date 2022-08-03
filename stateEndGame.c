
#include <string.h>
#include <stdlib.h>
#include "stateEndGame.h"
#include "stateMap.h"
#include "screen.h"
#include "player.h"
#include "disk.h"

//handle the end game screen input
bool stateEndGameUpdate(char input)
{
 switch(input)
 {
  case 10:
   //delete the game files
   diskDeleteGame();
   //clear player structure and move him to the main menu
   playerInit();
   break;
 }
 return false;
}

//render the end game screen
void stateEndGameRender(void)
{
 screenClear();
 //for now lets just print a "win" message
 screenPrint((screenWidth-strlen("You exited the dungeon alive!"))/2,screenHeight/2,"You exited the dungeon alive!");
 screenPrint(screenWidth-strlen("Press enter to continue")-1,screenHeight,
   "Press enter to continue");
}

