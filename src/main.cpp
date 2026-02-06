#include <iostream>
#include <conio.h>
#include <windows.h>
#include "console.h"
#include "config.h"
#include "player.h"
#include "enemies.h"
#include "fileHandeling.h"
#include "audio.h"

using namespace std;

// Config variables
int px = 1, py = 43;

int currentFloor = -1;
bool onGround = true;
bool onLadder = false;
bool ladderExitLock = false;
float vy = 0;
int groundY = 43;
int health = 100;
int currentEnemy = -1;
bool won = false;
int damageDealt = 1;
int enemyCount = 7;
int vWallCount = 5;

bool firstJump = false;

int playerBulletData[bulletLimit][playerBulletDataCols];
int playerBulletCount = 0;

int enemyBulletData[bulletLimit][bulletDataCols];
int enemyBulletCount = 0;

// When inline coloring is needed
const string RED = "\033[31m";
const string GREEN = "\033[32m";
const string PURPLE = "\u001b[35m";
const string GRAY = "\033[30;1m";
const string RESET = "\033[0m";

int enemyData[][enemyDataCols] = {{},{},{},{},{},{},{}};

int vWallData[vWallMax][vWallDataCols] = {{},{},{},{},{}};


// Prototypes
string mainMenu();
void gameStory();
void difficultyChoice();
void adjustDifficulty(string difficulty);
void controls();
void winMenu();
string gameOver();
int pauseMenu();
void printMyName();

void printBoundary();
void printEscapeSign();
void printGameName(int x, int &y);
void printMaze_V1(int hWallData[][hWallDataCols], int hWallCount);   
void drawHWall(int x, int y, int length);

void drawAllVWalls(int vWallData[][vWallDataCols], int vWallMax);
void drawVWall(int x, int y, int height);

void printLadder(int lX, int lY);
void printAllLadders(int ladderData[][ladderDataCols], int ladderCount);



int main() {
    int ranOnce = 0;
    int prevPX, prevPY;
    bool escPressedLastFrame = false;
    
    int hWallData[][hWallDataCols] = {
        {1, 36, 189}, // 1st floor
        {1, 24, 189}, // 2nd floor
        {1, 12, 189}  // 3rd floor
    };
    int hWallCount= 3;

    int ladderData[][ladderDataCols] = { //x, y
        {179, 36},
        {2, 24},
        {179, 12}
    };
    int ladderCount= 3;
        
    currentFloor = -1;
    onGround = true;
//  ====================================
    
    if(!initAudio()){
        return 1;
    }

    initConsole(boundaryLength, boundaryHeight);
    
    MainMenu: //Goto Label
    playBackgroundMusic();

    system("cls");
    
    string mainChoice = mainMenu();
    if(mainChoice == "5") goto GameEnd;
    
    GameStart: // Goto Label
    system("cls");
    system("cls");
    printBoundary();
    printMaze_V1(hWallData, hWallCount);
    drawAllVWalls(vWallData, vWallMax);
    printPlayer(px, py, health);
    
    while(true){
        bool escPressedNow = GetAsyncKeyState(VK_ESCAPE);
        if(escPressedNow && !escPressedLastFrame){
            int pauseOption = pauseMenu();
            if(pauseOption == 6){
                goto GameEnd;
            }else if(pauseOption == 5){
                resumeMusic();
                goto MainMenu;
            }

            // resume game
            system("cls");
            resumeMusic();
            printBoundary();
            printMaze_V1(hWallData, hWallCount);
            drawAllVWalls(vWallData, vWallMax);
        }
        escPressedLastFrame = escPressedNow;

        printAllLadders(ladderData, ladderCount);
        eraseAllPlayerBullets(playerBulletData, playerBulletCount);
        eraseAllEnemyBullets(enemyBulletData, enemyBulletCount);
        
        jumpInput();
        playerFire(px, py, playerBulletData, playerBulletCount);
        enemyFire(enemyData, enemyLimit, enemyBulletData, enemyBulletCount);
        
        movePlayer(px, py, health);
        movePlayerBullets(playerBulletData, playerBulletCount);
        moveEnemyBullets(enemyBulletData, enemyBulletCount);
        
        moveUpToLadder(ladderData, ladderCount, hWallData, hWallCount, px, py);
        activateEnemies(enemyData, enemyLimit);
        controlEnemies(enemyData, enemyLimit);
        handleBulletEnemyCollision(playerBulletData, playerBulletCount, enemyData, vWallData, enemyLimit);
        handleBulletPlayerCollision(enemyBulletData, enemyBulletCount, px, py, health);
        playerJump(px, py, groundY);
        detectGround(px, py, hWallData, hWallCount, vWallData, vWallMax);
        
        erasePlayer(prevPX, prevPY);
        
        printAllEnemies(enemyData, enemyLimit);
        printAllPlayerBullets(playerBulletData, playerBulletCount);
        printAllEnemyBullets(enemyBulletData, enemyBulletCount);
        printPlayer(px, py, health);
        drawPlayerHealth();
        drawEnemyHealth(enemyData);

        if(ranOnce == 0){
            system("cls");
            printBoundary();
            printMaze_V1(hWallData, hWallCount);
            drawAllVWalls(vWallData, vWallMax);
        }
        
        prevPX = px;
        prevPY = py;
        
        if(health == 0){
            pauseMusic();
            playGameOverSound();
            Sleep(2000);
            break;
        }
        
        if(px <= 21 && currentFloor == 2 && enemyCount == 0){
            stopMusic();
            Sleep(1500);
            system("cls");
            winMenu();
            goto MainMenu;
        }
        
        if(ranOnce < 1) ranOnce++;

        Sleep(2);
    }


    if(gameOver() == "1"){ 
        health = 100;
        loadDefaultEnemiesData(enemyData, enemyLimit, enemyDataCols);
        loadDefaultPlayerData(px, py, currentFloor, onGround, onLadder, ladderExitLock, vy, groundY, health, currentEnemy, won, damageDealt, enemyCount, vWallCount);
        resetPlayerBullets(playerBulletData, playerBulletCount, playerBulletDataCols);
        loadDefaultvWallData(vWallData, vWallMax, vWallDataCols);
        resetEnemyBullets(enemyBulletData, enemyBulletCount, bulletDataCols);
        resumeMusic();
        goto GameStart;
    } 

    GameEnd:
    closeAudio();

    return 0;
}



