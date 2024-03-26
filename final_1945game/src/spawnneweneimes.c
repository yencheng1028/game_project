#include "myheader.h"

// Function to spawn new enemies for level 1
void spawn_new_enemies(game_data* game) {
    // Reset the destroy_enemy flag for enemies in the array
    for (int i = 0; i < MAX_ENEMIES_LEVEL2; i++) {
        game->enemies[i].destroy_enemy = 1;
    }

    // Attempt to spawn NEW_ENEMY_COUNT new enemies
    for (int i = 0; i < NEW_ENEMY_COUNT; ++i) {
        // Check if the maximum number of enemies for this level is reached
        if (game->num_enemies < MAX_ENEMIES_LEVEL2) {
            // Initialize a new enemy
            initialize_enemies(&game->enemies[game->num_enemies], 1, game->display, game->event_queue);
            
            // Ensure the new enemy does not collide with existing enemies
            while (check_collision_with_existing(game, &game->enemies[game->num_enemies])) {
                int width = 80;
                int height = 80;
                game->enemies[game->num_enemies].x = rand() % (SCREEN_W - width);
                game->enemies[game->num_enemies].y = rand() % (SCREEN_H / 3 - height);
            }

            // Create and start a timer for enemy bullet firing
            game->enemies[game->num_enemies].bullet_timer = al_create_timer(0.001);
            al_register_event_source(game->event_queue, al_get_timer_event_source(game->enemies[game->num_enemies].bullet_timer));
            al_start_timer(game->enemies[game->num_enemies].bullet_timer);

            // Increment the number of enemies
            game->num_enemies++;
        } else {
            printf("1\n");
            break;
        }
    }

    // Handle bullet firing for all existing enemies
    for (int i = 0; i < game->num_enemies; ++i) {
        ALLEGRO_EVENT event;
        while (al_get_next_event(game->event_queue, &event)) {
            if (event.type == ALLEGRO_EVENT_TIMER && event.timer.source == game->enemies[i].bullet_timer) {
                fire_bullet(&game->enemies[i]);
            }
        }
    }
    
}

// Function to spawn new enemies for level 2
void spawn_new_enemies2(game_data* game) {
    // Reset the destroy_enemy flag for enemies in the array
    for (int i = 0; i < MAX_ENEMIES_LEVEL3; i++) {
        game->enemies[i].destroy_enemy = 0;
    }

    // Attempt to spawn NEW_ENEMY_COUNT new enemies
    for (int i = 0; i < NEW_ENEMY_COUNT; ++i) {
        // Check if the maximum number of enemies for this level is reached
        if (game->num_enemies < MAX_ENEMIES_LEVEL3) {
            // Initialize a new enemy
            initialize_enemies(&game->enemies[game->num_enemies], 1, game->display, game->event_queue);

            // Ensure the new enemy does not collide with existing enemies
            while (check_collision_with_existing(game, &game->enemies[game->num_enemies])) {
                int width = 80;
                int height = 80;
                game->enemies[game->num_enemies].x = rand() % (SCREEN_W - width);
                game->enemies[game->num_enemies].y = rand() % (SCREEN_H / 3 - height);
            }

            // Create and start a timer for enemy bullet firing
            game->enemies[game->num_enemies].bullet_timer = al_create_timer(0.001);
            al_register_event_source(game->event_queue, al_get_timer_event_source(game->enemies[game->num_enemies].bullet_timer));
            al_start_timer(game->enemies[game->num_enemies].bullet_timer);

            // Increment the number of enemies
            game->num_enemies++;
        } else {
            printf("2\n");
            break;
        }
    }

    // Handle bullet firing for all existing enemies
    for (int i = 0; i < game->num_enemies; ++i) {
        ALLEGRO_EVENT event;
        while (al_get_next_event(game->event_queue, &event)) {
            if (event.type == ALLEGRO_EVENT_TIMER && event.timer.source == game->enemies[i].bullet_timer) {
                fire_bullet(&game->enemies[i]);
            }
        }
    }
}

// Function to spawn new enemies for level 3
void spawn_new_enemies3(game_data* game) {
    // Reset the destroy_enemy flag for enemies in the array
    for (int i = 0; i < MAX_ENEMIES_LEVEL4; i++) {
        game->enemies[i].destroy_enemy = -8;
    }

    // Attempt to spawn NEW_ENEMY_COUNT new enemies
    for (int i = 0; i < NEW_ENEMY_COUNT; ++i) {
        // Check if the maximum number of enemies for this level is reached
        if (game->num_enemies < MAX_ENEMIES_LEVEL4) {
            // Initialize a new enemy
            initialize_enemies(&game->enemies[game->num_enemies], 1, game->display, game->event_queue);

            // Ensure the new enemy does not collide with existing enemies
            while (check_collision_with_existing(game, &game->enemies[game->num_enemies])) {
                int width = 80;
                int height = 80;
                game->enemies[game->num_enemies].x = rand() % (SCREEN_W - width);
                game->enemies[game->num_enemies].y = rand() % (SCREEN_H / 3 - height);
            }

            // Create and start a timer for enemy bullet firing
            game->enemies[game->num_enemies].bullet_timer = al_create_timer(0.001);
            al_register_event_source(game->event_queue, al_get_timer_event_source(game->enemies[game->num_enemies].bullet_timer));
            al_start_timer(game->enemies[game->num_enemies].bullet_timer);

            // Increment the number of enemies
            game->num_enemies++;
        } else {
            printf("3\n");
            break;
        }
    }

    // Handle bullet firing for all existing enemies
    for (int i = 0; i < game->num_enemies; ++i) {
        ALLEGRO_EVENT event;
        while (al_get_next_event(game->event_queue, &event)) {
            if (event.type == ALLEGRO_EVENT_TIMER && event.timer.source == game->enemies[i].bullet_timer) {
                fire_bullet(&game->enemies[i]);
            }
        }
    }
}

// Function to check collision with existing enemies
int check_collision_with_existing(game_data* game, enemy_data* new_enemy) {
    for (int i = 0; i < game->num_enemies; ++i) {
        if (check_collision(new_enemy->x, new_enemy->y, new_enemy->width, new_enemy->height,
                            game->enemies[i].x, game->enemies[i].y, game->enemies[i].width, game->enemies[i].height)) {
            return 1; // Collision detected
        }
    }

    return 0; // No collision
}
