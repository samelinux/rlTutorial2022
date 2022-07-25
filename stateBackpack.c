
#include <string.h>
#include <stdlib.h>
#include "stateBackpack.h"
#include "screen.h"
#include "player.h"

//handle the main menu input
bool stateBackpackUpdate(char input)
{
 bool newTurn=false;
 switch(input)
 {
  case 27:
   //move the player to the map state
   player.state=STATE_MAP;
   break;
  case 9:
   //change selection [backpack <-> nearby]
   player.backpackSelected=!player.backpackSelected;
   break;
  case 'g':
  case ',':
   //pickup items
   if(player.backpackSelected==false)
   {
    playerPickup(itemPoolAt(player.x,player.y,player.nearbyIndex));
    newTurn=true;
   }
   break;
  case 'u':
  case 10:
   //use item
   playerUseSelectedItem();
   newTurn=true;
   break;
  case 'd':
   //drop item
   playerDropSelectedItem();
   newTurn=true;
   break;
  case '4':
  case 'h':
   //select backpack
   player.backpackSelected=true;
   break;
  case '2':
  case 'j':
   //down
   if(player.backpackSelected==true)
   {
    //scroll on line down in the backpack
    int16_t backpackCount=playerBackpackCount();
    if(player.backpackIndex<backpackCount-1)
    {
     player.backpackIndex++;
     if(player.backpackIndex>=
       player.backpackStart+screenHeight-3)
     {
      player.backpackStart++;
     }
    }
   }
   else
   {
    //scroll on line down in the nearby items
    int16_t nearbyCount=itemPoolCountAt(player.x,player.y);
    if(player.nearbyIndex<nearbyCount-1)
    {
     player.nearbyIndex++;
     if(player.nearbyIndex>=
       player.nearbyStart+screenHeight-3)
     {
      player.nearbyStart++;
     }
    }
   }
   break;
  case '8':
  case 'k':
   //up
   if(player.backpackSelected==true)
   {
    //scroll one line up in the backpack
    if(player.backpackIndex>0)
    {
     player.backpackIndex--;
     if(player.backpackIndex<player.backpackStart)
     {
      player.backpackStart--;
     }
    }
   }
   else
   {
    //scroll on line up in the nearby items
    if(player.nearbyIndex>0)
    {
     player.nearbyIndex--;
     if(player.nearbyIndex<player.nearbyStart)
     {
      player.nearbyStart--;
     }
    }
   }
   break;
  case '6':
  case 'l':
   //select nearby
   player.backpackSelected=false;
   break;
 }
 return newTurn;
}

//draw the main menu screen
void stateBackpackRender(void)
{
 int8_t fgColor=WHITE;
 int8_t bgColor=BLACK;
 int8_t nearbyX=screenWidth/2;
 int8_t screenLine=0;

 screenClear();

 int8_t backpackItems=0;
 //print the backpack header, inverted if selected
 if(player.backpackSelected==true)
 {
  fgColor=BLACK;
  bgColor=WHITE;
 }
 else
 {
  fgColor=WHITE;
  bgColor=BLACK;
 }
 screenColorPrint(0,0,fgColor,bgColor,"Backpack");
 screenLine=1;
 //for each screen line -3 [1 for the header, one space and one line of log]
 for(int8_t i=0;i<screenHeight-3 &&
   player.backpackStart+i<BACKPACK_LENGTH;i++)
 {
  int16_t backpackIndex=player.backpackStart+i;
  //if the relative item in the backpack exists
  if(player.backpack[backpackIndex].type!=ITEM_NONE)
  {
   //print a '>' if that item is selected
   screenPrint(0,screenLine,"%c",
     player.backpackIndex==player.backpackStart+i?'>':' ');
   //print the item name
   screenPrint(1,screenLine++," %s",player.backpack[backpackIndex].name);
   backpackItems++;
  }
 }
 //if we did not print any item then there are no item in the backpack
 if(backpackItems==0)
 {
  screenPrint(1,screenLine,"No items");
 }

 int8_t nearbyCount=0;
 //print the nearby header, inverted if selected
 if(player.backpackSelected==false)
 {
  screenColorPrint(nearbyX,0,BLACK,WHITE,"Nearby");
 }
 else
 {
  screenColorPrint(nearbyX,0,WHITE,BLACK,"Nearby");
 }
 screenLine=1;
 int8_t nearbyItems=itemPoolCountAt(player.x,player.y);
 //for each nearby item -3 [1 for the header, one space and 1 line of log]
 for(int8_t i=0;i<screenHeight-3 && i<nearbyItems;i++)
 {
  item_t* item=itemPoolAt(player.x,player.y,i);
  //if the relative item in the player tile exist
  if(item!=NULL && item->type!=ITEM_NONE)
  {
   //print a '>' if that item is selected
   screenPrint(nearbyX+0,screenLine,"%c",
     player.nearbyIndex==nearbyCount?'>':' ');
   //print the item name
   screenPrint(nearbyX+1,screenLine++,"%s",item->name);
   nearbyCount++;
  }
 }
 //if we did not print any item the nthere are no item nearby the player
 if(nearbyCount==0)
 {
  screenPrint(nearbyX,screenLine,"No items");
 }

 //print the last journal line
 screenPrint(0,screenHeight-1,"%s",player.journal[JOURNAL_LENGTH-1]);
}

