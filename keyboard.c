
#include <stdio.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>
#include "keyboard.h"

//this whole file is based on
//https://www.man7.org/linux/man-pages/man3/termios.3.html

//This structur contains the initial termianl configuration
struct termios oldKeyboardFlags;

//Initialized the keyboard: clear ICANON and ECHO flags
void keyboardInit(void)
{
 struct termios newKeyboardFlags;
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

//Deinitialize the keyboard: set the initial terminal configuration
void keyboardDeinit(void)
{
 //set the old terminal flags
 tcsetattr(0,TCSADRAIN,&oldKeyboardFlags);
}

//Read a character from the keyboard [this function will wait until the player
//press a key]
char keyboardRead(void)
{
 int remaining=0;
 char buffer;
 //read one character from stdin
 read(STDIN_FILENO,&buffer,1);
 //if buffer contains 27 [ESC] we may have an escape sequence
 if(buffer==27)
 {
  //if there are more character [mybe it's just ESC!]
  if(ioctl(0,FIONREAD,&remaining)==0 && remaining>0)
  {
   //read the [ character
   read(STDIN_FILENO,&buffer,1);
   if(buffer==91)
   {
    //read the "real" character and translate it
    read(STDIN_FILENO,&buffer,1);
    switch(buffer)
    {
     case 49:
      buffer='y';
      break;
     case 52:
      buffer='b';
      break;
     case 53:
      buffer='u';
      break;
     case 54:
      buffer='n';
      break;
     case 68://left arrow
      buffer='h';
      break;
     case 66://down arrow
      buffer='j';
      break;
     case 65://up arrow
      buffer='k';
      break;
     case 67://right arrow
      buffer='l';
      break;
    }
   }
  }
 }
 return buffer;
}

