#include "pong_header.h"

void initPaddle(Paddle* paddlePtr, ALLEGRO_BITMAP* img)
{
    /* give left paddle its initial y-coordinate */
    paddlePtr->yLeft = SCREEN_H / 2;
    /* give right paddle its initial y-coordinate */
    paddlePtr->yRight = SCREEN_H / 2;
    paddlePtr->img = img;
}

void movePaddle(Paddle* paddlePtr, ALLEGRO_KEYBOARD_STATE* KBstatePtr)
{
    if(al_key_down(KBstatePtr, ALLEGRO_KEY_A))
        paddlePtr->yLeft -= PADDLE_MOVE;
    if(al_key_down(KBstatePtr, ALLEGRO_KEY_Z))
        paddlePtr->yLeft += PADDLE_MOVE;
    if(al_key_down(KBstatePtr, ALLEGRO_KEY_UP))
        paddlePtr->yRight -= PADDLE_MOVE;
    if(al_key_down(KBstatePtr, ALLEGRO_KEY_DOWN))
        paddlePtr->yRight += PADDLE_MOVE;

    /* make sure the paddles don go off screen */
    if(paddlePtr->yLeft < PADDLE_MIN)
        paddlePtr->yLeft = PADDLE_MIN;
    if(paddlePtr->yLeft > PADDLE_MAX)
        paddlePtr->yLeft = PADDLE_MAX;
    if(paddlePtr->yRight < PADDLE_MIN)
        paddlePtr->yRight = PADDLE_MIN;
    if(paddlePtr->yRight > PADDLE_MAX)
        paddlePtr->yRight = PADDLE_MAX;
}
