
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <execinfo.h>
#include <unistd.h>
#include "screen.h"
#include "signal.h"
#include "macro.h"
#include "keyboard.h"

//this whole file is base on:
//https://man7.org/linux/man-pages/man2/signal.2.html
//https://man7.org/linux/man-pages/man7/signal.7.html
//https://man7.org/linux/man-pages/man3/backtrace.3.html

//setup signal handlers for most of the fault signals
void signalInit(void)
{
 signal(SIGINT,signalInterruptHandler);
 signal(SIGABRT,signalHandler);
 signal(SIGBUS,signalHandler);
 signal(SIGFPE,signalHandler);
 signal(SIGILL,signalHandler);
 signal(SIGPIPE,signalHandler);
 signal(SIGSEGV,signalHandler);
 signal(SIGSYS,signalHandler);
 signal(SIGXCPU,signalHandler);
 signal(SIGXFSZ,signalHandler);
}

//reset signals handler to their default
void signalDeinit(void)
{
 signal(SIGABRT,SIG_DFL);
 signal(SIGBUS,SIG_DFL);
 signal(SIGFPE,SIG_DFL);
 signal(SIGILL,SIG_DFL);
 signal(SIGPIPE,SIG_DFL);
 signal(SIGSEGV,SIG_DFL);
 signal(SIGSYS,SIG_DFL);
 signal(SIGXCPU,SIG_DFL);
 signal(SIGXFSZ,SIG_DFL);
}

//on signal just print the stack trace and quit
void signalHandler(int signal)
{
 void *array[100];
 size_t size;
 //get the backgrace up to 100 calls
 size=backtrace(array,100);
 //reset the screen and terminal to their original states
 screenDeinit();
 keyboardDeinit();
 //print some info
 print("CRASH! Signal: %d\n",signal);
 print("Stack trace:\n");
 //print it in a "pretty" way
 backtrace_symbols_fd(array,size,STDERR_FILENO);
 exit(-1);
}

//we use a different signal handler for SIGINT so when the player presse
//ctrl+c we still have time to reset the screen and the terminal to their
//original state
void signalInterruptHandler(int signal)
{
 screenDeinit();
 keyboardDeinit();
 signalDeinit();
 print("Closing for signal: %d\n",signal);
 exit(-1);
}

