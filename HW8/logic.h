#include "gba.h"

#ifndef LOGIC_H
#define LOGIC_H

#define CPU_STARTING_ROW 66
#define CPU_STARTING_COL 8

#define PLAYER_STARTING_ROW 64
#define PLAYER_STARTING_COL 228

#define BALL_SPEED 2
#define BALL_STARTING_ROW 78
#define BALL_STARTING_COL 118
#define BALL_SIZE 4

void initGame(int secret);
int processGame(u32 keysPressed); 
void undrawGameScreen(void);
void drawGameScreen(void);

#endif