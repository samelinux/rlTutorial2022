
#include "map.h"

//declare a map
map_t map;

//setup a map_t structure
void mapInit(mapType_t type)
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
  *x=randomGet(0,MAP_WIDTH);
  *y=randomGet(0,MAP_HEIGHT);
 }while(mapIsValid(*x,*y)==false || mapTileAt(*x,*y)->walkable==false);
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

//render the whole map [for now this is ok since it is 80x24 but when the map
//will become bigger we will implement rendering just a part of it]
void mapRender()
{
 for(int16_t y=0;y<MAP_HEIGHT;y++)
 {
  for(int16_t x=0;x<MAP_WIDTH;x++)
  {
   int i=x+y*MAP_WIDTH;
   //draw each tile
   screenColorPut(x,y,map.tiles[i].fgColor,map.tiles[i].bgColor,
     map.tiles[i].glyph);
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

