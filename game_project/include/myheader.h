#ifndef _MYHEADER_H_
#define _MYHEADER_H_

#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>

#define SCREEN_W 700
#define SCREEN_H 860


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



void cleanup(game_background* game);
int initialize(game_background* game);
void draw(game_background* game);
void cleanup(game_background* game);
void Gamebackground_call();
#endif // _MYHEADER_H_