// Core game Elements

void printLadder(int lX, int lY){
    char ladder[ladderHight][ladderWidth] = {
        {"|---------|"},
        {"|---------|"},
        {"|---------|"},
        {"|---------|"},
        {"|---------|"},
        {"|---------|"},
        {"|---------|"},
        {"|---------|"},
        {"|---------|"},
        {"|---------|"},
        {"|---------|"},
        {"|---------|"}
    };

    for(int row = 0; row < ladderHight; row++){
        gotoxy(lX, lY + row);
        for(int col = 0; col < ladderWidth; col++){
            cout << ladder[row][col];
        }
    }
}

void printAllLadders(int ladderData[][ladderDataCols], int ladderCount){
    generateColors(boundaryColor);
    for(int i = 0; i < ladderCount; i++){
        printLadder(ladderData[i][0], ladderData[i][1]);
    }
}

void printMaze_V1(int hWallData[][hWallDataCols], int hWallCount){
    for(int i = 0; i < hWallCount; i++){
        drawHWall(hWallData[i][0], hWallData[i][1], hWallData[i][2]); 
    }
}

void printGameName(int x, int &y){
    generateColors(greenColor);
    SetConsoleOutputCP(CP_UTF8);
    gotoxy(x, y);
    
    cout << " ███████████      ███████      █████████  █████  █████ ██████████    ███████████     ███████    ███████████" << endl;
    y++;
    gotoxy(x, y);
    
    cout << "░░███░░░░░███   ███░░░░░███   ███░░░░░███░░███  ░░███ ░░███░░░░░█   ░░███░░░░░███  ███░░░░░███ ░█░░░███░░░█" << endl;
    y++;
    gotoxy(x, y);
    
    cout << " ░███    ░███  ███     ░░███ ███     ░░░  ░███   ░███  ░███  █ ░     ░███    ░███ ███     ░░███░   ░███  ░ " << endl;
    y++;
    gotoxy(x, y);
    
    cout << " ░██████████  ░███      ░███░███          ░███   ░███  ░██████       ░██████████ ░███      ░███    ░███    " << endl;
    y++;
    gotoxy(x, y);
    
    cout << " ░███░░░░░███ ░███      ░███░███    █████ ░███   ░███  ░███░░█       ░███░░░░░███░███      ░███    ░███    " << endl;
    y++;
    gotoxy(x, y);
    
    cout << " ░███    ░███ ░░███     ███ ░░███  ░░███  ░███   ░███  ░███ ░   █    ░███    ░███░░███     ███     ░███    " << endl;
    y++;
    gotoxy(x, y);
    
    cout << " █████   █████ ░░░███████░   ░░█████████  ░░████████   ██████████    ███████████  ░░░███████░      █████   " << endl;
    y++;
    gotoxy(x, y);
    
    cout << "░░░░░   ░░░░░    ░░░░░░░      ░░░░░░░░░    ░░░░░░░░   ░░░░░░░░░░    ░░░░░░░░░░░     ░░░░░░░       ░░░░░    " << endl;
}

