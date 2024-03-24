#ifndef _PONGHEADER_H_
#define _PONGHEADER_H_

#include <allegro5/allegro.h>
#include <allegro5/allegro_audio.h>

#define DOWN_RIGHT 0
#define UP_RIGHT 1
#define DOWN_LEFT 2
#define UP_LEFT 3

#define PADDLE_MOVE 10
#define PADDLE_MIN 30
#define PADDLE_MAX 380
#define PADDLE_SIZE 100

#define SCREEN_W  640
#define SCREEN_H  480
#define BALL_SIZE 40

#define PLAYER_R 0
#define PLAYER_L 1
#define N_PLAYER 2  /* amount of player */

typedef struct Ball
{
    int x; 		/* the ball's x-coordinate */
    int y; 		/* the ball's y-coordinate */
    int dir; 	/* the ball's direction */

    ALLEGRO_BITMAP* img; 	/* pointer to the ball's image bitmap */
    ALLEGRO_SAMPLE* boing; 	/* pointer to sound file */
} Ball;

typedef struct Paddle
{
    int yLeft;			/* y-coordinate of left paddle */
    int yRight;			/* y-coordinate of right paddle */

    ALLEGRO_BITMAP* img; 	/* pointer to the bar's image bitmap */
} Paddle;

typedef struct Player    
{
    int score;
} Player;

typedef struct Match     /***/
{
    Ball ball;
    Paddle paddle;

    Player players[N_PLAYER];  /* score of the two player */ 
} Match;

/* function prototypes */
void allegroDriverInit();
void initBall(Ball* ballPtr, ALLEGRO_BITMAP* img, ALLEGRO_SAMPLE* boing);
void initPaddle(Paddle* paddlePtr, ALLEGRO_BITMAP* img);
void initPlayers(Player* players, int nPlayer);

void moveBall(Match* matchPtr);
void movePaddle(Paddle* paddlePtr, ALLEGRO_KEYBOARD_STATE* KBstatePtr);
void getScore(Match* matchPtr, int player);
void reverseVerticalDirection(Ball* ballPtr);
void reverseHorizontalDirection(Match* matchPtr);

#endif // _PONGHEADER_H_
