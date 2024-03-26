#include "myheader.h"

// Function to initialize Allegro, fonts, images, audio, and keyboard
int initialize_all(game_data* game, plane_data* plane, int num_enemies,ALLEGRO_DISPLAY* display) {
    al_init_font_addon();
    al_init_ttf_addon();



    if (!al_reserve_samples(2)) {
        printf("Audio sample reservation failed\n");
        return -1;
    }

    if (initialize_game(game, num_enemies, display) != 0) {
        printf("Game initialization failed\n");
        return -1;
    }

    if (initialize_enemies(game->enemies, game->num_enemies, game->display, game->event_queue) != 0) {
        printf("Enemy initialization failed\n");
        return -1;
    }

    if (initialize_plane(plane) != 0) {
        printf("Plane initialization failed\n");
        return -1;
    }

    return 0;
}

// Function to initialize menu buttons, fonts, display, images, and event queue
int initializeButton(menu* button,ALLEGRO_DISPLAY* display) {
    al_init_font_addon();
    al_init_ttf_addon();


    if (!al_init() || !al_init_image_addon()) {
        fprintf(stderr, "Failed to initialize Allegro!\n");
        return -1;
    }
    

    button->display = display;
    button->menuBackgroundImage = al_load_bitmap("./starry_sky1.jpg");
    button->history_Font = NULL;
    button->history_Font = al_load_ttf_font("arial.ttf", 20, 0);

    if (!button->display || !button->menuBackgroundImage) {
        fprintf(stderr, "Failed to initialize or load resources!\n");
        return -1;
    }

    // Load images for menu buttons
    button->startGameImage = al_load_bitmap("start.png");
    button->exitGameImage = al_load_bitmap("exit.png");
    button->illustrateImage = al_load_bitmap("./illustrate.jpg");
    button->nameImage = al_load_bitmap("./name.png");

    // Check if images loaded successfully
    if (!button->startGameImage || !button->exitGameImage || !button->illustrateImage || !button->nameImage) {
        fprintf(stderr, "Failed to load images for menu buttons!\n");
        return -1;
    }

    // Set positions for menu buttons
    button->startX = (SCREEN_W - al_get_bitmap_width(button->startGameImage)) / 2.0;
    button->startY = (SCREEN_H - al_get_bitmap_height(button->startGameImage)) / 2.0 - 50;
    button->exitX = (SCREEN_W - al_get_bitmap_width(button->exitGameImage)) / 2.0;
    button->exitY = (SCREEN_H - al_get_bitmap_height(button->exitGameImage)) / 2.0 + 50;
    button->illustrateX = (SCREEN_W - al_get_bitmap_width(button->illustrateImage)) / 2.0;
    button->illustrateY = (SCREEN_H - al_get_bitmap_height(button->illustrateImage)) / 2.0 + 100;
    button->nameX = (SCREEN_W - al_get_bitmap_width(button->nameImage)) / 2.0;
    button->nameY = (SCREEN_H - al_get_bitmap_height(button->nameImage)) / 2.0 + 100;

    // Create event queue and register event sources
    button->event_queue = al_create_event_queue();
    if (!button->event_queue) {
        fprintf(stderr, "Failed to create event queue!\n");
        return -1;
    }

    al_install_mouse();
    al_install_keyboard();
    al_register_event_source(button->event_queue, al_get_display_event_source(button->display));
    al_register_event_source(button->event_queue, al_get_mouse_event_source());
    al_register_event_source(button->event_queue, al_get_keyboard_event_source());

    // Initialize button states
    button->shouldExit = false;
    return 0;
}

