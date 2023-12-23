#include <stdio.h>

#include "myheader.h"

int overlap_y(int ay1, int by1, int ay2, int by2);

void initPlayers(player_score *players, int nPlayer)
{
    int i = 0;
    for(i = 0; i < nPlayer; ++i)
    {
        players[i].score = 0;
    }
}

void getScore(Match* matchPtr, int player)
{
    Enemy enemy = matchPtr->enemy;
    Aircraft aircraft = matchPtr->aircraft;
    player_score *playerPtr = matchPtr->players;

    if (player == PLAYER_R &&
        overlap_y(aircraft.y, aircraft.y + AIRCRAFT_SIZE, enemy.y, enemy.y + ENEMY_SIZE))
    {
        playerPtr[PLAYER_R].score = playerPtr[PLAYER_R].score + 1;
        printf("enemy y=%d %d\n", enemy.y, enemy.y + ENEMY_SIZE);
        printf("aircraft =%d %d\n", aircraft.y, aircraft.y + AIRCRAFT_SIZE);
        printf("\n");
    }
    else if (player == PLAYER_L &&
             overlap_y(aircraft.y, aircraft.y + AIRCRAFT_SIZE, enemy.y, enemy.y + ENEMY_SIZE))
    {
        playerPtr[PLAYER_L].score = playerPtr[PLAYER_L].score + 1;
        printf("enemy y=%d %d\n", enemy.y, enemy.y + ENEMY_SIZE);
        printf("aircraft R =%d %d\n", aircraft.y, aircraft.y + AIRCRAFT_SIZE);
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


