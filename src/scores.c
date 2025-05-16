#include "scores.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#ifdef _WIN32
#include <direct.h>
#else
#include <sys/stat.h>
#endif

void initDataDirectory() {
    #ifdef _WIN32
    _mkdir("data");
    #else
    mkdir("data", 0777);
    #endif
}

void saveScore(const char* name, int score, int level) {
    initDataDirectory();
    
    PlayerScore scores[MAX_SCORES + 1]; 
    int count = 0;
    
    FILE* file = fopen(SCORES_FILE, "r");
    if (file) {
        while (count < MAX_SCORES && fscanf(file, "%49s %d %d", 
              scores[count].name, 
              &scores[count].score, 
              &scores[count].level) == 3) {
            count++;
        }
        fclose(file);
    }
    
    strncpy(scores[count].name, name, MAX_NAME_LENGTH);
    scores[count].name[MAX_NAME_LENGTH-1] = '\0';
    scores[count].score = score;
    scores[count].level = level;
    count++;
    
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (scores[j].score < scores[j+1].score) {
                PlayerScore temp = scores[j];
                scores[j] = scores[j+1];
                scores[j+1] = temp;
            }
        }
    }
    
    if (count > MAX_SCORES) {
        count = MAX_SCORES;
    }
    
    file = fopen(SCORES_FILE, "w");
    if (file) {
        for (int i = 0; i < count; i++) {
            fprintf(file, "%s %d %d\n", 
                   scores[i].name, 
                   scores[i].score, 
                   scores[i].level);
        }
        fclose(file);
    }
}

void showTopScores() {
    PlayerScore scores[MAX_SCORES] = {0};
    int count = 0;
    
    FILE* file = fopen(SCORES_FILE, "r");
    if (file) {
        while (count < MAX_SCORES && fscanf(file, "%49s %d %d", 
              scores[count].name, 
              &scores[count].score, 
              &scores[count].level) == 3) {
            count++;
        }
        fclose(file);
    }
    
    screenClear();
    screenSetColor(YELLOW, BLUE);
    screenGotoxy(MAXX/2 - 12, MINY + 1);
    printf("╔══════════════════════════╗");
    screenGotoxy(MAXX/2 - 12, MINY + 2);
    printf("║       TOP 5 JOGADORES    ║");
    screenGotoxy(MAXX/2 - 12, MINY + 3);
    printf("╚══════════════════════════╝");
    
    screenSetColor(WHITE, BLACK);
    for (int i = 0; i < count; i++) {
        screenGotoxy(MAXX/2 - 12, MINY + 5 + i);
        printf("║ %2d. %-15s %6d ║", i+1, scores[i].name, scores[i].score);
    }
    
    for (int i = count; i < MAX_SCORES; i++) {
        screenGotoxy(MAXX/2 - 12, MINY + 5 + i);
        printf("║ %2d. %-15s %6s ║", i+1, "", "");
    }
    
    screenGotoxy(MAXX/2 - 12, MINY + 11);
    printf("╔══════════════════════════╗");
    screenGotoxy(MAXX/2 - 12, MINY + 12);
    printf("║   Pressione qualquer     ║");
    screenGotoxy(MAXX/2 - 12, MINY + 13);
    printf("║      tecla para sair     ║");
    screenGotoxy(MAXX/2 - 12, MINY + 14);
    printf("╚══════════════════════════╝");
    
    screenUpdate();
    
    while (!keyhit()) {}
    readch();
}

int getPlayerName(char* name) {
    int pos = 0;
    screenGotoxy(MAXX/2 - 10, MAXY/2 + 3);
    
    while (1) {
        if (keyhit()) {
            int ch = readch();
            
            if (ch == 10 || ch == 13) {
                name[pos] = '\0';
                return 1;
            }
            else if (ch == 127 && pos > 0) {
                pos--;
                screenGotoxy(MAXX/2 - 10 + pos, MAXY/2 + 3);
                printf(" ");
                screenGotoxy(MAXX/2 - 10 + pos, MAXY/2 + 3);
            }
            else if (pos < MAX_NAME_LENGTH - 1 && ch >= 32 && ch <= 126) {
                name[pos++] = ch;
                printf("%c", ch);
            }
        }
        screenUpdate();
    }
}