// Function to initialize game data including display, background, fonts, and event queue
int initialize_game(game_data* game, int num_enemies,ALLEGRO_DISPLAY* display) {
    game->display = display;
    game->background = al_load_bitmap("./starry_sky1.jpg");
    game->pause_image = al_load_bitmap("./pause.jpg");
    game->win_image = al_load_bitmap("./win.png");
    game->lose_image = al_load_bitmap("./lose.png");
    game->level1_Font = NULL;
    game->level1_Font = al_load_ttf_font("arial.ttf", 20, 0);
    game->level2_Font = NULL;
    game->level2_Font = al_load_ttf_font("arial.ttf", 20, 0);
    game->level3_Font = NULL;
    game->level3_Font = al_load_ttf_font("arial.ttf", 20, 0);
    game->level4_Font = NULL;
    game->level4_Font = al_load_ttf_font("arial.ttf", 20, 0);

    // Check if display and background loaded successfully
    if (!game->display || !game->background) {
        return -1;
    }

    // Create event queue and register event source
    game->event_queue = al_create_event_queue();
    if (!game->event_queue) {
        return -1;
    }

    al_register_event_source(game->event_queue, al_get_display_event_source(game->display));

    // Set the number of enemies and initialize background music
    game->num_enemies = num_enemies;

    al_set_new_display_flags(ALLEGRO_OPENGL);
    game->background_music = al_load_sample("./background_music.wav");
    game->background_music_instance = al_create_sample_instance(game->background_music);

    al_set_sample_instance_playmode(game->background_music_instance, ALLEGRO_PLAYMODE_LOOP);
    al_attach_sample_instance_to_mixer(game->background_music_instance, al_get_default_mixer());

    return 0;
}

// Function to initialize enemies including loading images, timers, and setting initial positions
int initialize_enemies(enemy_data* enemies, int num_enemies, ALLEGRO_DISPLAY* display, ALLEGRO_EVENT_QUEUE* event_queue) {
    srand(time(NULL));

    for (int i = 0; i < num_enemies; ++i) {
        // Set enemy properties
        enemies[i].enemy_display = display;
        enemies[i].enemy_pic = al_load_bitmap("./enemy.png");

        // Check if enemy image loaded successfully
        if (!enemies[i].enemy_pic) {
            return -1;
        }

        enemies[i].event_enemy_queue = event_queue;
        enemies[i].timer = al_create_timer(1.0 / 240);
        enemies[i].bullet_timer = al_create_timer(BULLET_UPDATE_TIMER);
        enemies[i].shoot_sound = al_load_sample("enemy_shot.wav");

        // Check if shoot sound loaded successfully
        if (!enemies[i].shoot_sound) {
            return -1;
        }

        // Check if timers created successfully
        if (!enemies[i].timer || !enemies[i].bullet_timer) {
            return -1;
        }

        // Register timers as event sources and start them
        al_register_event_source(enemies[i].event_enemy_queue, al_get_timer_event_source(enemies[i].timer));
        al_start_timer(enemies[i].timer);
        al_register_event_source(enemies[i].event_enemy_queue, al_get_timer_event_source(enemies[i].bullet_timer));
        al_start_timer(enemies[i].bullet_timer);

        // Set enemy dimensions and initial positions
        enemies[i].width = 80;
        enemies[i].height = 80;

        enemies[i].x = rand() % (SCREEN_W - enemies[i].width);
        enemies[i].y = rand() % (SCREEN_H / 3 - enemies[i].height);
        enemies[i].vx = (rand() % 2 == 0 ? 1 : -1) * (rand() % 5 + 1);
        enemies[i].vy = (rand() % 2 == 0 ? 1 : -1) * (rand() % 5 + 1);
        enemies[i].num_bullets = 0;
    }

    return 0;
}

// Function to initialize bullet properties for enemies
void initialize_bullet(enemy_data* enemy, int index) {
    enemy->bullets[index].bullet_pic = al_load_bitmap("./enemy_bullet.png");
    enemy->bullets[index].x = enemy->x + enemy->width / 2;
    enemy->bullets[index].y = enemy->y + enemy->height;
    enemy->bullets[index].vy = 5.0;
    enemy->bullets[index].width = 40;
    enemy->bullets[index].height = 40;
}

