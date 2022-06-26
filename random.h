
#ifndef _random_
#define _random_

#include <stdint.h>
#include <time.h>

void randomSetup(void);

void randomSetSeed(uint64_t newseed);

uint64_t randomGet(uint64_t min,uint64_t max);

uint64_t randomDice(uint64_t diceSize);

#endif

