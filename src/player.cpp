#include <iostream>
#include <windows.h>
#include "config.h"
#include "console.h"
#include "bullets.h"
#include "audio.h"

#include "player.h" 
using namespace std;

void drawPlayerHealth(){
    drawHealthBar(pHBarX, pHBarY, health, maxPlayerHealth, "PLAYER");
}

void handleBulletPlayerCollision(int enemyBulletData[][bulletDataCols], int enemyBulletCount, int px, int py, int &health){
    for (int b = 0; b < enemyBulletCount; b++) {
        int bx = enemyBulletData[b][0];
        int by = enemyBulletData[b][1];

        if (bx >= px && bx < px + 8 &&
            by >= py && by < py + 5){
    
            enemyBulletData[b][0] = enemyBulletData[enemyBulletCount - 1][0];
            enemyBulletData[b][1] = enemyBulletData[enemyBulletCount - 1][1];
            enemyBulletCount--;
            b--;

            health -= damageDealt;
            eraseHealthBar(pHBarX, pHBarY);
            if (health <= 0) {
                health = 0;
                erasePlayer(px, py);
            }
            break;
        }
    }
}


void playerFire(int px, int py, int playerBulletData[][playerBulletDataCols], int &playerBulletCount){
    static int cooldown = 0;
    static int bulletsFiredInBurst = 0;
    static bool isFireSoundPlayed = false;
    static int fireSound = 0;
    const int maxBurst = 5;

    if (!GetAsyncKeyState(VK_SPACE)) {
        bulletsFiredInBurst = 0;
        cooldown = 0;
        fireSound--;
        return;
    }

    if (bulletsFiredInBurst >= maxBurst){
        fireSound--;
        return;
    }
    
    if (cooldown > 0) {
        cooldown--;
        fireSound--;
        return;
    }

    if (playerBulletCount < bulletLimit) {
        if(currentFloor % 2 != 0)
            createBullet(px + 5, py + 2, playerBulletData, playerBulletCount);
        else 
            createBullet(px - 1, py + 2, playerBulletData, playerBulletCount);

        bulletsFiredInBurst++;
        cooldown = 2;
        fireSound++;
    }

    if(fireSound < 5){
        playShootSound();
    }

    if(fireSound >= 5) isFireSoundPlayed = true;
    else if(fireSound <= 0) isFireSoundPlayed = false;
}

void movePlayerBullets(int playerBulletData[][playerBulletDataCols], int &playerBulletCount){
    if(currentFloor % 2 != 0){
        moveBulletRight(playerBulletData, playerBulletCount);
    }else{
        moveBulletLeft(playerBulletData, playerBulletCount);
    }
}

void eraseAllPlayerBullets(int playerBulletData[][playerBulletDataCols], int &playerBulletCount){
    for(int i = 0; i < playerBulletCount; i++){
        eraseBullet(playerBulletData[i][0], playerBulletData[i][1]);
    }
}

void printAllPlayerBullets(int playerBulletData[][playerBulletDataCols], int &playerBulletCount){
    generateColors(pBulletColor);
    for(int i = 0; i < playerBulletCount; i++){
        printBullet(playerBulletData[i][0], playerBulletData[i][1]);
    }
}



void printPlayer(int &px, int &py, int health) {
    char player[][8] = {
        {"  \\_/  "},
        {" (^_^) "},
        {" |[O]| "},
        {"  |||  "},
        {"  ---  "}
    };

    generateColors(playerColor);

    if(health > 0){
        for(int row = 0; row < 5; row++){
            gotoxy(px, py + row);
            for(int col = 0; col < 8; col++){
                cout << player[row][col];
            }
        }
    }
}

void movePlayer(int &px, int &py, int health){
    if ((GetAsyncKeyState(VK_LEFT) && (getCharAtxy(px - 1, py) == ' ' && (getCharAtxy(px - 1, py + 3) == ' ')) || getCharAtxy(px - 1, py) == '|' || getCharAtxy(px - 1, py) == '-')) {
        movePlayerLeft(px, py, health);
    }
    if ((GetAsyncKeyState(VK_RIGHT) && (getCharAtxy(px + 8, py) == ' ' && (getCharAtxy(px + 8, py + 3) == ' '))) || getCharAtxy(px + 8, py) == '|' || getCharAtxy(px + 8, py) == '-') {
        movePlayerRight(px, py, health);
    }
}


