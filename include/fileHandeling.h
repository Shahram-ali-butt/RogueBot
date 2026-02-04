#ifndef FILEHANDELING_H
#define FILEHANDELING_H

#include <string>

void savePrevPlayerData(int px, int py, int currentFloor, bool onGround, bool onLadder, 
    bool ladderExitLock, float vy, int groundY, int health, int currentEnemy, bool won, int damageDealt, int enemyCount, int vWallCount);
void loadPrevPlayerData(int &px, int &py, int &currentFloor, bool &onGround, bool &onLadder, 
    bool &ladderExitLock, float &vy, int &groundY, int &health, int &currentEnemy, bool &won, int &damageDealt, int &enemyCount, int &vWallCount);
void loadDefaultPlayerData(int &px, int &py, int &currentFloor, bool &onGround, bool &onLadder, 
    bool &ladderExitLock, float &vy, int &groundY, int &health, int &currentEnemy, bool &won, int &damageDealt, int &enemyCount, int &vWallCount);

void savePrevEnemiesData(int enemyData[][enemyDataCols], int enemyLimit, int enemyDataCols);
void loadPrevEnemiesData(int enemyData[][enemyDataCols], int enemyLimit, int enemyDataCols);
void loadDefaultEnemiesData(int enemyData[][enemyDataCols], int enemyLimit, int enemyDataCols);

void savePrevVWallData(int vWallData[][vWallDataCols], int vWallMax, int vWallDataCols);
void loadPrevVWallData(int vWallData[][vWallDataCols], int vWallMax, int vWallDataCols);
void loadDefaultvWallData(int vWallData[][vWallDataCols], int vWallMax, int vWallDataCols);

void loadPrevPlayerBullet(int playerBulletData[][playerBulletDataCols], int playerBulletCount, int playerBulletDataCols);
void savePrevPlayerBullet(int playerBulletData[][playerBulletDataCols], int playerBulletCount, int playerBulletDataCols);
void loadPrevEnemyBullet(int enemyBulletData[][bulletDataCols], int enemyBulletCount, int bulletDataCols);
void savePrevEnemyBullet(int enemyBulletData[][bulletDataCols], int enemyBulletCount, int bulletDataCols);

void resetEnemyBullets(int enemyBulletData[][bulletDataCols], int enemyBulletCount, int bulletDataCols);
void resetPlayerBullets(int playerBulletData[][playerBulletDataCols], int playerBulletCount, int playerBulletDataCols);

#endif 