#include "game.h"
#include <stdlib.h>
#include <time.h>
#include <string.h>

void gameInit(Game* game) {
    srand(time(NULL));
    
    playerInit(&game->player);
    itemsInit(&game->items);
    
    game->running = 1;
    game->timer = 0;
    
    screenInit(1);
    keyboardInit();
    timerInit(50);
}

void updateGameState(Game* game) {
    if (game->player.score >= game->player.level * LEVEL_UP_POINTS) {
        increasePlayerLevel(&game->player);
    }

    game->timer += 50;
    if (game->timer - game->player.lastDifficultyIncrease > DIFFICULTY_INTERVAL) {
        game->player.speed = (game->player.speed - 50 < MIN_SPEED) ? MIN_SPEED : game->player.speed - 50;
        game->player.lastDifficultyIncrease = game->timer;
    }

    if (game->timer - game->player.lastMoveTime > game->player.speed) {
        game->player.lastMoveTime = game->timer;
        updateItems(&game->items, &game->player, &game->running);
    }
}

void gameRun(Game* game) {
    char playerName[MAX_NAME_LENGTH] = {0};
    
    showWelcomeScreen();
    getPlayerName(playerName);
    showTopScores();
    
    gameInit(game);
    
    while (game->running) {
        if (timerTimeOver()) {
            game->timer += 50;
            
            handlePlayerInput(&game->player, &game->running);
            updateGameState(game);
            
            if (shouldSpawnItem(game->timer, game->items.lastSpawnTime)) {
                spawnItem(&game->items, game->player.level);
                game->items.lastSpawnTime = game->timer;
            }
            
            drawGameScreen(game);
        }
    }
    
    saveScore(playerName, game->player.score, game->player.level);
    showGameOverScreen(game->player.score, game->player.level);
    showTopScores();
}

void gameDestroy(Game* game) {
    keyboardDestroy();
    screenDestroy();
}