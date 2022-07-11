
#include "main.h"

//int main(int argc,char** argv)
int main(void)
{
 //declare a variable to store user input
 char command=0;

 //setup the "engine"
 signalInit();
 keyboardInit();
 screenInit();
 randomSetup();
 monsterPoolInit();

 //setup the player
 playerInit(MAP_WIDTH/2,MAP_HEIGHT/2);

 //setup the map
 mapInit(MAP_CAVE);

 //while the user has not pressed 'q'
 while(command!='q')
 {
  //clear the screen
  screenClear();

  //reset map field of view status
  mapResetFOV();
  //calculate new field of view
  playerCalculateFOV();
  //draw the map
  mapRender();
  //draw all monsters
  monsterPoolRender();
  //draw the player and a hint on how to quit
  playerRender();

  //get player input
  command=keyboardRead();
  //handle the input based on game/player status and if the player took an
  //action, make the monsters take their turns
  if(playerHandleInput(command)==true)
  {
   //handle monsters turn
   monsterPoolHandleTurn();
  }
 }

 //deinit the "engine"
 screenDeinit();
 keyboardDeinit();
 signalDeinit();

 //return
 return 0;
}

