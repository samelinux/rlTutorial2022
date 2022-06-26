
#include "position.h"

//separated x and y distance
position_t positionXYDistances(position_t p0,position_t p1)
{
 uint16_t dx=abs(p0.x-p1.x);
 uint16_t dy=abs(p0.y-p1.y);
 return POSITION(dx,dy);
}

//real distance
uint64_t positionDistance(position_t p0,position_t p1)
{
 return sqrt(pow(p0.x-p1.x,2)+pow(p0.y-p1.y,2));
}

//add two coordinates together [usefull for cycles]
position_t positionSum(position_t p0,position_t p1)
{
 position_t result=p0;
 result.x+=p1.x;
 result.y+=p1.y;
 return result;
}

//return true if two coordinates are the same point
bool positionEquals(position_t p0,position_t p1)
{
 return p0.x==p1.x && p0.y==p1.y;
}

