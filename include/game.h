#ifndef GAME_H
#define GAME_H

#include <stdbool.h>
#include <time.h>
#include "cli.h"

// Configurações do jogo
#define WIDTH 80
#define HEIGHT 24
#define MAX_OBJECTS 20
#define INITIAL_LIVES 3
#define BASE_GAME_SPEED 100
#define PLAYER_CHAR 'A'
#define GOOD_OBJ_CHAR '+'
#define BAD_OBJ_CHAR 'X'

// Estruturas do jogo
typedef struct {
    int x, y;
    bool active;
    bool isGood;
    int speed;
} GameObject;

typedef struct {
    int x, y;
    int lives;
    int score;
    bool gameOver;
    time_t startTime;
    time_t survivalTime;
} Player;

typedef struct {
    Player player;
    GameObject *objects;
    int objectCount;
    int gameSpeed;
    clock_t lastUpdate;
    bool paused;
} GameState;

// Funções do jogo
void initGame(GameState *game);
void updateGame(GameState *game);
void handleInput(GameState *game);
void cleanupGame(GameState *game);
void updateDifficulty(GameState *game);

#endif
