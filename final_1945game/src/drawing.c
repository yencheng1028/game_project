#include "myheader.h"

// Function to draw the game screen
void draw_game(game_data* game, plane_data* plane) {
    draw_background(game);
    draw_enemies(game);
    draw_plane(game, plane);
    al_draw_textf(game->Font, al_map_rgb(255, 255, 255), 75, 0, -1, "Player Score: %d", game->players[PLAYER_1].score);
    al_draw_textf(game->Font, al_map_rgb(255, 255, 255), 600, 0, -1, "Plane Health: %d", plane->health);
    al_flip_display();
}

// Function to draw the game background
void draw_background(game_data* game) {
    al_clear_to_color(al_map_rgb(0, 0, 0));
    int img_w = al_get_bitmap_width(game->background);
    int img_h = al_get_bitmap_height(game->background);

    al_draw_scaled_bitmap(
        game->background, 0, 0, img_w, img_h, 0, 0, SCREEN_W, SCREEN_H, 0
    );
}

// Function to draw enemies and their bullets
void draw_enemies(game_data* game) {
    for (int i = 0; i < game->num_enemies; ++i) {
        al_draw_scaled_bitmap(
            game->enemies[i].enemy_pic, 0, 0, al_get_bitmap_width(game->enemies[i].enemy_pic),
            al_get_bitmap_height(game->enemies[i].enemy_pic), game->enemies[i].x, game->enemies[i].y,
            game->enemies[i].width, game->enemies[i].height, 0
        );

        for (int j = 0; j < game->enemies[i].num_bullets; ++j) {
            al_draw_scaled_bitmap(
                game->enemies[i].bullets[j].bullet_pic,
                0, 0,
                al_get_bitmap_width(game->enemies[i].bullets[j].bullet_pic),
                al_get_bitmap_height(game->enemies[i].bullets[j].bullet_pic),
                game->enemies[i].bullets[j].x,
                game->enemies[i].bullets[j].y,
                game->enemies[i].bullets[j].width,
                game->enemies[i].bullets[j].height,
                0
            );
        }
    }
}

// Function to draw the player's plane and its bullets based on the score
void draw_plane(game_data* game, plane_data* plane) {
    al_draw_bitmap(plane->plane_img, plane->x, plane->y, 0);

    if (game->players[PLAYER_1].score < 560) {
        for (int j = 0; j < plane->num_bullets; ++j) {
            al_draw_scaled_bitmap(
                plane->bullets[j].bullet,
                0, 0,
                al_get_bitmap_width(plane->bullets[j].bullet),
                al_get_bitmap_height(plane->bullets[j].bullet),
                plane->bullets[j].x,
                plane->bullets[j].y,
                plane->bullets[j].width,
                plane->bullets[j].height,
                0
            );
        }
    }

    if (game->players[PLAYER_1].score >= 560) {
        for (int j = 0; j < plane->num_bullets2; ++j) {
            al_draw_scaled_bitmap(
                plane->bullets2[j].bullet,
                0, 0,
                al_get_bitmap_width(plane->bullets2[j].bullet),
                al_get_bitmap_height(plane->bullets2[j].bullet),
                plane->bullets2[j].x,
                plane->bullets2[j].y,
                plane->bullets2[j].width,
                plane->bullets2[j].height,
                0
            );
        }
    }
}

// Function to draw the main menu
void drawMenu(menu* button,int scorevalue) {
    al_clear_to_color(al_map_rgb(0, 0, 0));

    // Draw menu background
    int img_w = al_get_bitmap_width(button->menuBackgroundImage);
    int img_h = al_get_bitmap_height(button->menuBackgroundImage);
    al_draw_scaled_bitmap(
        button->menuBackgroundImage, 0, 0, img_w, img_h, 0, 0, SCREEN_W, SCREEN_H, 0
    );

    // Draw start game button
    int startWidth = al_get_bitmap_width(button->startGameImage);
    int startHeight = al_get_bitmap_height(button->startGameImage);
    float startX = (SCREEN_W - startWidth) / 2.0;
    float startY = (SCREEN_H - startHeight) / 2.0 - 50.0;
    al_draw_bitmap(button->startGameImage, startX, startY, 0);

    // Draw exit game button
    int exitWidth = al_get_bitmap_width(button->exitGameImage);
    int exitHeight = al_get_bitmap_height(button->exitGameImage);
    float exitX = (SCREEN_W - exitWidth) / 2.0;
    float exitY = (SCREEN_H - exitHeight) / 2.0 + 50.0;
    al_draw_bitmap(button->exitGameImage, exitX, exitY, 0);

    // Draw illustrate button
    int illustrateWidth = al_get_bitmap_width(button->illustrateImage);
    int illustrateHeight = al_get_bitmap_height(button->illustrateImage);
    float illustrateX = (SCREEN_W - illustrateWidth) / 2.0;
    float illustrateY = (SCREEN_H - illustrateHeight) / 2.0 + 250;
    al_draw_bitmap(button->illustrateImage, illustrateX, illustrateY, 0);

    // Draw name button
    int nameWidth = al_get_bitmap_width(button->nameImage);
    int nameHeight = al_get_bitmap_height(button->nameImage);
    float nameX = (SCREEN_W - nameWidth) / 2.0;
    float nameY = (SCREEN_H - nameHeight) / 2.0 - 250;
    al_draw_bitmap(button->nameImage, nameX, nameY, 0);


    char ScoreText[20];
    snprintf(ScoreText, sizeof(ScoreText), "%d", scorevalue);
    al_draw_text(button->history_Font, al_map_rgb(240, 240, 240), SCREEN_W / 2 - 300, SCREEN_H / 2 - 400 , ALLEGRO_ALIGN_LEFT, ScoreText);
    

    al_flip_display(); 
}

// Function to draw different levels or game outcomes
void drawlevel(game_data* game, int picture_number) {
    switch (picture_number) {
    case 1:
        al_draw_bitmap(game->win_image, 0, 0, 0);
        al_flip_display();
        al_rest(2.0);
        break;
    case 2:
        al_draw_bitmap(game->lose_image, 0, 0, 0);
        al_flip_display();
        al_rest(2.0);
        break;
    case 3:
        al_draw_textf(game->level1_Font, al_map_rgb(255, 255, 255), 350, 0, -1, "LEVEL 1");
        al_flip_display();
        break;
    case 4:
        al_draw_textf(game->level2_Font, al_map_rgb(255, 255, 255), 350, 0, -1, "LEVEL 2");
        al_flip_display();
        break;
    case 5:
        al_draw_textf(game->level2_Font, al_map_rgb(255, 255, 255), 350, 0, -1, "LEVEL 3");
        al_flip_display();
        break;
    case 6:
        al_draw_textf(game->level2_Font, al_map_rgb(255, 255, 255), 350, 0, -1, "LEVEL 4");
        al_flip_display();
        break;
    default:
        printf("drawlevel failed\n");
        break;
    }
}
