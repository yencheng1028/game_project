#include "myheader.h"

// Update the positions of enemies and handle their bullet firing
void update_enemy_positions(game_data* game, plane_data* plane,ALLEGRO_DISPLAY* display,int scorevalue) {
    for (int i = 0; i < game->num_enemies; ++i) {
        // Move enemies based on their velocity
        game->enemies[i].x += game->enemies[i].vx;
        game->enemies[i].y += game->enemies[i].vy;

        // Bounce off the screen edges
        if (game->enemies[i].x < 0 || game->enemies[i].x + game->enemies[i].width > SCREEN_W ) {
            game->enemies[i].vx = -game->enemies[i].vx;
        }

        // Reverse direction when reaching the top or bottom of the screen
        if (game->enemies[i].y < 0 || game->enemies[i].y + game->enemies[i].height > SCREEN_H / 3) {
            game->enemies[i].vy = -game->enemies[i].vy;
        }

        // Check for bullet firing timer events
        ALLEGRO_EVENT ev;
        al_wait_for_event(game->enemies[i].event_enemy_queue, &ev);

        if (ev.type == ALLEGRO_EVENT_TIMER && ev.timer.source == game->enemies[i].bullet_timer) {
            fire_bullet(&game->enemies[i]);
        }

        // Move and handle enemy bullets
        for (int j = 0; j < game->enemies[i].num_bullets; ++j) {
            game->enemies[i].bullets[j].y += game->enemies[i].bullets[j].vy;

            // Remove bullets when they go off-screen
            if (game->enemies[i].bullets[j].y > SCREEN_H) {
                al_destroy_bitmap(game->enemies[i].bullets[j].bullet_pic);
                game->enemies[i].bullets[j] = game->enemies[i].bullets[game->enemies[i].num_bullets - 1];
                game->enemies[i].num_bullets--;
            }
        }
    }
    // Check and handle collisions between bullets and the player's plane
    check_and_remove_bullet_collision(game, plane,display,scorevalue);
}

// Move the player's plane based on keyboard input
void movePlane(plane_data* plane, const ALLEGRO_KEYBOARD_EVENT* kbEvent) {
    if (kbEvent->keycode == ALLEGRO_KEY_LEFT && plane->x > PLANE_MIN) {
        plane->x -= PLANE_MOVE;
    } else if (kbEvent->keycode == ALLEGRO_KEY_RIGHT && plane->x < PLANE_MAX-PLANE_SIZE) {
        plane->x += PLANE_MOVE;
    }
}

// Fire bullets from enemy entities
void fire_bullet(enemy_data* enemy) {
    al_stop_samples();

    if (enemy->num_bullets < MAX_BULLETS) {
        initialize_bullet(enemy, enemy->num_bullets);
        
        enemy->num_bullets++;
        al_play_sample(enemy->shoot_sound, 0.1, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
    }
}

// Fire bullets from the player's plane
void fire_plane_bullet(plane_data* plane) {
    ALLEGRO_EVENT ev;
    al_wait_for_event(plane->event_plane_bullet_queue, &ev);

    // Move and handle player bullets
    for (int j = 0; j < plane->num_bullets; ++j) {
        plane->bullets[j].y += plane->bullets[j].vy;

        // Remove bullets when they go off-screen
        if (plane->bullets[j].y < 0) {
            al_destroy_bitmap(plane->bullets[j].bullet);
            plane->bullets[j] = plane->bullets[plane->num_bullets - 1];
            plane->num_bullets--;
        }
    }

    // Fire bullets based on a timer event
    if (ev.type == ALLEGRO_EVENT_TIMER && ev.timer.source == plane->plane_bullet_timer) {
        if (plane->num_bullets < MAX_PLANE_BULLETS) {
            initialize_plane_bullet(plane, plane->num_bullets);
            plane->num_bullets++;
        }
    }
}

// Fire a different type of bullet from the player's plane
void fire_plane_bullet2(plane_data *plane) {
    ALLEGRO_EVENT ev;
    al_wait_for_event(plane->event_plane_bullet_queue2, &ev);

    // Move and handle the second type of player bullets
    for (int j = 0; j < plane->num_bullets2; ++j) {
        plane->bullets2[j].y += plane->bullets2[j].vy;

        // Remove bullets when they go off-screen
        if (plane->bullets2[j].y < 0) {
            al_destroy_bitmap(plane->bullets2[j].bullet);
            plane->bullets2[j] = plane->bullets2[plane->num_bullets2 - 1];
            plane->num_bullets2--;
        }
    }

    // Fire the second type of bullets based on a timer event
    if (ev.type == ALLEGRO_EVENT_TIMER && ev.timer.source == plane->plane_bullet_timer2) {
        if (plane->num_bullets2 < MAX_PLANE_BULLETS) {
            initialize_plane_bullet2(plane, plane->num_bullets2);
            plane->num_bullets2++;
        }
    }
}