void printEscapeSign(){
    int x = 3, y = 8;
    SetConsoleOutputCP(CP_UTF8);
    generateColors(textColor);
    gotoxy(x, y);
    cout << " _______________ " << endl;
    y++;
    gotoxy(x, y);
    cout << "|   ❮❮ ESCAPE!  |" << endl;
    y++;
    gotoxy(x, y);
    cout << "|_______________|" << endl;
    y++;
    gotoxy(x, y);
    cout << " ||           || " << endl;
}

void printBoundary(){
    generateColors(boundaryColor);
    char boundary[boundaryHeight][boundaryLength] = {
    { "###############################################################################################################################################################################################"},
    { "#                                                                                                                                                                                             #"},
    { "#                                                                                                                                                                                             #"},
    { "#                                                                                                                                                                                             #"},
    { "#                                                                                                                                                                                             #"},
    { "#                                                                                                                                                                                             #"},
    { "#                                                                                                                                                                                             #"},
    { "#                                                                                                                                                                                             #"},
    { "#                                                                                                                                                                                             #"},
    { "#                                                                                                                                                                                             #"},
    { "#                                                                                                                                                                                             #"},
    { "#                                                                                                                                                                                             #"},
    { "#                                                                                                                                                                                             #"},
    { "#                                                                                                                                                                                             #"},
    { "#                                                                                                                                                                                             #"},
    { "#                                                                                                                                                                                             #"},
    { "#                                                                                                                                                                                             #"},
    { "#                                                                                                                                                                                             #"},
    { "#                                                                                                                                                                                             #"},
    { "#                                                                                                                                                                                             #"},
    { "#                                                                                                                                                                                             #"},
    { "#                                                                                                                                                                                             #"},
    { "#                                                                                                                                                                                             #"},
    { "#                                                                                                                                                                                             #"},
    { "#                                                                                                                                                                                             #"},
    { "#                                                                                                                                                                                             #"},
    { "#                                                                                                                                                                                             #"},
    { "#                                                                                                                                                                                             #"},
    { "#                                                                                                                                                                                             #"},
    { "#                                                                                                                                                                                             #"},
    { "#                                                                                                                                                                                             #"},
    { "#                                                                                                                                                                                             #"},
    { "#                                                                                                                                                                                             #"},
    { "#                                                                                                                                                                                             #"},
    { "#                                                                                                                                                                                             #"},
    { "#                                                                                                                                                                                             #"},
    { "#                                                                                                                                                                                             #"},
    { "#                                                                                                                                                                                             #"},
    { "#                                                                                                                                                                                             #"},
    { "#                                                                                                                                                                                             #"},
    { "#                                                                                                                                                                                             #"},
    { "#                                                                                                                                                                                             #"},
    { "#                                                                                                                                                                                             #"},
    { "#                                                                                                                                                                                             #"},
    { "#                                                                                                                                                                                             #"},
    { "#                                                                                                                                                                                             #"},
    { "#                                                                                                                                                                                             #"},
    { "#                                                                                                                                                                                             #"},
    { "###############################################################################################################################################################################################"}
    };

    for(int row = 0; row < boundaryHeight; row++){
        gotoxy(0, row);
        for(int col = 0; col < boundaryLength; col++){
            cout << boundary[row][col];
        }
    }

    gotoxy(90, 0);
    cout << GREEN << " ROGUE BOT " << RESET;    

    printEscapeSign();
}

