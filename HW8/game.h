#ifndef GAME_H
#define GAME_H

#include "gba.h"


/**
 * Represents a paddle in the game
 */
typedef struct paddle {
        int row;
        int col;
        int velocity;
        const unsigned short *image;
} Paddle;

/**
 * Respresents the ball in the game
 */
typedef struct ball {
        int row;
        int col;
        int x_velocity;
        int y_velocity;
} Ball;

#endif
