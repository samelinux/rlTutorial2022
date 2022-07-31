
#ifndef _disk_
#define _disk_

#include <stdbool.h>

bool diskSavePlayer(char* playerFile);

bool diskLoadPlayer(char* playerFile);

bool diskSaveLevel(char* levelFile);

bool diskLoadLevel(char* levelFile);

bool diskCanLoadGame(char* file);

bool diskSaveGame();

bool diskLoadGame();

void diskDeleteGame();

#endif

