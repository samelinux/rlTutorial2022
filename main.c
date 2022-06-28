
#include "main.h"

//int main(int argc,char** argv)
int main(void)
{
 player_t player;

 signalInit();
 keyboardInit();
 screenInit();

 playerInit(&player);

 //just an example: roll some dice, draw some colored '#' and get user input
 char command=0;
 while(command!='q')
 {
  screenClear();

  screenPut(player.x,player.y,'@');
  screenPrint(0,screenHeight,"Press 'q' to quit");

  command=keyboardRead();
  playerHandleInput(&player,command);
 }

 screenDeinit();
 keyboardDeinit();
 signalDeinit();
 return 0;
}

