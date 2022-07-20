
#include <string.h>
#include <stdlib.h>
#include "stateGameOver.h"
#include "screen.h"

//handle the journal screen input
bool stateJournalUpdate(player_t* player,char input)
{
 switch(input)
 {
  case 27:
   //move the player to the map
   player->state=STATE_MAP;
   break;
  case '2':
  case 'j':
   //down
   if(player->journalIndex<JOURNAL_LENGTH-screenHeight+1)
   {
    player->journalIndex++;
   }
   break;
  case '8':
  case 'k':
   //up
   if(player->journalIndex>0)
   {
    player->journalIndex--;
   }
   break;
 }
 return false;
}

//render the journal screen
void stateJournalRender(player_t* player)
{
 screenClear();
 int8_t screenLine=1;
 screenPrint(0,0,"Journal");
 for(int8_t i=0;i<screenHeight-1;i++)
 {
  int8_t logLine=(player->journalIndex+i)%JOURNAL_LENGTH;
  screenPrint(0,screenLine,"%s",player->journal[logLine]);
  screenLine++;
 }
}
