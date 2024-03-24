/*
   Creating the bouncing ball.
   Modified based on Dietel's examples Fig. 15.5/9.c  by Johnw, Xin-Ming Liu, Yu-Ren Zhang
   2015.12.07, 2019.11.11, 2019.11.18, 2019.11.25

   busy-waiting while loop
   with boing.wav sound and background music
   with right/left paddles
   with text
*/

#include <stdio.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#include "pong_header.h"

int main()
{
    int finish = 0;
    int counter = 0;
    Match match;
    Ball* ballPtr = &match.ball;
    Paddle* paddlePtr = &match.paddle;
    Player* players = match.players;

    ALLEGRO_BITMAP* bar = NULL;         /* pointer to the bar's image bitmap */
    ALLEGRO_BITMAP* ball = NULL;        /* pointer to the ball's image bitmap */
    ALLEGRO_DISPLAY* display = NULL;    /* pointer to display */
    ALLEGRO_SAMPLE* boing = NULL;       /* pointer to sound file */
    ALLEGRO_SAMPLE* background = NULL;  /* pointer to sound file */
    ALLEGRO_FONT* pongFont = NULL;      /* pointer to Font file */

    ALLEGRO_KEYBOARD_STATE KBstate;
    ALLEGRO_SAMPLE_ID backgroundId;

    allegroDriverInit();

    display = al_create_display(SCREEN_W, SCREEN_H);

    ball = al_load_bitmap("assets/ball.bmp"); /* load the ball bitmap */
    boing = al_load_sample("assets/boing.wav"); /* load the sound file */
    srand(time(NULL));                      /* seed the random function */
    initBall(ballPtr, ball, boing);         /* initial the ball */

    bar = al_load_bitmap("assets/bar.bmp"); /* load the bar bitmap */
    initPaddle(paddlePtr, bar);         /* initial the paddle */

    initPlayers(players, N_PLAYER);     /* initial the players */

    pongFont = al_load_ttf_font("assets/arial.ttf", 16, 0); /* load the FONT file */

    background = al_load_sample("assets/taipei.wav"); /* load the background sound file */
    al_play_sample(background, 1, 0, 1, ALLEGRO_PLAYMODE_LOOP, &backgroundId);

    while(finish == 0)
    {
        al_get_keyboard_state(&KBstate);
        if(al_key_down(&KBstate, ALLEGRO_KEY_ESCAPE))
        {
            finish = 1;
        }

        /* draw text onto the buffer */
        al_draw_textf(pongFont, al_map_rgb(255, 255, 255), 75, 0, -1,
                      "Left Player Score: %d", players[PLAYER_L].score);
        al_draw_textf(pongFont, al_map_rgb(255, 255, 255), 400, 0, -1,
                      "Right Player Score: %d", players[PLAYER_R].score);

        movePaddle(&match.paddle, &KBstate); /* move the paddles */
        al_draw_bitmap(paddlePtr->img, 0, paddlePtr->yLeft, 0);
        al_draw_bitmap(paddlePtr->img, 620, paddlePtr->yRight, 0);

        moveBall(&match); /* move the ball */
        al_draw_bitmap(ballPtr->img, ballPtr->x, ballPtr->y, 0); /* draw the bitmap */


        counter = counter + 1;
        printf("Hello, counter %d\n", counter);

        al_rest(0.01);


        /* display */
        al_flip_display(); /* Wait for the beginning of a vertical retrace. */
        al_clear_to_color(al_map_rgb(0, 0, 0));

        /* Clear the complete target bitmap, but confined by the clipping rectangle. */
    }

    al_stop_sample(&backgroundId);   /* stop bgm */
    al_destroy_sample(background);  /* destroy the background sound file */
    al_destroy_bitmap(ball);  /* destroy the ball bitmap */
    al_destroy_display(display);  /* destroy the display */
    al_destroy_bitmap(bar);   /* destroy the bar bitmap */
    al_destroy_sample(boing);   /* destroy the boing sound file */
    al_destroy_font(pongFont);   /* destroy the font */

    return 0;
} /* end function main */
