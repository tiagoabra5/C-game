#include "game.h"
#include <stdlib.h>

void handleInput(GameState *game);

int main() {
    cli_init();
    cli_hidecursor();
    
    GameState game;
    initGame(&game);
    
    while (1) {
        handleInput(&game);
        updateGame(&game);
        renderGame(&game);
        cli_sleep(10);
    }
    
    cleanupGame(&game);
    cli_showcursor();
    return 0;
}

void handleInput(GameState *game) {
    if (cli_kbhit()) {
        char key = cli_getch();
        switch (key) {
            case 'a':
                movePlayer(&game->player, -1);
                break;
            case 'd':
                movePlayer(&game->player, 1);
                break;
            case 'r':
                if (game->player.gameOver) {
                    cleanupGame(game);
                    initGame(game);
                }
                break;
            case 'p':
                game->paused = !game->paused;
                break;
            case 'q':
                cleanupGame(game);
                cli_showcursor();
                exit(0);
                break;
        }
    }
}
