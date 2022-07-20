
#include "monsterAIHostile.h"
#include "player.h"
#include "map.h"

//perform one action using MONSTER_AI_HOSTILE for monster
void monsterAIHostileAct(monster_t* monster)
{
 //if the player is nearby, attack him
 if(playerIsInAttackRange(monster,1)==true)
 {
  playerAttackedBy(monster);
 }
 else
 {
  monsterBestMoveToReachPlayer(monster);
 }
}

