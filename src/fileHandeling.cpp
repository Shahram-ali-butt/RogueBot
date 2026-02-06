#include <iostream>
#include <limits>
#include <fstream>
#include <sstream>
#include "config.h"
#include "console.h"
#include "fileHandeling.h"
using namespace std;

string base = getExeDir();

string prevPlayerFile = base + "/data/prevPlayer.txt";
string prevEnemiesFile = base + "/data/prevEnemies.txt";
string defaultPlayerFile = base + "/data/defaultPlayer.txt";
string defaultEnemiesFile = base + "/data/defaultEnemies.txt";

string prevPlayerBulletFile = base + "/data/prevPlayerBullets.txt";
string prevEnemiesBulletFile = base + "/data/prevEnemiesBullets.txt";

string prevVWallDataFile = base + "/data/prevVWallData.txt";
string defaultVWallDataFile = base + "/data/defaultVWallData.txt";


void savePrevPlayerData(int px, int py, int currentFloor, bool onGround, bool onLadder, bool ladderExitLock, 
    float vy, int groundY, int health, int currentEnemy, bool won, int damageDealt, int enemyCount, int vWallCount){
    ofstream ofile(prevPlayerFile);
    if(!ofile){
        cout << "File: " << prevPlayerFile << " not found" << endl;
        system("pause");
    }

    ofile << px << ' ' << py << ' ' << currentFloor << ' ' << onGround << ' ' 
    << onLadder << ' ' << ladderExitLock << ' ' << vy << ' ' << groundY << ' ' 
    << health << ' ' << currentEnemy << ' ' << won << ' ' << damageDealt << ' ' << enemyCount << ' ' << vWallCount << ' '; 

    ofile.close();
}

void loadPrevPlayerData(int &px, int &py, int &currentFloor, bool &onGround, bool &onLadder, bool &ladderExitLock, 
    float &vy, int &groundY, int &health, int &currentEnemy, bool &won, int &damageDealt, int &enemyCount, int &vWallCount){
    ifstream ifile(prevPlayerFile);
    if(!ifile){
        cout << "File: " << prevPlayerFile << " not found" << endl;
        system("pause");
    }

    ifile >> px >> py >> currentFloor >> onGround >> onLadder >> ladderExitLock >> vy >> groundY 
    >> health >> currentEnemy >> won >> damageDealt >> enemyCount >> vWallCount;

    ifile.close();
}

void loadDefaultPlayerData(int &px, int &py, int &currentFloor, bool &onGround, bool &onLadder, bool &ladderExitLock, 
    float &vy, int &groundY, int &health, int &currentEnemy, bool &won, int &damageDealt, int &enemyCount, int &vWallCount){
    ifstream ifile(defaultPlayerFile);
    if(!ifile){
        cout << "File: " << defaultPlayerFile << " not found" << endl;
        system("pause");
    }

    ifile >> px >> py >> currentFloor >> onGround >> onLadder >> ladderExitLock >> vy >> groundY 
    >> health >> currentEnemy >> won >> damageDealt >> enemyCount >> vWallCount;

    ifile.close();
}


void savePrevEnemiesData(int enemyData[][enemyDataCols], int enemyLimit, int enemyDataCols){
    ofstream ofile(prevEnemiesFile);
    if(!ofile){
        cout << "File: " << prevEnemiesFile << " not found" << endl;
        system("pause");
    }

    for(int e = 0; e < enemyLimit; e++){
        for(int col = 0; col < enemyDataCols; col++){
            ofile << enemyData[e][col] << " ";
        }
        ofile << '\n';
    }

    ofile.close();
}

void loadPrevEnemiesData(int enemyData[][enemyDataCols], int enemyLimit, int enemyDataCols){
    ifstream ifile(prevEnemiesFile);
    if(!ifile){
        cout << "File: " << prevEnemiesFile << " not found" << endl;
        system("pause");
    }

    for(int e = 0; e < enemyLimit; e++){
        for(int col = 0; col < enemyDataCols; col++){
            ifile >> enemyData[e][col];
        }
    }

    ifile.close();
}

void loadDefaultEnemiesData(int enemyData[][enemyDataCols], int enemyLimit, int enemyDataCols){
    ifstream ifile(defaultEnemiesFile);
    if(!ifile){
        cout << "File: " << defaultEnemiesFile << " not found" << endl;
        system("pause");
    }

    for(int e = 0; e < enemyLimit; e++){
        for(int col = 0; col < enemyDataCols; col++){
            ifile >> enemyData[e][col];
        }
    }

    ifile.close();
}


