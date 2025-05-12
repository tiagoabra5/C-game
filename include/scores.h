#ifndef __SCORES_H__
#define __SCORES_H__

#include "screen.h"
#include "keyboard.h"

#define MAX_SCORES 5
#define MAX_NAME_LENGTH 50
#define SCORES_FILE "data/scores.txt"

typedef struct {
    char name[MAX_NAME_LENGTH];
    int score;
    int level;
} PlayerScore;

void initDataDirectory();
void saveScore(const char* name, int score, int level);
void showTopScores();
int getPlayerName(char* name);

#endif /* __SCORES_H__ */