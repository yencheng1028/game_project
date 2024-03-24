#include <stdio.h>

#include "pong_header.h"

int overlap_y(int ay1, int by1, int ay2, int by2);

void initPlayers(Player* players, int nPlayer)
{
    int i = 0;
    for(i = 0; i < nPlayer; ++i)
    {
        players[i].score = 0;
    }
}

void getScore(Match* matchPtr, int player)
{
    Ball ball = matchPtr->ball;
    Paddle paddle = matchPtr->paddle;
    Player* playerPtr = matchPtr->players;

    if(player == PLAYER_R &&
       overlap_y(paddle.yRight, paddle.yRight+PADDLE_SIZE, ball.y, ball.y+BALL_SIZE))
    {
        playerPtr[PLAYER_R].score = playerPtr[PLAYER_R].score + 1;
        printf("ball y=%d %d\n", ball.y, ball.y+BALL_SIZE);
        printf("paddle R =%d %d\n", paddle.yRight, paddle.yRight+PADDLE_SIZE);
        printf("paddle L =%d %d\n", paddle.yLeft, paddle.yLeft+PADDLE_SIZE);
        printf("\n");   
    }
    else if(player == PLAYER_L &&
            overlap_y(paddle.yLeft, paddle.yLeft+PADDLE_SIZE, ball.y, ball.y+BALL_SIZE))
    {
        playerPtr[PLAYER_L].score = playerPtr[PLAYER_L].score + 1;
        printf("ball y=%d %d\n", ball.y, ball.y+BALL_SIZE);
        printf("paddle R =%d %d\n", paddle.yRight, paddle.yRight+PADDLE_SIZE);
        printf("paddle L =%d %d\n", paddle.yLeft, paddle.yLeft+PADDLE_SIZE);
        printf("\n");
    }

}

int overlap_y(int ay1, int by1, int ay2, int by2)
{

    if((ay1 >= ay2 && ay1 <= by2) ||
       (by1 >= ay2 && by1 <= by2) ||
       (ay1 <= ay2 && by1 >= by2))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}


