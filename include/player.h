#ifndef PLAYER_H
#define PLAYER_H 
#include "config.h"

void drawPlayerHealth();
void handleBulletPlayerCollision(int enemyBulletData[][bulletDataCols], int enemyBulletCount, int px, int py, int &health);

void playerFire(int px, int py, int bulletData[][playerBulletDataCols], int &playerBulletCount);
void movePlayerBullets(int bulletData[][playerBulletDataCols], int &playerBulletCount);
void eraseAllPlayerBullets(int playerBulletData[][playerBulletDataCols], int &playerBulletCount);
void printAllPlayerBullets(int playerBulletData[][playerBulletDataCols], int &playerBulletCount);

void printPlayer(int &px, int &py, int health);
void erasePlayer(int &px, int &py);
void movePlayerLeft(int &px, int &py, int health);
void movePlayerRight(int &px, int &py, int health);
void movePlayer(int &px, int &py, int health);

bool aboveNextGround(int hWallData[][hWallDataCols], int hWallCount, int py, int &nextGroundY);
void moveUpToLadder(int ladderData[][ladderDataCols], int ladderCount, int hWallData[][hWallDataCols], int hWallCount, int px, int &py);
void detectGround(int px, int &py, int hWallData[][hWallDataCols], int hWallCount, int vWallData[][vWallDataCols], int vWallMax);

void jumpInput();
void playerJump(int &px, int &py, int groundY);

#endif