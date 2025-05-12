#include "game.h"

int main() {
    Game game;
    
    gameInit(&game);
    gameRun(&game);
    gameDestroy(&game);
    
    return 0;
}