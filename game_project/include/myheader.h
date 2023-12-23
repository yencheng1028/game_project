#ifndef _MYHEADER_H_
#define _MYHEADER_H_

#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>

//enemy direction
#define DOWN_RIGHT 0
#define UP_RIGHT 1
#define DOWN_LEFT 2
#define UP_LEFT 3

#define AIRCRAFT_MOVE 3
#define LEFT_BORDER 
#define RIGHT_BORDER 
#define AIRCRAFT_SIZE 100

#define SCREEN_W 700
#define SCREEN_H 860
#define ENEMY_SIZE 32

#define PLAYER_R 0
#define PLAYER_L 1
#define N_PLAYER 2 /* amount of player */

typedef struct Enemy
{
    int x;
    int y;
    int dir;
    int live;

    ALLEGRO_BITMAP *img;
    ALLEGRO_SAMPLE *boing;
} Enemy;

typedef struct Aircraft
{
    ALLEGRO_BITMAP *img; /* pointer to the Aircraft's image bitmap */
} Aircraft;

typedef struct game_background
{
    ALLEGRO_DISPLAY* display;
    ALLEGRO_BITMAP* background;
    ALLEGRO_EVENT_QUEUE* event_queue;
    
} game_background;

typedef struct pistol
{
    float x;
    float y;

} pitsol;

typedef struct atomic
{
    float x;
    float y;

} atomic;

typedef struct missile
{
    float x;
    float y;

} missile;

typedef struct health
{
    float x;
    float y;

} health;
 

typedef struct menu
{
    float x;
    float y;

} menu;

typedef struct player_score
{
    int score;

} player_score;

typedef struct Match
{
    Enemy enemy;
    Aircraft aircraft;

    player_score players[N_PLAYER]; 
} Match;

int initialize(game_background* game);
void initEnemy(Enemy *EnemyPtr, ALLEGRO_BITMAP *img, ALLEGRO_SAMPLE *boing);
void initAircraft(Aircraft *AircraftPtr, ALLEGRO_BITMAP *img);
void initPlayers(player_score *players, int nPlayer);

void moveEnemy(Match *matchPtr);
void moveAircraft(Aircraft *AircraftPtr, ALLEGRO_KEYBOARD_STATE *KBstatePtr);
void getScore(Match *matchPtr, int player);
void reverseHorizontalDirection(Match *matchPtr); // reverse the horizontal direction of the enemy

void cleanup(game_background* game);
void draw(game_background* game);
void cleanup(game_background* game);
void Gamebackground_call();

#endif // _MYHEADER_H_