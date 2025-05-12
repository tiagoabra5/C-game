#ifndef __GAME_H__
#define __GAME_H__

#include "screen.h"
#include "keyboard.h"
#include "timer.h"
#include "player.h"
#include "items.h"
#include "scores.h"
#include "ui.h"

#define SCORES_FILE "data/scores.txt"

typedef struct Game {
    Player player;
    ItemManager items;
    int running;
    long timer;
} Game;

void gameInit(Game* game);
void gameRun(Game* game);
void gameDestroy(Game* game);
void updateGameState(Game* game);

#endif /* __GAME_H__ */