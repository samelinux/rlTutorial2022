
#include <string.h>
#include <stdlib.h>
#include "stateGameOver.h"
#include "stateMap.h"
#include "screen.h"
#include "player.h"
#include "disk.h"

//handle the game over screen input
bool stateGameOverUpdate(char input)
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

//render the game over screen
void stateGameOverRender(void)
{
 //this is an hack to have the map screen updated to the last action
 stateMapRender();
 //for now lets just print a "Dark Souls style" death screen
 screenPrint((screenWidth-strlen("You died"))/2,screenHeight/2,"You died");
 screenPrint(screenWidth-strlen("Press enter to continue")-1,screenHeight,
   "Press enter to continue");
}

