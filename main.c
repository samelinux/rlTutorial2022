
#include "main.h"

//int main(int argc,char** argv)
int main(void)
{
 //declare a player
 player_t player;
 //declare a variable to store user input
 char command=0;

 //setup the "engine"
 signalInit();
 keyboardInit();
 screenInit();

 //setup the player
 playerInit(&player);

 //while the user has not pressed 'q'
 while(command!='q')
 {
  //clear the screen
  screenClear();

  //draw the player and a hint on how to quit
  screenPut(player.x,player.y,'@');
  screenPrint(0,screenHeight,"Press 'q' to quit");

  //get player input
  command=keyboardRead();
  //handle the input based on game/player status
  playerHandleInput(&player,command);
 }

 //deinit the "engine"
 screenDeinit();
 keyboardDeinit();
 signalDeinit();

 //return
 return 0;
}

