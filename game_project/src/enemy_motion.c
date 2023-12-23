#include "myheader.h"

void initEnemy(Enemy *enemyPtr, ALLEGRO_BITMAP *img, ALLEGRO_SAMPLE *boing)
{
    enemyPtr->x = SCREEN_W / 2; /* give the enemy its initial x-coordinate */
    enemyPtr->y = SCREEN_H / 2; /* give the enemy its initial y-coordinate */
    enemyPtr->dir = rand() % 4; /* and then make a random initial direction */
    enemyPtr->img = img;
    enemyPtr->boing = boing;
}

/* moves the enemy */
void moveEnemy(Match *matchPtr)
{
    Enemy *enemyPtr = &matchPtr->enemy;

    switch (enemyPtr->dir)
    {
        case DOWN_RIGHT:
            ++enemyPtr->x; /* move the enemy to the right */
            ++enemyPtr->y; /* move the enemy down */
            break;
        case UP_RIGHT:
            ++enemyPtr->x; /* move the enemy to the right */
            --enemyPtr->y; /* move the enemy up */
            break;
        case DOWN_LEFT:
            --enemyPtr->x; /* move the enemy to the left */
            ++enemyPtr->y; /* move the enemy down */
            break;
        case UP_LEFT:
            --enemyPtr->x; /* move the enemy to the left */
            --enemyPtr->y; /* move the enemy up */
            break;
    } /* end switch */

    /* make sure the enemy doesn go off the screen */

    /* if the enemy is going off the top or bottom... */
    if (enemyPtr->y <= 0 || enemyPtr->y >= (SCREEN_H - ENEMY_SIZE))
    {
        reverseVerticalDirection(&matchPtr->enemy); /* make it go the other way */
        al_play_sample(enemyPtr->boing, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE,
                       NULL); /* play "boing" sound once */
    }

    /* if the enemy is going off the left or right... */
    if (enemyPtr->x <= 0 || enemyPtr->x >= (SCREEN_W - ENEMY_SIZE))
    {
        reverseHorizontalDirection(matchPtr); /* make it go the other way */
        al_play_sample(enemyPtr->boing, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE,
                       NULL); /* play "boing" sound once */
    }

} /* end function moveEnemy */

/* reverse the enemy up-down direction */
void reverseVerticalDirection(Enemy *enemyPtr)
{
    if (enemyPtr->dir == DOWN_RIGHT)
        enemyPtr->dir = UP_RIGHT;
    else if (enemyPtr->dir == DOWN_LEFT)
        enemyPtr->dir = UP_LEFT;
    else if (enemyPtr->dir == UP_RIGHT)
        enemyPtr->dir = DOWN_RIGHT;
    else if (enemyPtr->dir == UP_LEFT)
        enemyPtr->dir = DOWN_LEFT;

} /* end function reverseVerticalDirection */

/* reverses the horizontal direction */
void reverseHorizontalDirection(Match* matchPtr) 
{
    Enemy *enemyPtr = &matchPtr->enemy;
    //   int player;
    switch (enemyPtr->dir)
    {
        case DOWN_RIGHT:
            enemyPtr->dir = DOWN_LEFT;
            getScore(matchPtr, PLAYER_R);
            break;
        case UP_RIGHT:
            enemyPtr->dir = UP_LEFT;
            getScore(matchPtr, PLAYER_R);
            break;
        case DOWN_LEFT:
            enemyPtr->dir = DOWN_RIGHT;
            getScore(matchPtr, PLAYER_L);
            break;
        case UP_LEFT:
            enemyPtr->dir = UP_RIGHT;
            getScore(matchPtr, PLAYER_L);
            break;
    } /* end switch */

} /* end function reverseHorizontalDirection */
