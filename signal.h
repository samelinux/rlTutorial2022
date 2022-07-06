
#ifndef _signal_
#define _signal_

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <execinfo.h>
#include <unistd.h>
#include "macro.h"
#include "screen.h"
#include "keyboard.h"

void signalInit(void);

void signalDeinit(void);

void signalHandler(int signal);

void signalInterruptHandler(int signal);

#endif

