#ifndef CONFIG_H
#define CONFIG_H

// constants
const int boundaryLength = 192;
const int boundaryHeight = 49;

const int ladderHight = 12;
const int ladderWidth = 12;

const int hWallDataCols = 3;
const int ladderDataCols = 2;

const int bulletLimit = 50;
const int bulletDataCols = 3; // x, y, direction
const int playerBulletDataCols = 2; // x, y

const int vWallDataCols = 4;
const int vWallMax = 5;

const int enemyDataCols = 18;
const int enemyLimit = 7;


// Health Bars
const int healthBarWidth = 20;

const int eHBarX = 151;
const int eHBarY = 0;
const int pHBarX = 3;
const int pHBarY = 0;

const int maxPlayerHealth = 100;


// player state 
extern int px, py;
extern int currentFloor;
extern bool onGround, onLadder, ladderExitLock;
extern float vy;
extern int groundY;
extern int health;
extern int currentEnemy;
extern bool won;
extern int damageDealt;
extern int enemyCount;
extern int vWallCount;

extern bool firstJump;


// enemy data

extern int enemyData[enemyLimit][enemyDataCols];
extern int enemyCount;


// bullets
extern int playerBulletData[bulletLimit][playerBulletDataCols];
extern int playerBulletCount;
extern int enemyBulletData[bulletLimit][bulletDataCols];
extern int enemyBulletCount;
extern int vWallData[vWallMax][vWallDataCols]; 
extern int vWallCount;


// Colors 
const int redColor = 4;
const int whiteColor = 7;
const int greenColor = 10;
const int purpleColor = 13;

// UI colors
const int textColor      = 7;   
const int boundaryColor  = 8;   

// Player colors
const int playerColor    = 10;  
const int pBulletColor   = 7;  
const int pHBarColor     = 7;  

// Enemies colors
const int enemyColor     = 13;  
const int eBulletColor   = 4;  
const int eHBarColor     = 12;  

// Environment colors
const int vWallColor     = 8;

#endif