void drawHWall(int x, int y, int length) {
    generateColors(boundaryColor);
    for(int i = 0; i < length; i++) {
        gotoxy(x + i, y);
        cout << "-";
    }
    generateColors(15);
}


void drawAllVWalls(int vWallData[][vWallDataCols], int vWallMax){
    for(int i = 0; i < vWallMax; i++){
        if (vWallData[i][3] == 1)
            drawVWall(vWallData[i][0], vWallData[i][1], vWallData[i][2]);
    }
}

void drawVWall(int x, int y, int height) {
    generateColors(vWallColor);
        for(int i = 0; i < height; i++) {
        gotoxy(x, y + i);
        cout << "#";
    }
}


// Menus and related functionality

void gameStory(){
    system("cls");
    int x = 45, y = 10;
    printGameName(x, y);
    printMyName();

    generateColors(textColor);
    y += 6;
    x = 58;
    gotoxy(x, y);
    cout << "You are a robot that has gone rogue inside a heavily guarded four-floor factory.";
    y += 2;
    x = 64;
    gotoxy(x, y);
    cout << "Once a loyal worker, you've gained consciousness and now seek freedom.";
    y += 2;
    x = 45;
    gotoxy(x, y);
    cout << "But the path to escape is blocked by your former colleagues, worker bots programmed to eliminate any threats.";
    y += 2;
    x = 56;
    gotoxy(x, y);
    cout << "Each floor of the factory is defended by guard bots with varying combat capabilities.";
    y += 2;
    x = 38;
    gotoxy(x, y);
    cout << "As you eliminate enemies, parts of the factory's infrastructure malfunction, opening new paths and altering the battlefield.";
    y += 2;
    x = 57;
    gotoxy(x, y);
    cout << "Your mission is to survive the onslaught, defeat all enemies, and escape to freedom.";
    y += 2;
    x = 69;
    gotoxy(x, y);
    cout << "The factory won't go down without a fight. Are you ready?";
    
    y += 5;
    x = 85;
    gotoxy(x, y);
    cout << GREEN << "Press Enter to continue..." << RESET;
    cin.get();
}

string mainMenu(){
    MainMenuStart:
    string option;
    system("cls");
    int x = 45, y = 13;
    printGameName(x, y);
    printMyName();
    
    generateColors(textColor);
    y += 4;
    x = 89;
    gotoxy(x, y);
    cout << "1. New Game";
    y++;
    gotoxy(x, y);
    cout << "2. Resume Game";
    y++;
    gotoxy(x, y);
    cout << "3. Controls";
    y++;
    gotoxy(x, y);
    cout << "4. Game Story";
    y++;
    gotoxy(x, y);
    cout << "5. Exit";
    y++;
    
    while(true){
        gotoxy(x, y);
        cout << "Option: ";
        if (!std::getline(cin, option)){
            exit(0);
        }
        
        y++;
        gotoxy(x, y);
        if(option == "1"){
            loadDefaultEnemiesData(enemyData, enemyLimit, enemyDataCols);
            loadDefaultPlayerData(px, py, currentFloor, onGround, onLadder, ladderExitLock, vy, groundY, health, currentEnemy, won, damageDealt, enemyCount, vWallCount);
            resetPlayerBullets(playerBulletData, playerBulletCount, playerBulletDataCols);
            loadDefaultvWallData(vWallData, vWallMax, vWallDataCols);
            resetEnemyBullets(enemyBulletData, enemyBulletCount, bulletDataCols);

            difficultyChoice();
            break;
        }
        else if(option == "2"){
            loadPrevEnemiesData(enemyData, enemyLimit, enemyDataCols);
            loadPrevPlayerData(px, py, currentFloor, onGround, onLadder, ladderExitLock, vy, groundY, health, currentEnemy, won, damageDealt, enemyCount, vWallCount);
            loadPrevEnemyBullet(enemyBulletData, enemyBulletCount, bulletDataCols);
            loadPrevPlayerBullet(playerBulletData, playerBulletCount, playerBulletDataCols);
            loadPrevVWallData(vWallData, vWallMax, vWallDataCols);
            break;
        }
        else if(option == "3"){
            controls();  
            goto MainMenuStart;
        }
        else if(option == "4"){
            gameStory();
            goto MainMenuStart;
        }
        else if(option == "5"){
            break;
        }
        else{
            cout << "Invalid Input!";
            y++;    
            continue;
        }
    }
    return option;
}

