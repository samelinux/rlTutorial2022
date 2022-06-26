
#include "main.h"

//int main(int argc,char** argv)
int main(void)
{
 signalInit();
 keyboardSetup();

 //just an example: roll some dice, draw some colored '#' and get user input
 char command=0;
 while(command!='q')
 {
  screenClear();
  int dice[6]={0,0,0,0,0,0};
  for(int i=0;i<100000;i++)
  {
   dice[randomDice(6)-1]++;
  }
  for(int i=0;i<6;i++)
  {
   screenPrint(0,i,"#d(6)==%d -> %d\n",i+1,dice[i]);
  }
  screenPrint(0,6,"Colors:");
  for(int i=BLACK;i<=WHITE;i++)
  {
   screenColorPut(0+i-BLACK,7,i,BLACK,'#');
  }
  for(int i=BLACK_BRIGHT;i<=WHITE_BRIGHT;i++)
  {
   screenColorPut(0+i-BLACK_BRIGHT,8,i,BLACK,'#');
  }
  screenPrint(0,23,"q to quit, any key to reroll\n");
  command=keyboardRead();
 }

 screenReset();
 keyboardRestore();
 signalDeinit();
 return 0;
}

