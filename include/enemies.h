#ifndef ENEMIES_H
#define ENEMIES_H

#include "config.h"
using namespace std;

void drawEnemyHealth(int enemyData[][enemyDataCols]);

void controlEnemies(int enemyData[][enemyDataCols], int enemyLimit);
void eraseEnemyAt(int x, int y);

void handleBulletEnemyCollision(int playerBulletData[][playerBulletDataCols], int &playerBulletCount, int enemyData[][enemyDataCols], int vWallData[][vWallDataCols], int enemyLimit);
void eraseVWall(int x, int y, int height);

void printAllEnemies(int enemyData[][enemyDataCols], int enemyLimit);
void eraseAllEnemies(int enemyData[][enemyDataCols], int enemyLimit);

void activateEnemies(int enemyData[][enemyDataCols], int enemyLimit);
void activateEnemy(int enemy[]);

void enemyFire(int enemyData[][enemyDataCols], int enemyLimit, int enemyBulletData[][bulletDataCols], int &enemyBulletCount);
void moveEnemyBullets(int enemyBulletData[][bulletDataCols], int &enemyBulletCount);
void createEnemyBullet(int x, int y, int dir, int bulletData[][bulletDataCols], int &bulletCount);

void eraseAllEnemyBullets(int enemyBulletData[][bulletDataCols], int &enemyBulletCount);
void printAllEnemyBullets(int enemyBulletData[][bulletDataCols], int &enemyBulletCount);

// Logging
void printEnemy(int &ex, int &ey);
void eraseEnemy(int &ex, int &ey);

// Movement
void moveEnemyLimitedH(int &ex, int &ey, int &direction, int startingX, int limit);
void moveEnemyH(int &ex, int &ey, int &direction, int startingX);

#endif