
#ifndef _keyboard_
#define _keyboard_

#include <stdio.h>
#include <termios.h>
#include <unistd.h>

void keyboardSetup(void);

void keyboardRestore(void);

char keyboardRead(void);

#endif

