#include "myheader.h"

void initAircraft(Aircraft *aircraftPtr, ALLEGRO_BITMAP *img)
{
    /* give aircraft its initial y-coordinate */
    aircraftPtr->y = SCREEN_H / 2;

    aircraftPtr->img = img;
}

void moveAircraft(Aircraft *aircraftPtr, ALLEGRO_KEYBOARD_STATE *KBstatePtr)
{
    if(al_key_down(KBstatePtr, ALLEGRO_KEY_A))
        aircraftPtr->y -= AIRCRAFT_MOVE;
    if(al_key_down(KBstatePtr, ALLEGRO_KEY_D))
        aircraftPtr->y += AIRCRAFT_MOVE;

    /* make sure the aircraft don go off screen */
    if (aircraftPtr->y < LEFT_BORDER)
        aircraftPtr->y = LEFT_BORDER;
    if (aircraftPtr->y > RIGHT_BORDER)
        aircraftPtr->y = RIGHT_BORDER;
}
