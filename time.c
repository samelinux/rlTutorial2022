
#include <stdlib.h>
#include <sys/time.h>
#include "time.h"

//this whole file is based on:
//https://man7.org/linux/man-pages/man2/gettimeofday.2.html

//return the current timestamp in milliseconds
uint64_t timeMS(void)
{
 struct timeval te;
 gettimeofday(&te,NULL);
 return te.tv_sec*1000LL+te.tv_usec/1000;
}

