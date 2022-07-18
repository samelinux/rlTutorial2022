
#ifndef _signal_
#define _signal_

void signalInit(void);

void signalDeinit(void);

void signalHandler(int signal);

void signalInterruptHandler(int signal);

#endif

