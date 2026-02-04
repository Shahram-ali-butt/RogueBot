#ifndef BULLETS_H
#define BULLETS_H

void printBullet(int x, int y);
void eraseBullet(int x, int y);
void createBullet(int x, int y, int bulletData[][bulletDataCols], int &bulletCount);
void moveBulletLeft(int bulletData[][bulletDataCols], int &bulletCount);
void moveBulletRight(int bulletData[][bulletDataCols], int &bulletCount);
void eraseBullet(int x, int y);

void createBullet(int x, int y, int bulletData[][playerBulletDataCols], int &bulletCount);
void moveBulletLeft(int bulletData[][playerBulletDataCols], int &bulletCount);
void moveBulletRight(int bulletData[][playerBulletDataCols], int &bulletCount);

void drawHealthBar(int x, int y, int current, const int max, std::string label);
void eraseHealthBar(int barX, int barY);

#endif