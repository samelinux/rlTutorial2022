
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdio.h>
#include "disk.h"
#include "map.h"
#include "item.h"
#include "monster.h"
#include "player.h"

//open playerFile and call playerSave
bool diskSavePlayer(char* playerFile)
{
 FILE* aPlayerFile=fopen(playerFile,"wb+");
 if(aPlayerFile!=NULL)
 {
  bool saved=true;
  saved&=playerSave(aPlayerFile);
  fclose(aPlayerFile);
  return saved;
 }
 return false;
}

//open playerFile and call playerLoad
bool diskLoadPlayer(char* playerFile)
{
 FILE* aPlayerFile=fopen(playerFile,"rb");
 if(aPlayerFile!=NULL)
 {
  bool loaded=true;
  loaded&=playerLoad(aPlayerFile);
  fclose(aPlayerFile);
  return loaded;
 }
 return false;
}

//open levelFile and call mapSave,itemPoolSave and monsterPoolSave
bool diskSaveLevel(char* levelFile)
{
 FILE* aLevelFile=fopen(levelFile,"wb+");
 if(aLevelFile!=NULL)
 {
  bool saved=true;
  saved&=mapSave(aLevelFile);
  saved&=itemPoolSave(aLevelFile);
  saved&=monsterPoolSave(aLevelFile);
  fclose(aLevelFile);
  return saved;
 }
 return false;
}

//open levelFile and call mapLoad,itemPoolLoad and monsterPoolLoad
bool diskLoadLevel(char* levelFile)
{
 FILE* aLevelFile=fopen(levelFile,"rb");
 if(aLevelFile!=NULL)
 {
  bool loaded=true;
  loaded&=mapLoad(aLevelFile);
  loaded&=itemPoolLoad(aLevelFile);
  loaded&=monsterPoolLoad(aLevelFile);
  fclose(aLevelFile);
  return true;
 }
 return false;
}

//return true if file exists
bool diskCanLoad(char* file)
{
 return access(file,F_OK)==0;
}

//return true if the map file of level exists
bool diskCanLoadMap(int16_t level)
{
 char levelFile[16];
 memset(levelFile,0,sizeof(char)*16);
 snprintf(levelFile,16,"level%05d.save",level);
 return diskCanLoad(levelFile);
}

//save the whole game
bool diskSaveGame()
{
 bool saved=true;
 saved&=diskSavePlayer(PLAYER_SAVE_FILE);
 char levelFile[16];
 memset(levelFile,0,sizeof(char)*16);
 snprintf(levelFile,16,"level%05d.save",player.dungeonLevel);
 saved&=diskSaveLevel(levelFile);
 return saved;
}

//load the whole game
bool diskLoadGame()
{
 bool loaded=true;
 loaded&=diskLoadPlayer(PLAYER_SAVE_FILE);
 char levelFile[16];
 memset(levelFile,0,sizeof(char)*16);
 snprintf(levelFile,16,"level%05d.save",player.dungeonLevel);
 loaded&=diskLoadLevel(levelFile);
 return loaded;
}

//delete all game related files (player and levels)
void diskDeleteGame()
{
 DIR *aFolder=opendir(".");
 struct dirent* next=NULL;
 while((next=readdir(aFolder))!=NULL)
 {
  if(strstr(next->d_name,".save"))
  {
   if(strstr(next->d_name,"level"))
   {
    remove(next->d_name);
   }
   if(strstr(next->d_name,"player"))
   {
    remove(next->d_name);
   }
  }
 }
 closedir(aFolder);
}

