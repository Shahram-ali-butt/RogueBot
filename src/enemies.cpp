#include <iostream>
#include <windows.h>
#include "enemies.h"
#include "config.h"
#include "bullets.h"
#include "audio.h"
#include "console.h"

using namespace std;

int enemyToWallMap[7] = {1, -1, 2, 3, 4, -1, -1};


const int eWidth = 8, eHeight = 5;

void drawEnemyHealth(int enemyData[][enemyDataCols]){
    if (currentEnemy == -1) return;
    if (enemyData[currentEnemy][2] == 1) return;

    int health = enemyData[currentEnemy][6];
    int maxHealth = 100;

    drawHealthBar(eHBarX, eHBarY, health, maxHealth, "ENEMY ");
}



void controlEnemies(int enemyData[][enemyDataCols], int enemyLimit){
    int isKilled, moving, limitedMovement, horizontalMovement, startingCoord, limit, ex, ey, direction;
    
    for(int i = 0; i < enemyLimit; i++){
        ex = enemyData[i][0];
        ey = enemyData[i][1];
        isKilled = enemyData[i][2];
        moving = enemyData[i][3];
        direction = enemyData[i][4];
        startingCoord = enemyData[i][5];
        limit = enemyData[i][17];

        if(isKilled == 1){ //Killed
            continue;
        }

        if(moving){
            eraseEnemyAt(ex, ey);
            // moveEnemyH(ex, ey, direction, startingCoord);
            moveEnemyLimitedH(ex, ey, direction, startingCoord, limit);
        }

        enemyData[i][0] = ex;
        enemyData[i][1] = ey;
        enemyData[i][4] = direction;
    }
}

void eraseEnemyAt(int x, int y){
    for(int r = 0; r < eHeight; r++){
        gotoxy(x, y + r);
        cout << string(eWidth, ' ');
    }
}
 


void printAllEnemies(int enemyData[][enemyDataCols], int enemyLimit){
    generateColors(enemyColor);
    for(int i = 0; i < enemyLimit; i++){
        if(enemyData[i][2] == 0)
            printEnemy(enemyData[i][0], enemyData[i][1]);
    }
}

void eraseAllEnemies(int enemyData[][enemyDataCols], int enemyLimit){
    for(int i = 0; i < enemyLimit; i++){
        if (enemyData[i][2] == 0) { // alive only
            eraseEnemy(enemyData[i][0], enemyData[i][1]);
        }
    }
}



void handleBulletEnemyCollision(int playerBulletData[][playerBulletDataCols], int &playerBulletCount, int enemyData[][enemyDataCols], int vWallData[][vWallDataCols], int enemyLimit){
    for (int b = 0; b < playerBulletCount; b++) {

        int bx = playerBulletData[b][0];
        int by = playerBulletData[b][1];

        for (int e = 0; e < enemyLimit; e++) {

            if (enemyData[e][2] == 1) continue;

            int ex = enemyData[e][0];
            int ey = enemyData[e][1];
            int &health = enemyData[e][6];
            int damage = enemyData[e][7];

            if (bx >= ex && bx < ex + eWidth &&
                by >= ey && by < ey + eHeight){
        
                playerBulletData[b][0] = playerBulletData[playerBulletCount - 1][0];
                playerBulletData[b][1] = playerBulletData[playerBulletCount - 1][1];
                playerBulletCount--;
                b--;

                health -= damage;
                currentEnemy = e;
                eraseHealthBar(eHBarX, eHBarY);

                if (health <= 0) {
                    health = 0;
                    eraseEnemy(enemyData[e][0], enemyData[e][1]);
                    drawHealthBar(eHBarX, eHBarY, 0, 100, "ENEMY ");
                    enemyData[e][2] = 1;
                    enemyCount--;
                    playDeathSound();

                    // vWalls Handling
                    if(enemyToWallMap[e] != -1){
                        int wallIndex = enemyToWallMap[e];
                        if (vWallData[wallIndex][3] == 1) {
                            eraseVWall(
                                vWallData[wallIndex][0],
                                vWallData[wallIndex][1],
                                vWallData[wallIndex][2]
                            );
                            vWallData[wallIndex][3] = 0;
                        }
                    }
                }

                break;
            }
        }
    }
}

void eraseVWall(int x, int y, int height) {
    for(int i = 0; i < height; i++){
        gotoxy(x, y + i);
        cout << " ";
    }
}


//            0  1    2       3          4         5        6        7         8         
// enemyData (x, y, killed, moving, direction, startingX, health, damage , activated, 
//     9              10                  11          12            13           14            15       16         17
// fireRate, fireDirection(1L, -1R)), burstLimit, burstCount, fireCooldown, burstCooldown, burstDelay, floor, movementLimit

