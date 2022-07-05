
#include "map.h"

//declare a map
map_t map;

//setup a map_t structure
void mapInit(mapType_t type)
{
 memset(&(map),0,sizeof(map));
 map.type=type;
 for(int i=0;i<MAP_WIDTH*MAP_HEIGHT;i++)
 {
  tileInit(&(map.tiles[i]),TILE_FLOOR);
 }
 switch(type)
 {
  case MAP_MAX:
  case MAP_NONE:
  case MAP_EMPTY: break;
  case MAP_SAMPLE: mapSampleBuild(); break;
 }
}

//return true if x,y are in the map boundaries
bool mapIsValid(int16_t x,int16_t y)
{
 return x>=0 && x<MAP_WIDTH && y>=0 && y<MAP_HEIGHT;
}

//render the whole map [for now this is ok since it is 80x24 but when the map
//will become bigger we will implement rendering just a part of it]
void mapRender()
{
 for(int y=0;y<MAP_HEIGHT;y++)
 {
  for(int x=0;x<MAP_WIDTH;x++)
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

