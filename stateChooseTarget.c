
#include <stdlib.h>
#include "stateChooseTarget.h"
#include "stateMap.h"
#include "stateExamineMap.h"
#include "itemConfusionScroll.h"
#include "itemFireballScroll.h"
#include "monster.h"
#include "tile.h"
#include "screen.h"
#include "macro.h"
#include "map.h"
#include "player.h"

//handle choose target sstate player input
bool stateChooseTargetUpdate(char input)
{
 tile_t* tile=NULL;
 bool newTurn=stateExamineMapUpdate(input);
 switch(input)
 {
  case 10:
  case 't':
   tile=mapTileAt(player.examineX,player.examineY);
   if(tile!=NULL && tile->visible==true)
   {
    switch(player.itemToUse->type)
    {
     case ITEM_MAX:
     case ITEM_NONE:
     case ITEM_HEALTH_POTION:
     case ITEM_LIGHTNING_SCROLL:
      break;
     case ITEM_CONFUSION_SCROLL:
      newTurn=itemUseConfusionScroll(player.itemToUse,
        player.examineX,player.examineY);
      player.state=STATE_MAP;
      break;
     case ITEM_FIREBALL_SCROLL:
      newTurn=itemUseFireballScroll(player.itemToUse,
        player.examineX,player.examineY);
      player.state=STATE_MAP;
      break;
    }
   }
   else
   {
    playerLog("You can't target an area you can't see");
   }
   break;
 }
 return newTurn;
}

//render the choose target screen
void stateChooseTargetRender(void)
{
 stateExamineMapRender();
 int8_t itemRange=0;
 switch(player.itemToUse->type)
 {
  case ITEM_NONE:
  case ITEM_MAX:
  case ITEM_HEALTH_POTION:
  case ITEM_LIGHTNING_SCROLL:
  case ITEM_CONFUSION_SCROLL:
   break;
  case ITEM_FIREBALL_SCROLL:
   itemRange=itemRangeFireballScroll();
   break;
 }
 for(int8_t dy=-itemRange;dy<=itemRange;dy++)
 {
  for(int8_t dx=-itemRange;dx<=itemRange;dx++)
  {
   int16_t x=player.examineX+dx;
   int16_t y=player.examineY+dy;
   if(distance(x,y,player.examineX,player.examineY)<=itemRange)
   {
    tile_t* tile=mapTileAt(x,y);
    monster_t* monster=monsterPoolAt(x,y);
    int16_t itemCount=itemPoolCountAt(x,y);
    item_t* item=itemPoolAt(x,y,0);
    if(x==player.x && y==player.y)
    {
     //the player is under the selection, draw it with inverted colors
     if(dx==0 && dy==0)
     {
      playerRenderPlayer(player.examineX,player.examineY,TARGET_COLOR,BLACK);
     }
     else
     {
      playerRenderPlayer(player.examineX,player.examineY,BLACK,TARGET_COLOR);
     }
    }
    else
    {
     //if a tile is under the selection
     if(tile!=NULL)
     {
      //if a monster is under the selection draw it with inverted color
      if(monster!=NULL && tile->visible==true)
      {
       //if under selection use inverted colors
       if(dx==0 && dy==0)
       {
        monsterRender(monster,player.examineX,player.examineY,
          TARGET_COLOR,monster->color);
       }
       else
       {
        monsterRender(monster,player.examineX,player.examineY,
          monster->color,TARGET_COLOR);
       }
      }
      else
      {
       if(itemCount==0)
       {
        //if the tile is visible and there are no items draw it
        if(tile->visible==true || tile->seen==true)
        {
         //if under selection use inverted colors
         if(dx==0 && dy==0)
         {
          tileRender(tile,x,y,player.examineX,player.examineY,
            TARGET_COLOR,tile->fgColor);
         }
         else
         {
          tileRender(tile,x,y,player.examineX,player.examineY,
            tile->fgColor,TARGET_COLOR);
         }
        }
       }
       else
       {
        //if the tile is visible and there are some item/items print
        //it/'some items'
        if(tile->visible==true)
        {
         //if under selection use inverted colors
         if(dx==0 && dy==0)
         {
          itemRender(item,player.examineX,player.examineY,
            TARGET_COLOR,item->color);
         }
         else
         {
          itemRender(item,player.examineX,player.examineY,
            item->color,TARGET_COLOR);
         }
        }
       }
      }
     }
    }
   }
  }
 }
 //print the last journal line
 screenPrint(0,screenHeight-1,"%s",player.journal[JOURNAL_LENGTH-1]);
}