void enemyFire(int enemyData[][enemyDataCols], int enemyLimit, int enemyBulletData[][bulletDataCols], int &enemyBulletCount){
    for (int i = 0; i < enemyLimit; i++) {

        if (enemyData[i][2] == 1) continue;
        if (enemyData[i][8] == 0) continue; 

        int fireRate = enemyData[i][9];
        int fireDir = enemyData[i][10];
        int burstLimit = enemyData[i][11];
        int &burstCount = enemyData[i][12];
        int &fireCooldown = enemyData[i][13];
        int &burstCooldown = enemyData[i][14];
        int burstDelay = enemyData[i][15];

        if (burstCount >= burstLimit){
            if (burstCooldown > 0) {
                burstCooldown--;
                continue;
            }
            burstCount = 0;
            burstCooldown = burstDelay;
            fireCooldown = fireRate;
            continue;
        }

        // fire cooldown
        if (fireCooldown > 0){
            fireCooldown--;
            continue;
        }

        if (enemyBulletCount >= bulletLimit)
            continue;

        int ex = enemyData[i][0];
        int ey = enemyData[i][1];
        int bx;

        if(fireDir == 1){ 
            bx = ex + eWidth;
        }else 
            bx = ex - 1;

        generateColors(eBulletColor);
        
        playEnemyShootSound();
        createEnemyBullet(bx, ey + 3, fireDir, enemyBulletData, enemyBulletCount);

        burstCount++;
        fireCooldown = fireRate;
    }
}

void moveEnemyBullets(int enemyBulletData[][bulletDataCols], int &enemyBulletCount){
    for (int i = 0; i < enemyBulletCount; i++) {

        int &x   = enemyBulletData[i][0];
        int y    = enemyBulletData[i][1];
        int dir  = enemyBulletData[i][2];

        int nextX = x + dir;

        if (getCharAtxy(nextX, y) == ' ') {
            x = nextX;
        }
        else {
            eraseBullet(x, y);

            enemyBulletData[i][0] = enemyBulletData[enemyBulletCount - 1][0];
            enemyBulletData[i][1] = enemyBulletData[enemyBulletCount - 1][1];
            enemyBulletData[i][2] = enemyBulletData[enemyBulletCount - 1][2];

            enemyBulletCount--;
            i--;
        }
    }
}

void createEnemyBullet(int x, int y, int dir, int bulletData[][bulletDataCols], int &bulletCount){
    bulletData[bulletCount][0] = x;
    bulletData[bulletCount][1] = y;
    bulletData[bulletCount][2] = dir; // -1 or +1
    bulletCount++;
}

void eraseAllEnemyBullets(int enemyBulletData[][bulletDataCols], int &enemyBulletCount){
    for(int i = 0; i < enemyBulletCount; i++){
        eraseBullet(enemyBulletData[i][0], enemyBulletData[i][1]);
    }
}

void printAllEnemyBullets(int enemyBulletData[][bulletDataCols], int &enemyBulletCount){
    generateColors(eBulletColor);
    for(int i = 0; i < enemyBulletCount; i++){
        if (enemyBulletData[i][0] <= 0 || enemyBulletData[i][1] <= 0) continue;
        printBullet(enemyBulletData[i][0], enemyBulletData[i][1]);
    }
}



void activateEnemies(int enemyData[][enemyDataCols], int enemyLimit){
    for (int i = 0; i < enemyLimit; i++) {

        if (enemyData[i][2] == 1) continue; // killed

        int enemyFloor = enemyData[i][16];

        if (currentFloor >= enemyFloor) {
            enemyData[i][8]  = 1;
            // activateEnemy(enemyData[i]);
        }
    }
}

void activateEnemy(int enemy[]){
    enemy[8]  = 1;       
    enemy[12] = 0;       
    enemy[13] = enemy[9];
    enemy[14] = enemy[15];
}



void printEnemy(int &ex, int &ey) {
    char enemy[][eWidth] = {
        {" \\_=_/ "},
        {" (o_o) "},
        {" |[X]| "},
        {" /|||\\ "},
        {"  ---  "}
    };

    generateColors(enemyColor);
    for(int row = 0; row < eHeight; row++){
        gotoxy(ex, ey + row);
        for(int col = 0; col < eWidth; col++){
            cout << enemy[row][col];
        }
    }
}

void eraseEnemy(int &ex, int &ey){
    for(int row = 0; row < eHeight; row++){
        gotoxy(ex, ey + row);
        cout << "       ";
    }
}

bool enemyHitsVWall(int nextX, int ey, int direction) {
    int checkX;

    if(direction == 1)
        checkX = nextX + eWidth;
    else 
        checkX = nextX - 1;

    for (int row = 0; row < eHeight; row++) {
        if (getCharAtxy(checkX, ey + row) != ' ') {
            return true;
        }
    }
    return false;
}

void moveEnemyH(int &ex, int &ey, int &direction, int startingX) {
    int nextX = ex + direction;

    if (enemyHitsVWall(nextX, ey, direction)) {
        direction *= -1;
        nextX = ex + direction;
    }
    if (direction == -1 && ex <= startingX) {
        direction *= -1;
        nextX = ex + direction;
    }
    ex = nextX;

}


void moveEnemyLimitedH(int &ex, int &ey, int &direction, int startingX, int limit) {
    int nextX = ex + direction;

    if (enemyHitsVWall(nextX, ey, direction)) {
        direction *= -1;
        nextX = ex + direction;
    }

    if (direction == -1 && nextX <= startingX) {
        direction *= -1;
        nextX = ex + direction;
    }

    if (direction == 1 && nextX + eWidth >= limit) {
        direction *= -1;
        nextX = ex + direction;
    }

    ex = nextX;
}



