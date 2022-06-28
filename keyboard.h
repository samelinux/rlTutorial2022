
#ifndef _keyboard_
#define _keyboard_

#include <stdio.h>
#include <termios.h>
#include <unistd.h>

void keyboardInit(void);

void keyboardDeinit(void);

char keyboardRead(void);

#endif