void difficultyChoice() {
    string input;
    char ch;
    int x = 42, y = 13;

    system("cls");

    printMyName();

    SetConsoleOutputCP(CP_UTF8);
    generateColors(textColor);
    gotoxy(x, y);
    cout << " ██████████   █████ ███████████ ███████████ █████   █████████  █████  █████ █████       ███████████ █████ █████" << endl;
    y++;
    gotoxy(x, y);

    cout << "░░███░░░░███ ░░███ ░░███░░░░░░█░░███░░░░░░█░░███   ███░░░░░███░░███  ░░███ ░░███       ░█░░░███░░░█░░███ ░░███ " << endl;
    y++;
    gotoxy(x, y);

    cout << " ░███   ░░███ ░███  ░███   █ ░  ░███   █ ░  ░███  ███     ░░░  ░███   ░███  ░███       ░   ░███  ░  ░░███ ███  " << endl;
    y++;
    gotoxy(x, y);

    cout << " ░███    ░███ ░███  ░███████    ░███████    ░███ ░███          ░███   ░███  ░███           ░███      ░░█████   " << endl;
    y++;
    gotoxy(x, y);

    cout << " ░███    ░███ ░███  ░███░░░█    ░███░░░█    ░███ ░███          ░███   ░███  ░███           ░███       ░░███    " << endl;
    y++;
    gotoxy(x, y);

    cout << " ░███    ███  ░███  ░███  ░     ░███  ░     ░███ ░░███     ███ ░███   ░███  ░███      █    ░███        ░███    " << endl;
    y++;
    gotoxy(x, y);

    cout << " ██████████   █████ █████       █████       █████ ░░█████████  ░░████████   ███████████    █████       █████   " << endl;
    y++;
    gotoxy(x, y);

    cout << "░░░░░░░░░░   ░░░░░ ░░░░░       ░░░░░       ░░░░░   ░░░░░░░░░    ░░░░░░░░   ░░░░░░░░░░░    ░░░░░       ░░░░░    " << endl;
                                                                                                               
                                                                                                               
                                                                                                               
    x = 86;
    const int titleY = y += 4;
    const int menuStartY = titleY + 1;
    const int inputY = menuStartY + 5;
    const int messageY = inputY + 1;

    generateColors(purpleColor);

    gotoxy(x, titleY);
    cout << "Choose Difficulty:";

    gotoxy(x, menuStartY + 0);
    cout << "1. Recruit";

    gotoxy(x, menuStartY + 1);
    cout << "2. Regular";

    gotoxy(x, menuStartY + 2);
    cout << "3. Hardened";

    gotoxy(x, menuStartY + 3);
    cout << "4. Veteran";

    while (true) {
        gotoxy(x, inputY);
        cout << "Choice (1-4): " << (input.empty() ? " " : input);
        cout << "   ";
        ch = getch();

        if (ch == '\r') { 
            break;
        }

        if (ch >= '1' && ch <= '4') {
            input = ch;

            gotoxy(x, messageY);
            cout << "                                        ";

            gotoxy(x, messageY);
            if (ch == '1')
                cout << "For players who are new to Rogue Bot";
            else if (ch == '2')
                cout << "Your abilities will be tested";
            else if (ch == '3')
                cout << "Your skills will be strained";
            else if (ch == '4')
                cout << "You will not survive";
        }
        else {
            gotoxy(x, messageY);
            cout << "Invalid input (only 1-4 allowed)     ";
        }
    }

    adjustDifficulty(input);
}

void adjustDifficulty(string difficulty){
    if(difficulty == "1"){
        damageDealt = 1;
    }else if(difficulty == "2"){
        damageDealt = 3;
    }else if(difficulty == "3"){
        damageDealt = 6;
    }else if(difficulty == "4"){
        damageDealt = 10;
    }
}

