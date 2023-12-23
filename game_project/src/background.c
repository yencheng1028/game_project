#include "myheader.h"

void Gamebackground_call() 
{
    game_background game;

    if (initialize(&game) != 0) {
        fprintf(stderr, "Initialization failed!\n");
        return;
    }

    while (1) {
        draw(&game);

        ALLEGRO_EVENT ev;
        al_wait_for_event(game.event_queue, &ev);

        if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            break;
        }
    }

    cleanup(&game);
}


int initialize(game_background* game) {
    if (!al_init() || !al_init_image_addon()) {
        fprintf(stderr, "Failed to initialize Allegro!\n");
        return -1;
    }

    game->display = al_create_display(SCREEN_W, SCREEN_H);
    game->background = al_load_bitmap("assets/starry_sky1.jpg");

    if (!game->display || !game->background) {
        fprintf(stderr, "Failed to initialize or load resources!\n");
        return -1;
    }

    game->event_queue = al_create_event_queue();
    if (!game->event_queue) {
        fprintf(stderr, "Failed to create event queue!\n");
        return -1;
    }

    al_register_event_source(game->event_queue, al_get_display_event_source(game->display));

    return 0;
}

void cleanup(game_background* game) {
    al_destroy_bitmap(game->background);
    al_destroy_display(game->display);
    al_destroy_event_queue(game->event_queue);
}

void draw(game_background* game) {
    al_clear_to_color(al_map_rgb(0, 0, 0));

    int img_w = al_get_bitmap_width(game->background);
    int img_h = al_get_bitmap_height(game->background);

    al_draw_scaled_bitmap(
        game->background, 0, 0, img_w, img_h, 0, 0, SCREEN_W, SCREEN_H, 0
    );

    al_flip_display();
}
