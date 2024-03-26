#ifndef _MYHEADER_H_
#define _MYHEADER_H_

#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

// Constants for screen dimensions
#define SCREEN_W 700
#define SCREEN_H 860

// Maximum number of enemies and bullets
#define MAX_ENEMIES 100
#define MAX_BULLETS 70

// Time intervals for bullet updates
#define BULLET_UPDATE_TIMER 0.05
#define PLANE_BULLET_UPDATE_TIMER 0.005

// Other game-related constants
#define NEW_ENEMY_COUNT 2
#define BALL_SIZE 40
#define PLANE_MOVE 20
#define PLANE_MIN 0
#define PLANE_MAX 700
#define PLANE_SIZE 40
#define MAX_ENEMIES_LEVEL2 6
#define MAX_ENEMIES_LEVEL3 6
#define MAX_ENEMIES_LEVEL4 8
#define MAX_PLANE_BULLETS 1

// Player-related constants
#define PLAYER_1 0
#define N_PLAYER 1 

// Structure to hold player information
typedef struct player_data {
    char name[20];
    int score;
} player_data;

// Structure to represent enemy bullets
typedef struct enemy_bullet_data {
    float x;
    float y;
    float vy;
    ALLEGRO_BITMAP* bullet_pic;
    int width;
    int height;
} enemy_bullet;

// Structure to represent plane bullets
typedef struct plane_bullet_data {
    float x;
    float y;
    float vy;
    ALLEGRO_BITMAP* bullet;
    int width;
    int height;
} plane_bullet;

// Additional structure for a different type of plane bullet
typedef struct plane_bullet_data2 {
    float x;
    float y;
    float vy;
    ALLEGRO_BITMAP *bullet;
    int width;
    int height;
} plane_bullet2;

// Structure to represent the player's plane
typedef struct plane_data {
    float x;
    float y;
    ALLEGRO_BITMAP* plane_img;
    ALLEGRO_DISPLAY* plane_display;
    ALLEGRO_TIMER* plane_timer;
    ALLEGRO_TIMER* plane_bullet_timer;
    ALLEGRO_TIMER* plane_bullet_timer2;
    ALLEGRO_EVENT_QUEUE* event_plane_queue;
    ALLEGRO_EVENT_QUEUE* event_plane_bullet_queue;
    ALLEGRO_EVENT_QUEUE* event_plane_bullet_queue2;
    plane_bullet bullets[MAX_PLANE_BULLETS];
    plane_bullet2 bullets2[MAX_PLANE_BULLETS];
    int num_bullets;
    int num_bullets2;
    int width;
    int height;
    int health;
} plane_data;

// Structure to represent enemy entities
typedef struct enemy_data {
    float x;
    float y;
    float vx;
    float vy;
    ALLEGRO_DISPLAY* enemy_display;
    ALLEGRO_BITMAP* enemy_pic;
    ALLEGRO_EVENT_QUEUE* event_enemy_queue;
    ALLEGRO_TIMER* timer;
    ALLEGRO_TIMER* bullet_timer;
    ALLEGRO_SAMPLE* shoot_sound;
    int width;
    int height;
    enemy_bullet bullets[MAX_BULLETS];
    int num_bullets;
    int hit_count;
    int destroy_enemy;
} enemy_data;

// Structure to represent the overall game state
typedef struct game_data {
    ALLEGRO_DISPLAY* display;
    ALLEGRO_BITMAP* background;
    ALLEGRO_EVENT_QUEUE* event_queue;
    enemy_data enemies[MAX_ENEMIES];
    int num_enemies;
    ALLEGRO_SAMPLE* background_music;
    ALLEGRO_SAMPLE_INSTANCE* background_music_instance;
    ALLEGRO_TIMER* bullet_spawn_timer;
    ALLEGRO_FONT *Font;
    player_data players[N_PLAYER];
    ALLEGRO_BITMAP* pause_image;
    ALLEGRO_BITMAP* win_image;
    ALLEGRO_BITMAP* lose_image;
    ALLEGRO_FONT* level1_Font;
    ALLEGRO_FONT* level2_Font;
    ALLEGRO_FONT* level3_Font;
    ALLEGRO_FONT* level4_Font;
} game_data;

// Structure for the main menu
typedef struct menu {
    ALLEGRO_DISPLAY* display;
    ALLEGRO_EVENT_QUEUE* event_queue;
    ALLEGRO_BITMAP* startGameImage;
    ALLEGRO_BITMAP* exitGameImage;
    ALLEGRO_BITMAP* menuBackgroundImage;
    ALLEGRO_BITMAP* illustrateImage;
    ALLEGRO_BITMAP* nameImage;
    ALLEGRO_FONT* history_Font;
    float nameX;
    float nameY;
    float illustrateX;
    float illustrateY;
    float startX;
    float startY;
    float exitX;
    float exitY;
    bool isPressed;
    bool isXInButtonRange;
    bool isYInButtonRange;
    bool isXInButtonRange_exit;
    bool isYInButtonRange_exit;
    bool shouldExit;
} menu;

// Function declarations
void initPlayers(player_data *players, int nPlayer);
void Gamebackground_call(game_data* game, plane_data* plane,ALLEGRO_DISPLAY* display,int scorevalue);
void draw_enemies(game_data* game);
void draw_game(game_data* game, plane_data* plane);
void draw_background(game_data* game);
void draw_plane(game_data *game, plane_data *plane);
void drawlevel(game_data*game, int picture_number);
void cleanup(game_data *game);
void cleanup_enemies(game_data* game);
void cleanup_plane(plane_data*plane);
void update_enemy_positions(game_data* game, plane_data* plane,ALLEGRO_DISPLAY* display,int scorevalue);
void fire_bullet(enemy_data* enemy);
void fire_plane_bullet(plane_data* plane);
void fire_plane_bullet2(plane_data *plane);
int initialize_all(game_data* game,plane_data* plane, int num_enemies,ALLEGRO_DISPLAY* display);
int initialize_game(game_data* game, int num_enemies,ALLEGRO_DISPLAY* display);
int initialize_enemies(enemy_data* enemies, int num_enemies, ALLEGRO_DISPLAY* display, ALLEGRO_EVENT_QUEUE* event_queue);
void initialize_bullet(enemy_data* enemy, int index);
void initialize_plane_bullet(plane_data *plane, int index);
void initialize_plane_bullet2(plane_data *plane, int index);
int initialize_plane(plane_data* plane);
int initializeButton(menu* button,ALLEGRO_DISPLAY* display);
void drawMenu(menu* button,int scorevalue);
void cleanupMenu(menu* button);
void handleInput(ALLEGRO_EVENT *ev, menu *button, game_data *game);
void menu_call(int scorevalue);
void movePlane(plane_data* plane, const ALLEGRO_KEYBOARD_EVENT* kbEvent);
int check_collision(float x1, float y1, int w1, int h1, float x2, float y2, int w2, int h2);
void check_and_remove_bullet_collision(game_data* game, plane_data* plane,ALLEGRO_DISPLAY* display,int scorevalue);
int check_collision_with_existing(game_data* game, enemy_data* new_enemy);
void spawn_new_enemies(game_data* game);
void spawn_new_enemies2(game_data* game);
void spawn_new_enemies3(game_data* game);

void ScoreFileLoad (int* Score);
void ScoreFileSave (int Score);

#endif // _MYHEADER_H_