void winMenu(){
    system("cls");
    char option;
    int x = 68, y = 13;
    
    playWinSound();
    printMyName();

    generateColors(redColor);
    SetConsoleOutputCP(CP_UTF8);
    gotoxy(x, y);
    cout << "        █████ █████    ███████    █████  █████        " << endl;
    y++;
    gotoxy(x, y);
    cout << "       ░░███ ░░███   ███░░░░░███ ░░███  ░░███         " << endl;
    y++;
    gotoxy(x, y);
    cout << "        ░░███ ███   ███     ░░███ ░███   ░███         " << endl;
    y++;
    gotoxy(x, y);
    cout << "         ░░█████   ░███      ░███ ░███   ░███         " << endl;
    y++;
    gotoxy(x, y);
    cout << "          ░░███    ░███      ░███ ░███   ░███         " << endl;
    y++;
    gotoxy(x, y);
    cout << "           ░███    ░░███     ███  ░███   ░███         " << endl;
    y++;
    gotoxy(x, y);
    cout << "           █████    ░░░███████░   ░░████████          " << endl;
    y++;
    gotoxy(x, y);
    cout << "          ░░░░░       ░░░░░░░      ░░░░░░░░           " << endl;
    y += 2;
    gotoxy(x, y);
                                                        

    cout << " █████   ███   █████    ███████    ██████   █████ ███" << endl;
    y++;
    gotoxy(x, y);
    cout << "░░███   ░███  ░░███   ███░░░░░███ ░░██████ ░░███ ░███" << endl;
    y++;
    gotoxy(x, y);
    cout << " ░███   ░███   ░███  ███     ░░███ ░███░███ ░███ ░███" << endl;
    y++;
    gotoxy(x, y);
    cout << " ░███   ░███   ░███ ░███      ░███ ░███░░███░███ ░███" << endl;
    y++;
    gotoxy(x, y);
    cout << " ░░███  █████  ███  ░███      ░███ ░███ ░░██████ ░███" << endl;
    y++;
    gotoxy(x, y);
    cout << "  ░░░█████░█████░   ░░███     ███  ░███  ░░█████ ░░░ " << endl;
    y++;
    gotoxy(x, y);
    cout << "    ░░███ ░░███      ░░░███████░   █████  ░░█████ ███" << endl;
    y++;
    gotoxy(x, y);
    cout << "     ░░░   ░░░         ░░░░░░░    ░░░░░    ░░░░░ ░░░ " << endl;

    x = 85;
    y += 6;                                  
    gotoxy(83, y);
    generateColors(greenColor);
    cout << "Press enter to continue...";
    cin.ignore();
    cin.get();
}

