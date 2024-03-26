#include "myheader.h"

// Function to clean up game-related resources
void cleanup(game_data* game) {
    al_destroy_bitmap(game->background);
    al_destroy_event_queue(game->event_queue);
    al_destroy_sample(game->background_music);
}

// Function to clean up enemy-related resources
void cleanup_enemies(game_data* game) {
    for (int i = 0; i < game->num_enemies; ++i) {
        al_destroy_bitmap(game->enemies[i].enemy_pic);

        for (int j = 0; j < game->enemies[i].num_bullets; ++j) {
            al_destroy_bitmap(game->enemies[i].bullets[j].bullet_pic);
        }

        al_destroy_display(game->enemies[i].enemy_display);
        al_destroy_event_queue(game->enemies[i].event_enemy_queue);
        al_destroy_timer(game->enemies[i].timer);
        al_destroy_timer(game->enemies[i].bullet_timer);
    }
}

// Function to clean up plane-related resources
void cleanup_plane(plane_data* plane) {
    al_destroy_bitmap(plane->plane_img);
    al_destroy_display(plane->plane_display);
    al_destroy_event_queue(plane->event_plane_queue);
    al_destroy_timer(plane->plane_timer);

    // Clean up plane bullets
    for (int j = 0; j < plane->num_bullets; ++j) {
        al_destroy_bitmap(plane->bullets[j].bullet);
    }
    al_destroy_timer(plane->plane_bullet_timer);

    // Clean up second set of plane bullets
    for (int j = 0; j < plane->num_bullets2; ++j) {
        al_destroy_bitmap(plane->bullets2[j].bullet);
    }
    al_destroy_timer(plane->plane_bullet_timer2);
}

// Function to clean up menu-related resources
void cleanupMenu(menu* button) {
    al_destroy_bitmap(button->menuBackgroundImage);
    al_destroy_bitmap(button->startGameImage);
    al_destroy_bitmap(button->exitGameImage);
    al_destroy_bitmap(button->illustrateImage);
    al_destroy_event_queue(button->event_queue);
}
