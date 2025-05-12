#include "items.h"
#include <stdlib.h>
#include <time.h>
#include <string.h>

void itemsInit(ItemManager* manager) {
    memset(manager->items, 0, sizeof(Item) * MAX_ITEMS);
    manager->lastSpawnTime = 0;
}

void spawnItem(ItemManager* manager, int level) {
    if (rand() % 100 > (40 + level * 2)) return;

    for (int i = 0; i < MAX_ITEMS; i++) {
        if (!manager->items[i].active) {
            manager->items[i].type = (rand() % 100 < (60 - level * 2)) ? GOOD_ITEM_CHAR : BAD_ITEM_CHAR;
            manager->items[i].x = SCRSTARTX + (rand() % (SCRENDX - SCRSTARTX + 1));
            manager->items[i].y = SCRSTARTY;
            manager->items[i].active = 1;
            break;
        }
    }
}

void updateItems(ItemManager* manager, Player* player, int* running) {
    for (int i = 0; i < MAX_ITEMS; i++) {
        if (manager->items[i].active) {
            manager->items[i].y++;
            
            if (manager->items[i].y >= MAXY) {
                manager->items[i].active = 0;
                continue;
            }
            
            if (manager->items[i].y == player->y && manager->items[i].x == player->x) {
                if (manager->items[i].type == GOOD_ITEM_CHAR) {
                    player->score += 10;
                } else {
                    player->lives--;
                    if (player->lives <= 0) *running = 0;
                }
                manager->items[i].active = 0;
            }
        }
    }
}

int shouldSpawnItem(long currentTime, long lastSpawnTime) {
    return (currentTime - lastSpawnTime > SPAWN_INTERVAL);
}