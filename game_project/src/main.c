#include "myheader.h"

int main() 
{
    Gamebackground_call();

    int finish = 0;
    int counter = 0;
    Match match;
    Enemy *enemyPtr = &match.enemy;
    Aircraft *aircraftPtr = &match.aircraft;
    player_score *players = match.players;

    ALLEGRO_BITMAP *aircraft = NULL;   /* pointer to the aircraft's image bitmap */
    ALLEGRO_BITMAP *enemy = NULL;      /* pointer to the enemy's image bitmap */
    ALLEGRO_DISPLAY *display = NULL;   /* pointer to display */
    ALLEGRO_SAMPLE *boing = NULL;      /* pointer to sound file */
    ALLEGRO_SAMPLE *background = NULL; /* pointer to sound file */
    ALLEGRO_FONT *pongFont = NULL;     /* pointer to Font file */

    ALLEGRO_KEYBOARD_STATE KBstate;
    ALLEGRO_SAMPLE_ID backgroundId;

    allegroDriverInit();

    //display = al_create_display(SCREEN_W, SCREEN_H);

    enemy = al_load_bitmap("assets/enemy.png"); /* load the enemy bitmap */
    boing = al_load_sample("assets/soundenemy.wav"); /* load the sound file */
    srand(time(NULL));                          /* seed the random function */
    initEnemy(enemyPtr, enemy, boing);          /* initial the enemy */

    aircraft = al_load_bitmap("assets/aircraft.webp"); /* load the aircraft bitmap */
    initAircraft(aircraftPtr, aircraft);              /* initial the aircraft */

    initPlayers(players, N_PLAYER); 

    pongFont = al_load_ttf_font("assets/arial.ttf", 16, 0); /* load the FONT file */

    background = al_load_sample("assets/bgm.mp3"); /* load the background sound file */
    al_play_sample(background, 1, 0, 1, ALLEGRO_PLAYMODE_LOOP, &backgroundId);

    while (finish == 0)
    {
        al_get_keyboard_state(&KBstate);
        if (al_key_down(&KBstate, ALLEGRO_KEY_ESCAPE))
        {
            finish = 1;
        }

        /* draw text onto the buffer */
        al_draw_textf(pongFont, al_map_rgb(255, 255, 255), 75, 0, -1,
                      "Left Player Score: %d", players[PLAYER_L].score);
        al_draw_textf(pongFont, al_map_rgb(255, 255, 255), 400, 0, -1,
                      "Right Player Score: %d", players[PLAYER_R].score);

        moveAircraft(&match.aircraft, &KBstate); /* move the aircraft */
        al_draw_bitmap(aircraftPtr->img, 310, aircraftPtr->y, 0);

        moveEnemy(&match);                                          /* move the enemy */
        al_draw_bitmap(enemyPtr->img, enemyPtr->x, enemyPtr->y, 0); /* draw the bitmap */

        counter = counter + 1;
        printf("Hello, counter %d\n", counter);

        al_rest(0.01);

        /* display */
        al_flip_display(); /* Wait for the beginning of a vertical retrace. */
        al_clear_to_color(al_map_rgb(0, 0, 0));

        /* Clear the complete target bitmap, but confined by the clipping rectangle. */
    }

    al_stop_sample(&backgroundId); /* stop bgm */
    al_destroy_sample(background); /* destroy the background sound file */
    al_destroy_bitmap(enemy);      /* destroy the enemy bitmap */
    al_destroy_display(display);   /* destroy the display */
    al_destroy_bitmap(aircraft);   /* destroy the aircraft bitmap */
    al_destroy_sample(boing);      /* destroy the boing sound file */
    al_destroy_font(pongFont);     /* destroy the font */

    return 0;
} /* end main */

    

