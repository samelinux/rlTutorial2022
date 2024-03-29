
#include <string.h>
#include <stdlib.h>
#include "stateMainMenu.h"
#include "screen.h"
#include "main.h"
#include "map.h"
#include "player.h"
#include "disk.h"

//handle the main menu input
bool stateMainMenuUpdate(char input)
{
 switch(input)
 {
  case 10:
   //return pressed
   switch(player.menuSelection)
   {
    case 0:
     //new game selected
     if(diskCanLoad(PLAYER_SAVE_FILE))
     {
      //confirm the creation of a new game since we already have an ongoing game
      playerGotoState(STATE_CONFIRM_NEW_GAME);
     }
     else
     {
      //setup the player for a new game
      playerNewGame();
     }
     break;
    case 1:
     if(diskCanLoad(PLAYER_SAVE_FILE) && diskLoadGame()==true)
     {
      //move the player to the map state if we manage to load the game
      playerGotoState(STATE_MAP);
     }
     break;
    case 2:
     //quit the game
     mainQuit();
     break;
   }
   break;
  case '8':
  case 'k':
   //up
   player.menuSelection=(player.menuSelection+2)%3;
   if(player.menuSelection==1 && diskCanLoad(PLAYER_SAVE_FILE)==false)
   {
    player.menuSelection--;
   }
   break;
  case '2':
  case 'j':
   //down
   player.menuSelection=(player.menuSelection+1)%3;
   if(player.menuSelection==1 && diskCanLoad(PLAYER_SAVE_FILE)==false)
   {
    player.menuSelection++;
   }
   break;
 }
 return false;
}

//draw the main menu screen
void stateMainMenuRender(void)
{
 screenClear();
 //for now lets just print a basic welcome screen
 screenPrint((screenWidth-strlen("Welcome to rlTutorial"))/2,screenHeight/2,
   "Welcome to rlTutorial");

 int16_t fgColor=WHITE_BRIGHT;
 int16_t bgColor=BLACK;

 if(player.menuSelection==0)
 {
  //new game selected, print with inverted color
  screenColorPrint((screenWidth-strlen("New game"))/2,screenHeight/2+2,
    bgColor,fgColor,"New game");
 }
 else
 {
  //print with regular color
  screenColorPrint((screenWidth-strlen("New game"))/2,screenHeight/2+2,
    fgColor,bgColor,"New game");
 }

 if(diskCanLoad(PLAYER_SAVE_FILE))
 {
  if(player.menuSelection==1)
  {
   //game to load found, load last game selected, print with inverted color
   screenColorPrint((screenWidth-strlen("Load last game"))/2,screenHeight/2+3,
     bgColor,fgColor,"Load last game");
  }
  else
  {
   //game to load found, print with regular color
   screenColorPrint((screenWidth-strlen("Load last game"))/2,screenHeight/2+3,
     fgColor,bgColor,"Load last game");
  }
 }
 else
 {
  //no game to load, print with a darker white
  screenColorPrint((screenWidth-strlen("Load last game"))/2,screenHeight/2+3,
    WHITE,bgColor,"Load last game");
 }

 if(player.menuSelection==2)
 {
  //quit selected, print with inverted color
  screenColorPrint((screenWidth-strlen("Quit"))/2,screenHeight/2+4,
    bgColor,fgColor,"Quit");
 }
 else
 {
  //print with regular color
  screenColorPrint((screenWidth-strlen("Quit"))/2,screenHeight/2+4,
    fgColor,bgColor,"Quit");
 }

 screenPrint(
   screenWidth-strlen("Up/Down to change selection, Return to select")-1,
   screenHeight,"Up/Down to change selection, Return to select");
}

