
#include <stdlib.h>
#include "map.h"
#include "tile.h"
#include "bresenham.h"

//calculate if an unobstructed line can be drawn from fromX,fromY to toX,toY
//using the tiles blockFOV property. Basically return true if from tile
//fromX,fromY there is a clear line of sito to toX,toY without taking into
//account the distance
//For a more in depth algorithm analysis take a look here:
//https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm
bool bresenhamLos(int16_t fromX,int16_t fromY,int16_t toX,int16_t toY)
{
 tile_t* tile;
 int32_t dx=abs(toX-fromX);
 int sx=fromX<toX?1:-1;
 int32_t dy=abs(toY-fromY);
 int sy=fromY<toY?1:-1;
 int32_t err=(dx>dy?dx:-dy)/2;
 int e2=0;
 if(mapIsValid(fromX,fromY)==false || mapIsValid(toX,toY)==false)
 {
  return false;
 }
 for (;;)
 {
  e2=err;
  if(e2>-dx)
  {
   err-=dy;
   fromX+=sx;
  }
  if(e2<dy)
  {
   err+=dx;
   fromY+=sy;
  }
  if(fromX==toX && fromY==toY)
  {
   return true;
  }
  tile=mapTileAt(fromX,fromY);
  if(tile->blockFOV==true)
  {
   return false;
  }
 }
 return false;
}