void erasePlayer(int &px, int &py){
    for(int row = 0; row < 5; row++){
        gotoxy(px, py + row);
        cout << "        ";
    }
}

void movePlayerLeft(int &px, int &py, int health){
        erasePlayer(px, py);
        px = px - 1;
        printPlayer(px, py, health);
}

void movePlayerRight(int &px, int &py, int health){
        erasePlayer(px, py);
        px = px + 1;
        printPlayer(px, py, health);
}



bool aboveNextGround(int hWallData[][hWallDataCols], int hWallCount, int py, int &nextGroundY){
    int nextFloor = currentFloor + 1;

    if (nextFloor >= hWallCount)
        return false;

    int feetY = py + 5;
    int wallY = hWallData[nextFloor][1];

    if (feetY <= wallY) {
        nextGroundY = wallY;
        return true;
    }

    return false;
}

void moveUpToLadder(int ladderData[][ladderDataCols], int ladderCount, int hWallData[][hWallDataCols], int hWallCount, int px, int &py){
    onLadder = false;

    for (int i = 0; i < ladderCount; i++) {
        int lX = ladderData[i][0];
        int lY = ladderData[i][1];

        bool insideX = (px + 8 > lX && px < lX + ladderWidth);
        bool insideY = (py + 5 > lY && py < lY + ladderHight);

        if (!insideX || !insideY)
            continue;

        onLadder = true;
        vy = 0;
        
        if (GetAsyncKeyState(VK_UP)) {
            int nextGroundY;
            
            if(aboveNextGround(hWallData, hWallCount, py, nextGroundY)) {
                py = nextGroundY - 5;
                groundY = nextGroundY;
                currentFloor++;
                
                onLadder = false;
                onGround = true;
                ladderExitLock = true;
            } else {
                py--;
            }
        }
        else if (GetAsyncKeyState(VK_DOWN) && groundY > py + 5) {
            py++;
        }

        return;
    }
}

void detectGround(int px, int &py, int hWallData[][hWallDataCols], int hWallCount, int vWallData[][vWallDataCols], int vWallMax) {
    int prevBottom = (py - vy) + 4;
    int currBottom = py + 4;
    int counter = 0;

    for (int i = 0; i < vWallMax; i++) {
        if(vWallData[i][3] == 0) continue;

        int wallX = vWallData[i][0];
        int wallTop = vWallData[i][1];

        bool horizontalOverlap =
            (px + 7 >= wallX && px <= wallX);

        if (horizontalOverlap &&
            prevBottom < wallTop &&
            currBottom >= wallTop &&
            vy > 0) {

            py = wallTop - 5;
            vy = 0;
            onGround = true;
            return;
        }
    }

    for (int i = 0; i < hWallCount; i++) {
        int floorY = hWallData[i][1];

        if (prevBottom < floorY &&
            currBottom >= floorY &&
            vy > 0) {

            py = floorY - 5;
            vy = 0;
            onGround = true;
            groundY = floorY;
            currentFloor = i;
            return;
        }
    }

    if (py >= groundY) {
        py = groundY;
        vy = 0;
        onGround = true;
    }
    else {
        onGround = false;
    }
}



void jumpInput(){
    static bool jumpSoundPlayed = false;

    if(ladderExitLock){
        ladderExitLock = false;
        return;
    }

    if(GetAsyncKeyState(VK_UP)) {
        if (onGround && !onLadder) {
            vy = -2.3;
            onGround = false;

            if (!jumpSoundPlayed) {
                playJumpSound();
                jumpSoundPlayed = true;
            }
        }
    }else {
        jumpSoundPlayed = false; // reset when landing
    }

    if(GetAsyncKeyState(VK_DOWN)){
        if (!onGround && !onLadder) {
            vy += 1.2;
        }
    }
}

void playerJump(int &px, int &py, int groundY){
    if(!onGround && !onLadder){
        
        if(getCharAtxy(px, py - 1) != ' '){
            py += 1;
            return;
        }
        vy += 0.6;
        py += vy;

    }
}

