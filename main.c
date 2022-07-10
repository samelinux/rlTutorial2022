
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

 //setup the player
 playerInit(MAP_WIDTH/2,MAP_HEIGHT/2);

 //setup the map
 mapInit(MAP_CAVE);

 //setup monsters
 monstersInit();

 //add a monster
 monster_t rat;
 monsterInit(&rat,MONSTER_RAT);
 monstersAdd(rat);

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
  monstersRender();
  //draw the player and a hint on how to quit
  playerRender();

  screenPrint(0,screenHeight,"Press 'q' to quit");

  //get player input
  command=keyboardRead();
  //handle the input based on game/player status
  playerHandleInput(command);
 }

 //deinit the "engine"
 screenDeinit();
 keyboardDeinit();
 signalDeinit();

 //return
 return 0;
}

