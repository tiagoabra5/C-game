#include "ui.h"
#include "keyboard.h"
#include "game.h"

void showWelcomeScreen() {
    screenClear();
    
    screenSetColor(CYAN, BLACK);
    screenGotoxy(MAXX/2 - 15, MINY + 3);
    printf("   _____   _____  _      _      _____ ");
    screenGotoxy(MAXX/2 - 15, MINY + 4);
    printf("  / ____| / ____|| |    | |    / ____|");
    screenGotoxy(MAXX/2 - 15, MINY + 5);
    printf(" | (___  | |     | |    | |   | |     ");
    screenGotoxy(MAXX/2 - 15, MINY + 6);
    printf("  \\___ \\ | |     | |    | |   | |     ");
    screenGotoxy(MAXX/2 - 15, MINY + 7);
    printf("  ____) || |____ | |____| |___| |____ ");
    screenGotoxy(MAXX/2 - 15, MINY + 8);
    printf(" |_____/  \\_____||______|______\\_____|");
    
    screenSetColor(LIGHTGREEN, BLACK);
    screenGotoxy(MAXX/2 - 15, MAXY/2);
    printf("┌─────────────────────────────────────┐");
    screenGotoxy(MAXX/2 - 15, MAXY/2 + 1);
    printf("│  Digite seu nome e pressione ENTER: │");
    screenGotoxy(MAXX/2 - 15, MAXY/2 + 2);
    printf("└─────────────────────────────────────┘");
    
    screenGotoxy(MAXX/2 - 10, MAXY/2 + 4);
    screenUpdate();
}

void drawGameScreen(Game* game) {
    screenClear();
    
    screenSetColor(LIGHTCYAN, BLACK);
    
    screenGotoxy(SCRSTARTX-1, SCRSTARTY-1);
    printf("╔");
    for (int i = SCRSTARTX; i <= SCRENDX; i++) printf("═");
    printf("╗");
    
    for (int i = SCRSTARTY; i <= SCRENDY; i++) {
        screenGotoxy(SCRSTARTX-1, i); printf("║");
        screenGotoxy(SCRENDX+1, i); printf("║");
    }
    
    screenGotoxy(SCRSTARTX-1, SCRENDY+1);
    printf("╚");
    for (int i = SCRSTARTX; i <= SCRENDX; i++) printf("═");
    printf("╝");
    
    screenSetColor(LIGHTCYAN, BLACK);
    int playerX = (game->player.x < SCRSTARTX) ? SCRSTARTX : 
                 (game->player.x > SCRENDX) ? SCRENDX : game->player.x;
    int playerY = (game->player.y < SCRSTARTY) ? SCRSTARTY : 
                 (game->player.y > SCRENDY) ? SCRENDY : game->player.y;
    
    screenGotoxy(playerX, playerY);
    printf("☻");
    
    for (int i = 0; i < MAX_ITEMS; i++) {
        if (game->items.items[i].active) {
            if (game->items.items[i].type == GOOD_ITEM_CHAR) {
                screenSetColor(LIGHTGREEN, BLACK);
                screenGotoxy(game->items.items[i].x, game->items.items[i].y);
                printf("★");
            } 
            else {
                screenSetColor(LIGHTRED, BLACK);
                screenGotoxy(game->items.items[i].x, game->items.items[i].y);
                printf("☠");
            }
        }
    }
    
    drawHUD(&game->player);
    screenUpdate();
}

void drawHUD(const Player* player) {
    screenSetColor(WHITE, BLACK);
    
    screenGotoxy(SCRSTARTX, SCRENDY+2);
    printf("Score: %-6d   Level: %-2d   Lives: ", player->score, player->level);
    
    screenSetColor(LIGHTRED, BLACK);
    for (int i = 0; i < player->lives; i++) {
        printf("♥ ");
    }
}

void showGameOverScreen(int score, int level) {
    screenSetColor(RED, BLACK);
    screenGotoxy(MAXX/2 - 10, MAXY/2 - 2);
    printf("┌──────────────────────┐");
    screenGotoxy(MAXX/2 - 10, MAXY/2 - 1);
    printf("│      GAME OVER       │");
    screenGotoxy(MAXX/2 - 10, MAXY/2);
    printf("├──────────────────────┤");
    
    screenSetColor(WHITE, BLACK);
    screenGotoxy(MAXX/2 - 10, MAXY/2 + 1);
    printf("│   Score: %-11d  │", score);
    screenGotoxy(MAXX/2 - 10, MAXY/2 + 2);
    printf("│   Level: %-11d  │", level);
    screenGotoxy(MAXX/2 - 10, MAXY/2 + 3);
    printf("└──────────────────────┘");
    
    screenSetColor(YELLOW, BLACK);
    screenGotoxy(MAXX/2 - 15, MAXY - 2);
    printf("Pressione qualquer tecla para voltar ao menu...");
    
    screenUpdate();
    
    while (!keyhit()) {}
    readch();
}