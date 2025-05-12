#ifndef __ITEMS_H__
#define __ITEMS_H__

#include "screen.h"
#include "player.h"

#define GOOD_ITEM_CHAR '+'
#define BAD_ITEM_CHAR 'X'
#define MAX_ITEMS 20
#define SPAWN_INTERVAL 1000

typedef struct {
    int x;
    int y;
    char type;
    int active;
} Item;

typedef struct {
    Item items[MAX_ITEMS];
    long lastSpawnTime;
} ItemManager;

void itemsInit(ItemManager* manager);
void spawnItem(ItemManager* manager, int level);
void updateItems(ItemManager* manager, Player* player, int* running);
int shouldSpawnItem(long currentTime, long lastSpawnTime);

#endif /* __ITEMS_H__ */