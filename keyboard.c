
#include "keyboard.h"

//this whole file is based on
//https://www.man7.org/linux/man-pages/man3/termios.3.html

struct termios oldKeyboardFlags;
struct termios newKeyboardFlags;

void keyboardSetup(void)
{
 //get terminal flags
 if(tcgetattr(0,&oldKeyboardFlags)>=0)
 {
  tcgetattr(0,&newKeyboardFlags);
  //set terminal in non canonical mode
  newKeyboardFlags.c_lflag&=~ICANON;
  //disable echo of input
  newKeyboardFlags.c_lflag&=~ECHO;
  //read block until requested character
  newKeyboardFlags.c_cc[VMIN]=1;
  newKeyboardFlags.c_cc[VTIME]=0;
  //set terminal falgs
  tcsetattr(0,TCSANOW,&newKeyboardFlags);
 }
}

void keyboardRestore(void)
{
 //set the old terminal flags
 tcsetattr(0,TCSADRAIN,&oldKeyboardFlags);
}

char keyboardRead(void)
{
 char buf;
 //read one character from stdin
 read(STDIN_FILENO,&buf,1);
 return buf;
}