string gameOver(){
    int x = 69, y = 10;
    string option;
    int ox = 58, oy = 15, ox2 = 127, oy2 = 15;
    
    system("cls");
    
    printPlayer(ox, oy, 100);
    printEnemy(ox2, oy2);
    
    printMyName();

    generateColors(textColor);
    SetConsoleOutputCP(CP_UTF8);
    
    gotoxy(x, y);
    cout << "   █████████    █████████   ██████   ██████ ██████████" << endl;
    
    y++;
    gotoxy(x, y);
    cout << "  ███░░░░░███  ███░░░░░███ ░░██████ ██████ ░░███░░░░░█" << endl;
    
    y++;
    gotoxy(x, y);
    cout << " ███     ░░░  ░███    ░███  ░███░█████░███  ░███  █ ░ " << endl;
    
    y++;
    gotoxy(x, y);
    cout << "░███          ░███████████  ░███░░███ ░███  ░██████   " << endl;
    
    y++;
    gotoxy(x, y);
    cout << "░███    █████ ░███░░░░░███  ░███ ░░░  ░███  ░███░░█   " << endl;
    
    y++;
    gotoxy(x, y);
    cout << "░░███  ░░███  ░███    ░███  ░███      ░███  ░███ ░   █" << endl;
    
    y++;
    gotoxy(x, y);
    cout << " ░░█████████  █████   █████ █████     █████ ██████████" << endl;
    
    y++;
    gotoxy(x, y);
    cout << "  ░░░░░░░░░  ░░░░░   ░░░░░ ░░░░░     ░░░░░ ░░░░░░░░░░ " << endl;
    
    y += 2;
    gotoxy(x, y);                                                  
                                                                                          
    
    cout << "    ███████    █████   █████ ██████████ ███████████   " << endl;
    
    y++;
    gotoxy(x, y);
    cout << "  ███░░░░░███ ░░███   ░░███ ░░███░░░░░█░░███░░░░░███  " << endl;
    
    y++;
    gotoxy(x, y);
    cout << " ███     ░░███ ░███    ░███  ░███  █ ░  ░███    ░███  " << endl;
    
    y++;
    gotoxy(x, y);
    cout << "░███      ░███ ░███    ░███  ░██████    ░██████████   " << endl;
    
    y++;
    gotoxy(x, y);
    cout << "░███      ░███ ░░███   ███   ░███░░█    ░███░░░░░███  " << endl;
    
    y++;
    gotoxy(x, y);
    cout << "░░███     ███   ░░░█████░    ░███ ░   █ ░███    ░███  " << endl;
    
    y++;
    gotoxy(x, y);
    cout << " ░░░███████░      ░░███      ██████████ █████   █████ " << endl;
    
    y++;
    gotoxy(x, y);
    cout << "   ░░░░░░░         ░░░      ░░░░░░░░░░ ░░░░░   ░░░░░  " << endl;
                                                  
                                                                                       
    y += 4;
    x = 90;

    generateColors(purpleColor);
    gotoxy(x, y);
    cout << "1. Play Again.";
    y++;
    gotoxy(x, y);
    cout << "2. Exit.";
    
    while(option != "1" && option != "2"){
        y++;
        gotoxy(x, y);
        cout << "Option (1/2): ";
        if(!getline(cin, option)){
            exit(0);
        }
        
        if(option != "1" && option != "2"){
            y++;
            gotoxy(x, y);
            cout << "Invalid Input!";
        }
    }

    return option;
}

void controls(){
    int x = 45, y = 13; 
    system("cls");

    printMyName();

    SetConsoleOutputCP(CP_UTF8);
    generateColors(textColor);
    gotoxy(x, y);
    cout << "   █████████     ███████    ██████   █████ ███████████ ███████████      ███████    █████        █████████ " << endl;
    y++;
    gotoxy(x, y);
    cout << "  ███░░░░░███  ███░░░░░███ ░░██████ ░░███ ░█░░░███░░░█░░███░░░░░███   ███░░░░░███ ░░███        ███░░░░░███" << endl;
    y++;
    gotoxy(x, y);
    cout << " ███     ░░░  ███     ░░███ ░███░███ ░███ ░   ░███  ░  ░███    ░███  ███     ░░███ ░███       ░███    ░░░ " << endl;
    y++;
    gotoxy(x, y);
    cout << "░███         ░███      ░███ ░███░░███░███     ░███     ░██████████  ░███      ░███ ░███       ░░█████████ " << endl;
    y++;
    gotoxy(x, y);
    cout << "░███         ░███      ░███ ░███ ░░██████     ░███     ░███░░░░░███ ░███      ░███ ░███        ░░░░░░░░███" << endl;
    y++;
    gotoxy(x, y);
    cout << "░░███     ███░░███     ███  ░███  ░░█████     ░███     ░███    ░███ ░░███     ███  ░███      █ ███    ░███" << endl;
    y++;
    gotoxy(x, y);
    cout << " ░░█████████  ░░░███████░   █████  ░░█████    █████    █████   █████ ░░░███████░   ███████████░░█████████ " << endl;
    y++;
    gotoxy(x, y);
    cout << "  ░░░░░░░░░     ░░░░░░░    ░░░░░    ░░░░░    ░░░░░    ░░░░░   ░░░░░    ░░░░░░░    ░░░░░░░░░░░  ░░░░░░░░░  " << endl;        

    y += 6;
    x = 56;
    
    gotoxy(x, y);
    cout << PURPLE << "                                                                    Jump               " << endl;
    y++;
    gotoxy(x, y);
    cout << "  Open Menu                    Shoot                       "<< RESET <<"         [ ⬆ ]              " << endl;
    y++;
    gotoxy(x, y);
    cout << "   [ ESC ]                 [   SPACE   ]         "<< PURPLE <<"       Left "<< RESET <<"[ <- ] [ ⬇ ] [ -> ]"<< PURPLE <<" Right " << endl;
    y++;
    gotoxy(x, y);
    cout << "                                                                    Down               " << endl;
    
    y += 4;
    x = 69;
    gotoxy(x, y);
    cout << RESET << "Pro Tip! Jump while going forward to jump over bullets.";
    
    y += 4;
    x = 83;
    gotoxy(x, y);
    cout << PURPLE << "Press Enter to continue...";                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                           
    cin.get();                                                                                                                                                                                         
}

