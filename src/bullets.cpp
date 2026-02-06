#include <iostream>
#include "console.h"
#include "config.h"
#include "bullets.h"
using namespace std;

void drawHealthBar(int x, int y, int current, const int max, string label){
    int filled = (current * healthBarWidth) / max;

    generateColors(whiteColor);
    gotoxy(x, y);
    cout << " " << label << " [";
    
    (current <= 30) ?  generateColors(redColor) : generateColors(whiteColor);
    for (int i = 0; i < healthBarWidth; i++){
        if (i < filled) cout << "#";
        else cout << " ";
    }
    
    generateColors(whiteColor);
    cout << "] " << current << "/" << max << " ";
}

void eraseHealthBar(int barX, int barY){
    gotoxy(barX, barY);
    cout << string(37, '#');
}

void createBullet(int x, int y, int bulletData[][playerBulletDataCols], int &bulletCount){
    bulletData[bulletCount][0] = x;
    bulletData[bulletCount][1] = y;
    bulletCount++;
}

void moveBulletLeft(int bulletData[][playerBulletDataCols], int &bulletCount){
    int bX, bY;
    for (int i = 0; i < bulletCount; i++){

        bX = bulletData[i][0];
        bY = bulletData[i][1];

        if (getCharAtxy(bX - 1, bY) == ' '){
            bX--;
            bulletData[i][0] = bX;

        }
        else{
            bulletData[i][0] = bulletData[bulletCount - 1][0];
            bulletData[i][1] = bulletData[bulletCount - 1][1];
            bulletCount--;
            i--;
        }
    }
}

void moveBulletRight(int bulletData[][playerBulletDataCols], int &bulletCount){
    int bX, bY;
    for (int i = 0; i < bulletCount; i++){

        bX = bulletData[i][0];
        bY = bulletData[i][1];

        if (getCharAtxy(bX + 1, bY) == ' '){
            bX++;
            bulletData[i][0] = bX;

        }
        else{
            bulletData[i][0] = bulletData[bulletCount - 1][0];
            bulletData[i][1] = bulletData[bulletCount - 1][1];
            bulletCount--;
            i--;
        }
    }
}

void printBullet(int x, int y){
    gotoxy(x, y);
    cout << ".";
}

void eraseBullet(int x, int y){
    gotoxy(x, y);
    cout << " ";
}
