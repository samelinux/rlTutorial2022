
#ifndef _disk_
#define _disk_

#include <stdbool.h>

#define PLAYER_SAVE_FILE ("player.save")

bool diskSavePlayer(char* playerFile);

bool diskLoadPlayer(char* playerFile);

bool diskSaveLevel(char* levelFile);

bool diskLoadLevel(char* levelFile);

bool diskCanLoad(char* file);

bool diskCanLoadMap(int16_t level);

bool diskSaveGame();

bool diskLoadGame();

void diskDeleteGame();

#endif

