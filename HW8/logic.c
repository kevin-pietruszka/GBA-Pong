#include "logic.h"
#include "gba.h"
#include "game.h"

#include "images/germany.h"
#include "images/whitepaddle.h"
#include "images/maroongold.h"
#include "images/redorange.h"
#include "images/royal.h"
#include "images/tech.h"


Paddle cpu;
Paddle player;
Ball ball; 
int player_score;
int cpu_score;

/**
 * Intializes initial game values
 * @param secret determines which paddles the player has
 */
void initGame(int secret) {

    player_score = 0;
    cpu_score = 0;

    cpu.col = CPU_STARTING_COL;
    cpu.row = CPU_STARTING_ROW;
    cpu.velocity = 0;
    cpu.image = StandardPaddle;

    player.col = PLAYER_STARTING_COL;
    player.row = PLAYER_STARTING_ROW;
    player.velocity = 0;

    if (secret == 0) {

        player.image = StandardPaddle;

    } else if (secret == 1) {

        player.image = RedOrangePaddle;

    } else if (secret == 2) {

        player.image = RedGoldPaddle;

    } else if (secret == 3) {
        
        player.image = RoyalPaddle;

    } else if (secret == 4) {

        player.image = GermanyPattern;

    } else {

        player.image = TechPaddle;

    }

    randint(-BALL_SPEED, BALL_SPEED);
    ball.col = BALL_STARTING_COL;
    ball.row = BALL_STARTING_ROW;
    ball.x_velocity = BALL_SPEED;
    ball.y_velocity = randint(-BALL_SPEED, BALL_SPEED);
}


static void updatePlayer(u32 keysPressed) {

    if (KEY_DOWN(BUTTON_UP, keysPressed)) {

        player.velocity = -4;

    } else if (KEY_DOWN(BUTTON_DOWN, keysPressed)) {

        player.velocity = 4;

    } else {

        player.velocity = 0;

    }

    int newPlayerPos = player.row + player.velocity;

    if (!(newPlayerPos < 0 || newPlayerPos + 28 > HEIGHT)) {

        player.row = newPlayerPos;

    }

}

static void updateCPU(void) {

    int offset = 14;

    if (cpu.row + offset < ball.row) {

        cpu.velocity = 1;

    } else if (cpu.row + offset > ball.row) {
        
        cpu.velocity = -1;

    } else {

        cpu.velocity = 0;

    }

    int newCpuPos = cpu.row + cpu.velocity;

    if (!(newCpuPos < 0 || newCpuPos + 28 > HEIGHT)) {

        cpu.row = newCpuPos;

    }

}

static int score(int player) {

    if (player) {

        player_score++;

        if (player_score == 5) {
            return 1;
        }

    } else {

        cpu_score++;

        if (cpu_score == 5) {
            return 1;
        }
    }
    return 0;

}


static void resetBall(void) {

    ball.col = BALL_STARTING_COL;
    ball.row = BALL_STARTING_ROW;
    ball.x_velocity = BALL_SPEED;
    ball.y_velocity = randint(-BALL_SPEED, BALL_SPEED);

}

/**
 * Updates the objects locations and does edge collision
 */
int processGame(u32 keysPressed) {

    updatePlayer(keysPressed);
    updateCPU();
    
    //Move ball and check for collisions

    int newBallX = ball.col + ball.x_velocity;
    int newBallY = ball.row + ball.y_velocity;

    if (newBallY < 0 || newBallY + BALL_SIZE > HEIGHT) {

        ball.y_velocity = -ball.y_velocity;

    } else if ((newBallY >= player.row && newBallY <= player.row + 28) && (newBallX == player.col)) { //collision with player 

        ball.x_velocity = -ball.x_velocity;
        ball.y_velocity = randint(-BALL_SPEED, BALL_SPEED);

    } else if ((newBallY >= cpu.row && newBallY <= cpu.row + 28) && (newBallX == cpu.col + BALL_SIZE)) { //collision with cpu

        ball.x_velocity = -ball.x_velocity;
        ball.y_velocity = randint(-BALL_SPEED, BALL_SPEED);

    } else if (newBallX < 0) {

        resetBall();
        if (score(1)) {
            return 1;
        }

    } else if(newBallX > WIDTH) {

        resetBall();
        if (score(0)) {
            return -1;
        }

    }  else {

        ball.col = newBallX;
        ball.row = newBallY;
    }

    return 0;
}

void undrawGameScreen(void) {

    if (player.image == TechPaddle) {

        drawRectDMA(player.row, player.col, 5, 28, BLACK);

    } else {

        drawRectDMA(player.row, player.col, 4, 28, BLACK);

    }
    drawRectDMA(cpu.row, cpu.col, 4, 28, BLACK);
    drawRectDMA(ball.row, ball.col, BALL_SIZE, BALL_SIZE, BLACK);

    drawChar(2, 110, (char)(48 + cpu_score), BLACK);
    drawChar(2, 117 , '-', BLACK);
    drawChar(2, 124, (char)(48 + player_score), BLACK);
}

void drawGameScreen(void) {

    if (player.image == TechPaddle) {

        drawImageDMA(player.row, player.col, 5, 28, player.image);

    } else {

        drawImageDMA(player.row, player.col, 4, 28, player.image);

    }
    drawImageDMA(cpu.row, cpu.col, 4, 28, cpu.image);
    drawRectDMA(ball.row, ball.col, BALL_SIZE, BALL_SIZE, WHITE);

    drawChar(2, 110, (char)(48 + cpu_score), WHITE);
    drawChar(2, 117, '-', WHITE);
    drawChar(2, 124, (char)(48 + player_score), WHITE);

}