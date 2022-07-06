
#include "mapCave.h"
#include <unistd.h>

//setup a cave shaped map
void mapCaveBuild()
{
 //this two array will be used to calculate the cellular automata generations
 bool mapWalls[MAP_WIDTH*MAP_HEIGHT];
 bool mapWallsTemp[MAP_WIDTH*MAP_HEIGHT];
 do
 {
  for(int16_t y=0;y<MAP_HEIGHT;y++)
  {
   for(int16_t x=0;x<MAP_WIDTH;x++)
   {
    //fill the real array with random "walls"
    mapWalls[x+y*MAP_WIDTH]=randomDice(100)>65;
   }
  }
  //6 generations should be good enough
  int iteration=6;
  while(iteration-->0)
  {
   for(int16_t y=0;y<MAP_HEIGHT;y++)
   {
    for(int16_t x=0;x<MAP_WIDTH;x++)
    {
     //calculate the number of neighbours for heach tile
     int neighboursCount=0;
     for(int8_t dy=-1;dy<=1;dy++)
     {
      for(int8_t dx=-1;dx<=1;dx++)
      {
       if(dx!=0 || dy!=0)
       {
        if(!mapIsValid(x+dx,y+dy) ||
          mapWalls[x+dx+(y+dy)*MAP_WIDTH]==true)
        {
         neighboursCount++;
        }
       }
      }
     }
     //implement some birth/death rules (different rules produces different
     //results!) and copy the new value in the temporary array
     if(neighboursCount<4) mapWallsTemp[x+y*MAP_WIDTH]=false;
     if(neighboursCount>=4) mapWallsTemp[x+y*MAP_WIDTH]=true;
    }
   }
   //copy back the new generation to the main array
   memcpy(&mapWalls,&mapWallsTemp,sizeof(bool)*MAP_WIDTH*MAP_HEIGHT);
  }
  //compose the map
  for(int16_t y=0;y<MAP_HEIGHT;y++)
  {
   for(int16_t x=0;x<MAP_WIDTH;x++)
   {
    if(x==0 || x==MAP_WIDTH-1 || y==0 || y==MAP_HEIGHT-1)
    {
     tileInit(mapTileAt(x,y),TILE_WALL);
    }
    else
    {
     tileInit(mapTileAt(x,y),mapWalls[x+y*MAP_WIDTH]==true?TILE_WALL:TILE_FLOOR);
    }
   }
  }
  //repeat this process until we get a fully connected map so the player can
  //reach all of its walkable tiles
 }while(mapIsConnected()==false);
}

