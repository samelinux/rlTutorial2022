
#include <string.h>
#include <stdlib.h>
#include "stateMainMenu.h"
#include "screen.h"
#include "main.h"
#include "map.h"

//handle the main menu input
bool stateMainMenuUpdate(player_t* player,char input)
{
 switch(input)
 {
  case 'q':
   //close the program
   mainQuit();
   break;
  case 10:
   //setup the player for a new game
   playerNewGame();
   //generate a new map
   mapGenerate(MAP_CAVE);
   //move the player to the map state
   player->state=STATE_MAP;
   break;
 }
 return false;
}

//draw the main menu screen
void stateMainMenuRender(player_t* player)
{
 (void)player;
 screenClear();
 //for now lets just print a basic welcome screen
 screenPrint((screenWidth-strlen("Welcome to rlTutorial"))/2,screenHeight/2,
   "Welcome to rlTutorial");
 screenPrint(screenWidth-strlen("Press enter to continue or 'q' to quit")-1,
   screenHeight,"Press enter to continue or 'q' to quit");
}

