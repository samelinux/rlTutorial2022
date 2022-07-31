
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "map.h"
#include "screen.h"
#include "mapSample.h"
#include "mapCave.h"
#include "monster.h"
#include "player.h"
#include "random.h"

//declare a map
map_t map;
//declare a Dijkstra map
//[http://www.roguebasin.com/index.php/Dijkstra_Maps_Visualized]
int16_t dijkstraMap[MAP_WIDTH*MAP_HEIGHT];

//clear the map
void mapInit(void)
{
 memset(&(map),0,sizeof(map));
}

//deinitialize the map
void mapDeinit(void)
{
 //for now doed nothing, but if we decide to allocate the map dynamically here
 //is the right player do deallocate it
}

//save the map to a file
bool mapSave(FILE* aFile)
{
 size_t written=fwrite(&map,sizeof(map_t),1,aFile);
 if(written==1)
 {
  return true;
 }
 return false;
}

//load the map from a file
bool mapLoad(FILE* aFile)
{
 size_t readed=fread(&map,sizeof(map_t),1,aFile);
 if(readed==1)
 {
  return true;
 }
 return false;
}

//generate a new level
void mapGenerate(mapType_t type)
{
 int16_t x=0;
 int16_t y=0;
 memset(&(map),0,sizeof(map));
 map.type=type;
 for(int i=0;i<MAP_WIDTH*MAP_HEIGHT;i++)
 {
  tileInit(&(map.tiles[i]),TILE_FLOOR);
 }
 //call the proper building function base on the map type
 switch(type)
 {
  case MAP_MAX:
  case MAP_NONE:
  case MAP_EMPTY: break;
  case MAP_SAMPLE: mapSampleBuild(); break;
  case MAP_CAVE: mapCaveBuild(); break;
 }
 //generate some monsters
 monsterPoolInit();
 monsterPoolSpawn(10);
 //generate some items
 itemPoolInit();
 itemPoolSpawn(10);
 //get a random walkable tile and teleport the player there
 mapRandomWalkablePosition(&x,&y);
 playerTeleportTo(x,y);
}

//return true if x,y are in the map boundaries
bool mapIsValid(int16_t x,int16_t y)
{
 return x>=0 && x<MAP_WIDTH && y>=0 && y<MAP_HEIGHT;
}

//fill x,y with random walkable coordinate in the map
void mapRandomWalkablePosition(int16_t* x,int16_t* y)
{
 do
 {
  //randomize an x,y coordinate
  *x=randomGet(0,MAP_WIDTH);
  *y=randomGet(0,MAP_HEIGHT);
  //until the tile is not valid or the tile in not walkable or there is a
  //monster at that coordinate
 }while(mapIsValid(*x,*y)==false ||
   mapTileAt(*x,*y)->walkable==false ||
   monsterPoolAt(*x,*y)!=NULL);
}

//recursively calculate the map connection "mask" in connectionMap
void mapCalculateConnection(bool connectionMap[MAP_WIDTH*MAP_HEIGHT],int16_t x,
  int16_t y)
{
 if(mapIsValid(x,y))
 {
  if(mapTileAt(x,y)->walkable==true && connectionMap[x+y*MAP_WIDTH]==false)
  {
   connectionMap[x+y*MAP_WIDTH]=true;
   //just orthogonal movements for now
   mapCalculateConnection(connectionMap,x,y-1);
   mapCalculateConnection(connectionMap,x-1,y);
   mapCalculateConnection(connectionMap,x+1,y);
   mapCalculateConnection(connectionMap,x,y+1);
  }
 }
}

//return true if a map is fully connected (a fully connected map has all its
//walkable tiles reachable from all other tiles)
bool mapIsConnected(void)
{
 int16_t x=-1;
 int16_t y=-1;
 bool found=false;
 //search a walkable starting point
 for(y=0;y<MAP_HEIGHT && found==false;y++)
 {
  for(x=0;x<MAP_WIDTH && found==false;x++)
  {
   if(mapTileAt(x,y)->walkable)
   {
    found=true;
    break;
   }
  }
 }
 if(found)
 {
  //create an calculate the connection "mask"
  bool connectionMap[MAP_WIDTH*MAP_HEIGHT];
  memset(connectionMap,0,sizeof(bool)*MAP_WIDTH*MAP_HEIGHT);
  mapCalculateConnection(connectionMap,x,y);
  //if every walkable tile in the map is connected the the map is fully
  //connected
  for(y=0;y<MAP_HEIGHT;y++)
  {
   for(x=0;x<MAP_WIDTH;x++)
   {
    if(mapTileAt(x,y)->walkable && connectionMap[x+y*MAP_WIDTH]==false)
    {
     //we found a walkable tile that is not connected
     return false;
    }
   }
  }
  return true;
 }
 //probably we didn't even find a starting point 8p
 return false;
}

