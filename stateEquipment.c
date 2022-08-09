
#include <string.h>
#include <stdlib.h>
#include "stateEquipment.h"
#include "screen.h"
#include "player.h"

//handle the main menu input
bool stateEquipmentUpdate(char input)
{
 bool newTurn=false;
 switch(input)
 {
  case 27:
   //move the player to the map state
   playerGotoState(STATE_MAP);
   break;
  case 'd':
   //drop item
   newTurn=playerDropSelectedEquipmentItem();
   break;
  case 'W':
   //unwield/take off item
   newTurn=playerUnequipSelectedEquipmentItem();
   break;
  case '2':
  case 'j':
   //down
   player.equipmentIndex=(player.equipmentIndex+1)%EQUIPMENT_MAX;
   break;
  case '8':
  case 'k':
   //up
   player.equipmentIndex=(player.equipmentIndex+EQUIPMENT_MAX-1)%EQUIPMENT_MAX;
   break;
 }
 return newTurn;
}

//draw the main menu screen
void stateEquipmentRender(void)
{
 int8_t screenLine=0;

 screenClear();

 //print the backpack header, inverted if selected
 screenColorPrint(0,0,BLACK,WHITE,"Equipment");
 screenLine=1;
 //for each screen line -3 [1 for the header, one space and one line of log]
 for(int8_t i=0;i<screenHeight-3 &&
   player.equipmentStart+i<EQUIPMENT_MAX;i++)
 {
  int16_t equipmentIndex=player.equipmentStart+i;
  //print a '>' if that item is selected
  screenPrint(0,screenLine,"%c",
    player.equipmentIndex==player.equipmentStart+i?'>':' ');
  //if the relative item in the backpack exists
  if(player.equipment[equipmentIndex].type!=ITEM_NONE)
  {
   //print the item name
   screenPrint(1,screenLine++," %s: %s",playerEquipmentName(equipmentIndex),
     player.equipment[equipmentIndex].name);
  }
  else
  {
   //print "no item"
   screenPrint(1,screenLine++," %s: no item",
     playerEquipmentName(equipmentIndex));
  }
 }

 //print the last journal line
 screenPrint(0,screenHeight-1,"%s",player.journal[JOURNAL_LENGTH-1]);
}

