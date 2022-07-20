
#include <stdlib.h>
#include "main.h"
#include "keyboard.h"
#include "map.h"
#include "monster.h"
#include "random.h"
#include "screen.h"
#include "signal.h"
#include "player.h"

//int main(int argc,char** argv)
int main(void)
{
 //setup the "engine"
 signalInit();
 keyboardInit();
 screenInit();
 randomSetup();
 monsterPoolInit();
 playerInit();
 mapInit();

 //infinite loop, states will break it if needed
 while(true)
 {

  //render the screen
  playerRender();

  //handle the input based on game/player status and if the player took an
  //action, make the monsters take their turns
  if(playerUpdate(keyboardRead())==true)
  {
   //handle monsters turn
   monsterPoolHandleTurn();
  }
 }

 //return
 return 0;
}

//close the program
void mainQuit(void)
{
 //deinit the "engine"
 mapDeinit();
 playerDeinit();
 monsterPoolDeinit();
 screenDeinit();
 keyboardDeinit();
 signalDeinit();
 //quit
 exit(0);
}

