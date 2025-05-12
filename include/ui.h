#ifndef __UI_H__
#define __UI_H__

#include "screen.h"
#include "player.h"
#include "items.h"

struct Game;
typedef struct Game Game;

void showWelcomeScreen();
void drawGameScreen(Game* game);
void drawHUD(const Player* player);
void showGameOverScreen(int score, int level);

#endif /* __UI_H__ */