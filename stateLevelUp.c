
#include <string.h>
#include <stdlib.h>
#include "stateLevelUp.h"
#include "stateMap.h"
#include "screen.h"
#include "player.h"

//handle the level up screen input
bool stateLevelUpUpdate(char input)
{
 switch(input)
 {
  case 10:
   //return
   switch(player.menuSelection)
   {
    //modify the relevant stat based on the player selection
    case 0:
     player.maxHitPoints+=20;
     break;
    case 1:
     player.attack+=1;
     break;
    case 2:
     player.defence+=1;
     break;
   }
   playerGotoState(STATE_MAP);
   break;
  case '8':
  case 'k':
   //up
   player.menuSelection=abs((player.menuSelection+2)%3);
   break;
  case '2':
  case 'j':
   //down
   player.menuSelection=(player.menuSelection+1)%3;
   break;
 }
 return false;
}

//render the level up screen
void stateLevelUpRender(void)
{
 int8_t x=(screenWidth-35)/2;
 int8_t y=(screenHeight-5)/2;
 //this is an hack to have the map screen updated to the last action
 stateMapRender();
 //draw the level up popup
 screenBox(x-2,y-2,x+35+1,y+5+1,WHITE,BLACK);
 //"header"
 screenPrint(x,y++,"You gained a level! Choose a bonus:");
 y++;
 //options
 if(player.menuSelection==0)
 {
  screenColorPrint(x,y++,BLACK,WHITE,"+20 Hit points (from %d)",
    player.maxHitPoints);
 }
 else
 {
  screenColorPrint(x,y++,WHITE,BLACK,"+20 Hit points (from %d)",
    player.maxHitPoints);
 }
 if(player.menuSelection==1)
 {
  screenColorPrint(x,y++,BLACK,WHITE,"+1 Attack (from %d)",player.attack);
 }
 else
 {
  screenColorPrint(x,y++,WHITE,BLACK,"+1 Attack (from %d)",player.attack);
 }
 if(player.menuSelection==2)
 {
  screenColorPrint(x,y++,BLACK,WHITE,"+1 Defence (from %d)",player.defence);
 }
 else
 {
  screenColorPrint(x,y++,WHITE,BLACK,"+1 Defence (from %d)",player.defence);
 }
}

