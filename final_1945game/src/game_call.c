#include "myheader.h"

// Function to handle the menu and game initialization
void menu_call(int scorevalue) {
    game_data game;
    plane_data plane;
    menu button;
    if (!al_init() || !al_init_image_addon() || !al_install_audio() || !al_init_acodec_addon() || !al_install_keyboard()) {
        printf("Initialization failed\n");
    }

    ALLEGRO_DISPLAY* display = al_create_display(SCREEN_W, SCREEN_H);
    // Initialize the menu buttons
    if (initializeButton(&button,display) != 0) {
        fprintf(stderr, "Initialization failed!\n");
        return;
    }
   
    

    // Main loop for the menu
    while (1) {
        drawMenu(&button,scorevalue);
        
        ALLEGRO_EVENT ev;

        // Check for events in the menu event queue
        if (al_get_next_event(button.event_queue, &ev)) {
            // Handle input events for the menu
            handleInput(&ev, &button, &game);

            // If the start button is pressed, switch to the game
            if (button.isPressed) {
                cleanupMenu(&button);
                initialize_all(&game, &plane, 5,display);
                game.Font = NULL;
                game.Font = al_load_ttf_font("arial.ttf", 16, 0);
                printf("Switching to game\n");
                Gamebackground_call(&game, &plane,display,scorevalue);
                cleanup(&game);
                cleanup_enemies(&game);
                cleanup_plane(&plane);
            }

            // If the window is closed or the exit button is pressed, exit the program
            if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE || button.shouldExit) {
                button.shouldExit = true;
                printf("exit\n");
                cleanupMenu(&button);
                cleanup(&game);
                cleanup_enemies(&game);
                cleanup_plane(&plane);
                break;
            }
        }
    }
}

// Function to handle the game background and player interactions
void Gamebackground_call(game_data* game, plane_data* plane,ALLEGRO_DISPLAY* display,int scorevalue) {
    player_data *playersPtr = game->players;
    initPlayers(playersPtr,1);
    al_play_sample_instance(game->background_music_instance);
    printf("gamebackground call\n");
    int isPaused = 0;
    bool showImage = false;

    // Main loop for the game background
    while (1) {
        if (!isPaused) {
            update_enemy_positions(game, plane,display,scorevalue);
            draw_game(game, plane);

            // Fire different bullets based on the player's score
            if (game->players[PLAYER_1].score < 560)
                fire_plane_bullet(plane);
            if (game->players[PLAYER_1].score >= 560)
                fire_plane_bullet2(plane);
        }

        // Display different levels based on the player's score
        if (playersPtr[PLAYER_1].score < 200) {
            drawlevel(game, 3);
        }
        if (playersPtr[PLAYER_1].score >= 200 && playersPtr[PLAYER_1].score < 320) {
            drawlevel(game, 4);
        }
        if (playersPtr[PLAYER_1].score >= 320 && playersPtr[PLAYER_1].score < 560) {
            drawlevel(game, 5);
        }
        if (playersPtr[PLAYER_1].score >= 560) {
            drawlevel(game, 6);
        }

        ALLEGRO_EVENT ev;
        ALLEGRO_EVENT plane_ev;

        // Wait for events in the game and plane event queues
        al_wait_for_event(game->event_queue, &ev);
        al_wait_for_event(plane->event_plane_queue, &plane_ev);

        // Handle events to exit the game
        if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE || (plane_ev.type == ALLEGRO_EVENT_KEY_DOWN && plane_ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE)) {
            cleanup(game);
            cleanup_enemies(game);
            cleanup_plane(plane);
            break;
        } else if (plane_ev.type == ALLEGRO_EVENT_KEY_DOWN || plane_ev.type == ALLEGRO_EVENT_KEY_UP) {
            // Pause the game on Tab key press
            if (plane_ev.keyboard.keycode == ALLEGRO_KEY_TAB && plane_ev.type == ALLEGRO_EVENT_KEY_DOWN) {
                isPaused = !isPaused;
                showImage = !showImage;
                
                // Show a pause image on game pause
                if (showImage) {
                    al_draw_bitmap(game->pause_image, 0, 0, 0);
                    al_flip_display();
                    printf("showimage\n");
                }
            } else {
                // Move the plane based on keyboard input
                movePlane(plane, &plane_ev.keyboard);
            }
        }
    }

    // Cleanup after exiting the game loop
    cleanup_enemies(game);
    al_destroy_display(display);
}
