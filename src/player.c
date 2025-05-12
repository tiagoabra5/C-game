#include "player.h"
#include "keyboard.h"

void playerInit(Player* player) {
    player->x = MAXX / 2;
    player->y = MAXY - 2;
    player->score = 0;
    player->lives = 3;
    player->speed = INITIAL_SPEED;
    player->level = 1;
    player->lastMoveTime = 0;
    player->lastDifficultyIncrease = 0;
}

void handlePlayerInput(Player* player, int* running) {
    while (keyhit()) {
        int ch = readch();
        switch (ch) {
            case 'a':
            case 'A':
                if (player->x > SCRSTARTX) player->x--;
                break;
            case 'd':
            case 'D':
                if (player->x < SCRENDX) player->x++;
                break;
            case 'q':
            case 'Q':
                *running = 0;
                break;
        }
    }
}

void increasePlayerLevel(Player* player) {
    player->level++;
    player->speed = player->speed * 0.85;
    if (player->speed < MIN_SPEED) player->speed = MIN_SPEED;
}