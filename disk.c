
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdio.h>
#include "map.h"
#include "item.h"
#include "monster.h"
#include "player.h"

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

bool diskCanLoadGame(char* file)
{
 return access(file,F_OK)==0;
}

bool diskSaveGame()
{
 bool saved=true;
 saved&=diskSavePlayer("player.save");
 char levelFile[16];
 memset(levelFile,0,sizeof(char)*16);
 snprintf(levelFile,16,"level%05d.save",player.dungeonLevel);
 saved&=diskSaveLevel(levelFile);
 return saved;
}

bool diskLoadGame()
{
 bool loaded=true;
 loaded&=diskLoadPlayer("player.save");
 char levelFile[16];
 memset(levelFile,0,sizeof(char)*16);
 snprintf(levelFile,16,"level%05d.save",player.dungeonLevel);
 loaded&=diskLoadLevel(levelFile);
 return loaded;
}

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

