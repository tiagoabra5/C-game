#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "screen.h"

#define PLAYER_CHAR '@'
#define MAX_NAME_LENGTH 50
#define INITIAL_SPEED 2000
#define MAX_SPEED 400
#define MIN_SPEED 300
#define LEVEL_UP_POINTS 30
#define DIFFICULTY_INTERVAL 15000

typedef struct {
    int x;
    int y;
    int score;
    int lives;
    int speed;
    int level;
    long lastMoveTime;
    long lastDifficultyIncrease;
} Player;

void playerInit(Player* player);
void handlePlayerInput(Player* player, int* running);
void increasePlayerLevel(Player* player);

#endif /* __PLAYER_H__ */