#include "myheader.h"

int main() {
    game_data game;
    plane_data plane;
    menu button;
    player_data *playersPtr;
    
    int scorevalue = 0 ;

    ScoreFileLoad (&scorevalue);
    printf("Loaded Score: %d\n", scorevalue);

    menu_call(scorevalue);

    cleanup(&game);
    cleanup_enemies(&game);
    cleanup_plane(&plane);
    cleanupMenu(&button);    
      
    return 0;
}
