#pragma once

bool initAudio();
void closeAudio();

void playShootSound();
void playEnemyShootSound();
void playJumpSound();
void playDeathSound();
void playWinSound();
void playGameOverSound();

void playBackgroundMusic();
void pauseMusic();
void resumeMusic();
void stopMusic();