//render map from fromX,fromY point of view
void mapRender(int16_t fromX,int16_t fromY)
{
 int16_t x=fromX-MAP_VIEWPORT_WIDTH/2;
 int16_t y=fromY-MAP_VIEWPORT_HEIGHT/2;
 for(int16_t dy=0;dy<MAP_VIEWPORT_HEIGHT;dy++)
 {
  for(int16_t dx=0;dx<MAP_VIEWPORT_WIDTH;dx++) {
   tile_t* tile=mapTileAt(x+dx,y+dy);
   if(tile!=NULL)
   {
    if(tile->visible || tile->seen)
    {
     //draw each visible tile
     tileRender(tile,x+dx,y+dy,fromX,fromY,tile->fgColor,tile->bgColor);
    }
   }
  }
 }
}

//return the tile at x,y in the map, NULL otherwise
tile_t* mapTileAt(int16_t x,int16_t y)
{
 if(mapIsValid(x,y))
 {
  return &(map.tiles[x+y*MAP_WIDTH]);
 }
 return NULL;
}

//clear all map tile visible status
void mapResetFOV(void)
{
 for(int16_t y=0;y<MAP_HEIGHT;y++)
 {
  for(int16_t x=0;x<MAP_WIDTH;x++)
  {
   mapTileAt(x,y)->visible=false;
  }
 }
}

//clear the dijkstra map
void mapResetDijkstraMap(void)
{
 memset(dijkstraMap,0,sizeof(int16_t)*MAP_WIDTH*MAP_HEIGHT);
}

//calculate the map dijkstra map from x,y point of view
void mapCalculateDijkstraMap(int16_t x,int16_t y)
{
 //declare a queue to store tile index
 int16_t indexQueue[MAP_WIDTH*MAP_HEIGHT];
 //head and tail of the queue
 int16_t head=0;
 int16_t tail=1;
 //current hazzard
 int16_t hazard=INT16_MAX;
 //start with x,y in the queue
 indexQueue[head]=x+y*MAP_WIDTH;
 //while there are index to process
 while(head<tail)
 {
  //save the actual tail
  int16_t tmpTail=tail;
  //for each index of the previous iteration
  while(head<tmpTail)
  {
   //"pop" an index and calculate its x,y coordinate
   int16_t newIndex=indexQueue[head];
   head++;
   int16_t newX=newIndex%MAP_WIDTH;
   int16_t newY=newIndex/MAP_WIDTH;
   tile_t* tile=mapTileAt(newX,newY);
   //if it is a valid tile
   if(tile!=NULL)
   {
    //if there is no hazard or the old hazard is worse
    if(dijkstraMap[newIndex]==0 || hazard>dijkstraMap[newIndex])
    {
     //update the hazard and "push" all its neighbour tile
     dijkstraMap[newIndex]=hazard;
     for(int8_t dy=-1;dy<=1;dy++)
     {
      for(int8_t dx=-1;dx<=1;dx++)
      {
       if(dx!=0 || dy!=0)
       {
        tile=mapTileAt(newX+dx,newY+dy);
        monster_t* monster=monsterPoolAt(newX+dx,newY+dy);
        //if the tile is valid, walkable and there is not a monster in it
        if(tile!=NULL && tile->walkable==true && monster==NULL)
        {
         indexQueue[tail]=newX+dx+(newY+dy)*MAP_WIDTH;
         tail++;
        }
       }
      }
     }
    }
   }
  }
  //pack the queue toward the start and reset tail and head [so we don't have
  //to handle wraparound in the array]
  int16_t j=0;
  for (int16_t i=head;i<=tail;i++)
  {
   indexQueue[j]=indexQueue[i];
   j++;
  }
  tail=tail-head;
  head=0;
  //calculate the next hazard
  hazard--;
 }
}

//return the hazard at x,y or 0 if the coordinate is not valid
int16_t mapDijkstraAt(int16_t x,int16_t y)
{
 if(mapIsValid(x,y)==true)
 {
  return dijkstraMap[x+y*MAP_WIDTH];
 }
 //return 0 because it is the worst possible hazard
 return 0;
}