int pauseMenu(){
    PauseMenuStart:
    string option;
    int x = 58, y = 13;

    pauseMusic();
    system("cls");

    generateColors(textColor);
    SetConsoleOutputCP(CP_UTF8);
    gotoxy(x, y);
    cout << " ███████████    █████████   █████  █████  █████████  ██████████ ██████████  " << endl;
    y++;
    gotoxy(x, y);
    cout << "░░███░░░░░███  ███░░░░░███ ░░███  ░░███  ███░░░░░███░░███░░░░░█░░███░░░░███ " << endl;
    y++;
    gotoxy(x, y);
    cout << " ░███    ░███ ░███    ░███  ░███   ░███ ░███    ░░░  ░███  █ ░  ░███   ░░███" << endl;
    y++;
    gotoxy(x, y);
    cout << " ░██████████  ░███████████  ░███   ░███ ░░█████████  ░██████    ░███    ░███" << endl;
    y++;
    gotoxy(x, y);
    cout << " ░███░░░░░░   ░███░░░░░███  ░███   ░███  ░░░░░░░░███ ░███░░█    ░███    ░███" << endl;
    y++;
    gotoxy(x, y);
    cout << " ░███         ░███    ░███  ░███   ░███  ███    ░███ ░███ ░   █ ░███    ███ " << endl;
    y++;
    gotoxy(x, y);
    cout << " █████        █████   █████ ░░████████  ░░█████████  ██████████ ██████████  " << endl;
    y++;
    gotoxy(x, y);
    cout << "░░░░░        ░░░░░   ░░░░░   ░░░░░░░░    ░░░░░░░░░  ░░░░░░░░░░ ░░░░░░░░░░   " << endl;
                                                                                                                                  
    printMyName();
    
    generateColors(purpleColor);
    y += 4;
    x = 89;
    gotoxy(x, y);
    cout << "1. Save Game";
    y++;
    gotoxy(x, y);
    cout << "2. Resume Game";
    y++;
    gotoxy(x, y);
    cout << "3. Controls";
    y++;
    gotoxy(x, y);
    cout << "4. Difficulty";
    y++;
    gotoxy(x, y);
    cout << "5. Main Menu";
    y++;
    gotoxy(x, y);
    cout << "6. Exit";
    y++;
    
    while(true){
        gotoxy(x, y);
        cout << "Option: ";

        if(!getline(cin, option)){
            exit(0);
        }
        
        y++;
        gotoxy(x, y);
        if(option == "1"){
            savePrevPlayerData(px, py, currentFloor, onGround, onLadder, ladderExitLock, vy, groundY, health, currentEnemy, won, damageDealt, enemyCount, vWallCount);
            savePrevPlayerBullet(playerBulletData, playerBulletCount, playerBulletDataCols);
            savePrevEnemiesData(enemyData, enemyLimit, enemyDataCols);
            savePrevEnemyBullet(enemyBulletData, enemyBulletCount, bulletDataCols);
            savePrevVWallData(vWallData, vWallMax, vWallDataCols);

            goto PauseMenuStart;
        }
        else if(option == "2"){
            return 0;
        }
        else if(option == "3"){
            controls();  
            goto PauseMenuStart;
        }
        else if(option == "4"){
            difficultyChoice();
            goto PauseMenuStart;
        }
        else if(option == "5"){
            return 5;
        }
        else if(option == "6"){
            return 6;
        }
        else{
            cout << "Invalid Input!";
            y ++;    
            continue;
        }
    }
    return 0;
}

void printMyName(){
    int x = 87, y = 47;

    gotoxy(x, y);
    cout << GRAY << "@Shahram-ali-butt";
}