void savePrevVWallData(int vWallData[][vWallDataCols], int vWallMax, int vWallDataCols){
    ofstream ofile(prevVWallDataFile);
    if(!ofile){
        cout << "File: " << prevVWallDataFile << " not found" << endl;
        system("pause");
    }

    for(int e = 0; e < vWallMax; e++){
        for(int col = 0; col < vWallDataCols; col++){
            ofile << vWallData[e][col] << " ";
        }
        ofile << '\n';
    }

    ofile.close();
}

void loadPrevVWallData(int vWallData[][vWallDataCols], int vWallMax, int vWallDataCols){
    ifstream ifile(prevVWallDataFile);
    if(!ifile){
        cout << "File: " << prevVWallDataFile << " not found" << endl;
        system("pause");
    }

    for(int e = 0; e < vWallMax; e++){
        for(int col = 0; col < vWallDataCols; col++){
            ifile >> vWallData[e][col];
        }
    }

    ifile.close();
}

void loadDefaultvWallData(int vWallData[][vWallDataCols], int vWallMax, int vWallDataCols){
    ifstream ifile(defaultVWallDataFile);
    if(!ifile){
        cout << "File: " << defaultVWallDataFile << " not found" << endl;
        system("pause");
    }

    for(int e = 0; e < vWallMax; e++){
        for(int col = 0; col < vWallDataCols; col++){
            ifile >> vWallData[e][col];
        }
    }

    ifile.close();
}


void savePrevEnemyBullet(int enemyBulletData[][bulletDataCols], int enemyBulletCount, int bulletDataCols){
    ofstream ofile(prevEnemiesBulletFile);
    if(!ofile){
        cout << "File: " << prevEnemiesBulletFile << " not found" << endl;
        system("pause");
    }

    for(int b = 0; b < enemyBulletCount; b++){
        for(int col = 0; col < bulletDataCols; col++){
            ofile << enemyBulletData[b][col] << " ";
        }
        ofile << '\n';
    }

    ofile.close();
}

void loadPrevEnemyBullet(int enemyBulletData[][bulletDataCols], int enemyBulletCount, int bulletDataCols){
    ifstream ifile(prevEnemiesBulletFile);
    if(!ifile){
        cout << "File: " << prevEnemiesBulletFile << " not found" << endl;
        system("pause");
    }

    for(int e = 0; e < enemyBulletCount; e++){
        for(int col = 0; col < bulletDataCols; col++){
            ifile >> enemyBulletData[e][col];
        }
    }

    ifile.close();
}


void savePrevPlayerBullet(int playerBulletData[][playerBulletDataCols], int playerBulletCount, int playerBulletDataCols){
    ofstream ofile(prevPlayerBulletFile);
    if(!ofile){
        cout << "File: " << prevPlayerBulletFile << " not found" << endl;
        system("pause");
    }

    for(int b = 0; b < playerBulletCount; b++){
        for(int col = 0; col < playerBulletDataCols; col++){
            ofile << playerBulletData[b][col] << " ";
        }
        ofile << '\n';
    }

    ofile.close();
}

void loadPrevPlayerBullet(int playerBulletData[][playerBulletDataCols], int playerBulletCount, int playerBulletDataCols){
    ifstream ifile(prevPlayerBulletFile);
    if(!ifile){
        cout << "File: " << prevPlayerBulletFile << " not found" << endl;
        system("pause");
    }

    for(int b = 0; b < playerBulletCount; b++){
        for(int col = 0; col < playerBulletDataCols; col++){
            ifile >> playerBulletData[b][col];
        }
    }

    ifile.close();
}


void resetEnemyBullets(int enemyBulletData[][bulletDataCols], int enemyBulletCount, int bulletDataCols){
    for (int i = 0; i < enemyBulletCount; i++) {
        for (int j = 0; j < bulletDataCols; j++) {
            enemyBulletData[i][j] = 0;
        }
    }
}

void resetPlayerBullets(int playerBulletData[][playerBulletDataCols], int playerBulletCount, int playerBulletDataCols){
    for (int i = 0; i < playerBulletCount; i++) {
        for (int j = 0; j < playerBulletDataCols; j++) {
            playerBulletData[i][j] = 0;
        }
    }
}

