#include "audio.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_mixer.h"
#include <iostream>

using namespace std;

// Music
Mix_Music* bgMusic = nullptr;

// Sound effects
Mix_Chunk* shootSound = nullptr;
Mix_Chunk* enemyShootSound = nullptr;
Mix_Chunk* jumpSound = nullptr;
Mix_Chunk* deathSound = nullptr;
Mix_Chunk* gameOverSound = nullptr;
Mix_Chunk* winSound = nullptr;

bool initAudio() {
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        cout << "SDL Audio Init Failed: " << SDL_GetError() << endl;
        return false;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        cout << "SDL_mixer Init Failed: " << Mix_GetError() << endl;
        return false;
    }

    // Load sounds
    shootSound = Mix_LoadWAV("assets/playerShoot.wav");
    enemyShootSound = Mix_LoadWAV("assets/enemyShoot.wav");
    jumpSound = Mix_LoadWAV("assets/jump.wav");
    deathSound = Mix_LoadWAV("assets/enemyDeath.wav");
    gameOverSound = Mix_LoadWAV("assets/gameover.wav");
    winSound = Mix_LoadWAV("assets/SOR2_win.wav");

    bgMusic = Mix_LoadMUS("assets/SOR2.wav");

    if (!bgMusic || !shootSound || !jumpSound || !deathSound || !winSound || !enemyShootSound || !gameOverSound) {
        cout << "Failed to load audio files: " << Mix_GetError() << endl;
        return false;
    }

    return true;
}

void closeAudio(){
    Mix_FreeChunk(shootSound);
    Mix_FreeChunk(jumpSound);
    Mix_FreeChunk(deathSound);
    Mix_FreeChunk(winSound);
    Mix_FreeChunk(enemyShootSound); 
    Mix_FreeChunk(gameOverSound); 
    Mix_FreeMusic(bgMusic);

    Mix_CloseAudio();
    SDL_QuitSubSystem(SDL_INIT_AUDIO);
}


void playShootSound() {
    Mix_PlayChannel(-1, shootSound, 0);
}

void playEnemyShootSound() {
    Mix_PlayChannel(-1, enemyShootSound, 0);
}

void playJumpSound() {
    Mix_PlayChannel(-1, jumpSound, 0);
}

void playDeathSound() {
    Mix_PlayChannel(-1, deathSound, 0);
}

void playWinSound() {
    Mix_PlayChannel(-1, winSound, 0);
}

void playGameOverSound() {
    Mix_PlayChannel(-1, gameOverSound, 0);
}



void playBackgroundMusic() {
    if (!Mix_PlayingMusic()) {
        Mix_PlayMusic(bgMusic, -1); // loop forever
    }
}

void pauseMusic() {
    if (Mix_PlayingMusic()) {
        Mix_PauseMusic();
    }
}

void resumeMusic() {
    if (Mix_PausedMusic()) {
        Mix_ResumeMusic();
    }
}

void stopMusic() {
    Mix_HaltMusic();
}