// Function to initialize bullet properties for player's plane
void initialize_plane_bullet(plane_data* plane, int index) {
    plane->bullets[index].bullet = al_load_bitmap("./plane_bullet.png");
    plane->bullets[index].x = plane->x + plane->width / 2;
    plane->bullets[index].y = plane->y + plane->height;
    plane->bullets[index].vy = -20.0;
    plane->bullets[index].width = 40;
    plane->bullets[index].height = 40;
}

// Function to initialize second type of bullet properties for player's plane
void initialize_plane_bullet2(plane_data* plane, int index) {
    plane->bullets2[index].bullet = al_load_bitmap("ball.bmp");
    plane->bullets2[index].x = plane->x + plane->width / 2-20;
    plane->bullets2[index].y = plane->y + plane->height;
    plane->bullets2[index].vy = -20.0;
    plane->bullets2[index].width = 80;
    plane->bullets2[index].height = 80;
}

// Function to initialize player's plane properties
int initialize_plane(plane_data* plane) {
    plane->health = 5;
    plane->x = SCREEN_W / 2;
    plane->y = SCREEN_H - PLANE_SIZE - 10;
    plane->plane_img = al_load_bitmap("./plane.png");
    plane->plane_timer = al_create_timer(1.0 / 60);
    plane->event_plane_queue = al_create_event_queue();
    plane->event_plane_bullet_queue = al_create_event_queue();
    plane->event_plane_bullet_queue2 = al_create_event_queue();
    plane->plane_bullet_timer = al_create_timer(PLANE_BULLET_UPDATE_TIMER);
    plane->plane_bullet_timer2 = al_create_timer(PLANE_BULLET_UPDATE_TIMER);
    al_register_event_source(plane->event_plane_queue, al_get_timer_event_source(plane->plane_timer));
    al_register_event_source(plane->event_plane_queue, al_get_keyboard_event_source());
    al_start_timer(plane->plane_timer);
    al_register_event_source(plane->event_plane_bullet_queue, al_get_timer_event_source(plane->plane_bullet_timer));
    al_register_event_source(plane->event_plane_bullet_queue2, al_get_timer_event_source(plane->plane_bullet_timer2));
    al_start_timer(plane->plane_bullet_timer);
    al_start_timer(plane->plane_bullet_timer2);

    return 0;
}


void handleInput(ALLEGRO_EVENT *ev, menu *button, game_data *game) {
    // Get the dimensions of the start and exit buttons
    int startWidth = al_get_bitmap_width(button->startGameImage);
    int startHeight = al_get_bitmap_height(button->startGameImage);
    int exitWidth = al_get_bitmap_width(button->exitGameImage);
    int exitHeight = al_get_bitmap_height(button->exitGameImage);

    // Check if the event type is a mouse button down
    if (ev->type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
        // Get the mouse coordinates
        int mouseX = ev->mouse.x;
        int mouseY = ev->mouse.y;

        // Check if the mouse is within the start button's range
        button->isXInButtonRange = (mouseX >= button->startX) && (mouseX <= button->startX + startWidth);
        button->isYInButtonRange = (mouseY >= button->startY) && (mouseY <= button->startY + startHeight);

        // Check if the mouse is within the exit button's range
        button->isXInButtonRange_exit = (mouseX >= button->exitX) && (mouseX <= button->exitX + exitWidth);
        button->isYInButtonRange_exit = (mouseY >= button->exitY) && (mouseY <= button->exitY + exitHeight);

        // Handle start button press
        if (button->isXInButtonRange && button->isYInButtonRange) {
            button->isPressed = true;
            printf("button start is pressed\n");
        }

        // Handle exit button press
        if (button->isXInButtonRange_exit && button->isYInButtonRange_exit) {
            printf("button exit is pressed\n");
            button->shouldExit = true;
        }
    }
}

void initPlayers(player_data *players, int nPlayer)
{
    int i = 0;
    for (i = 0; i < nPlayer; ++i)
    {
        players[i].score = 0;
    }
}
