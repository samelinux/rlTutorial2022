
#include "random.h"

//this whole file is based on Lehmer random numbers:
//https://en.wikipedia.org/wiki/Lehmer_random_number_generator

uint64_t randomSeed=0;

//set a random seed
void randomSetup(void)
{
 randomSetSeed(time(NULL));
}

//set a user defined seed
void randomSetSeed(uint64_t seed)
{
 randomSeed=seed;
 randomGet(0,1);
}

//get a random value based on
uint64_t randomGet(uint64_t min,uint64_t max)
{
 uint64_t tmp=0;
 uint32_t multiplier1=0;
 if (max-min+1<=0)
 {
  return 0;
 }
 //here come the Lehmer magic 8p
 randomSeed+=0xe120fc15;
 tmp=(uint64_t)randomSeed*0x4a39b70d;
 multiplier1=(tmp>>32)^tmp;
 tmp=(uint64_t)multiplier1*0x12fad5c9;
 return ((tmp>>32)^tmp)%(max-min+1)+min;
}

//get a random valued based on a dice roll
uint64_t randomDice(uint64_t diceSize)
{
 return randomGet(1,diceSize);
}

