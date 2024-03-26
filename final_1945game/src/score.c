#include "myheader.h"

// Function to check collision between two rectangles
int check_collision(float x1, float y1, int w1, int h1, float x2, float y2, int w2, int h2)
{
    return x1 < x2 + w2 &&
           x1 + w1 > x2 &&
           y1 < y2 + h2 &&
           y1 + h1 > y2;
}

// Function to check and handle collisions between bullets and enemies/planes
void check_and_remove_bullet_collision(game_data *game, plane_data *plane,ALLEGRO_DISPLAY* display,int scorevalue)
{
    player_data *playersPtr = game->players;

    // Check collision between enemy bullets and the player's plane
    for (int i = 0; i < game->num_enemies; ++i)
    {
        for (int j = 0; j < game->enemies[i].num_bullets; ++j)
        {
            if (check_collision(game->enemies[i].bullets[j].x, game->enemies[i].bullets[j].y,
                                game->enemies[i].bullets[j].width, game->enemies[i].bullets[j].height,
                                plane->x + 20, plane->y, plane->width, plane->height))
            {
                // Remove bullet upon collision
                al_destroy_bitmap(game->enemies[i].bullets[j].bullet_pic);
                game->enemies[i].bullets[j] = game->enemies[i].bullets[game->enemies[i].num_bullets - 1];
                game->enemies[i].num_bullets--;
                
                // Decrease player's health
                plane->health--;

                break;
            }
        }
    }

    // Check collision between player's bullets and enemies
    if (playersPtr[PLAYER_1].score < 560)
    {
        for (int i = 0; i < plane->num_bullets; ++i)
        {
            for (int j = 0; j < game->num_enemies; ++j)
            {
                if (PLAYER_1 == 0)
                {
                    if (check_collision(plane->bullets[i].x, plane->bullets[i].y,
                                        plane->bullets[i].width, plane->bullets[i].height,
                                        game->enemies[j].x+20, game->enemies[j].y,
                                        game->enemies[j].width - 40, game->enemies[j].height-40))
                    {
                        // Remove bullet upon collision
                        al_destroy_bitmap(plane->bullets[i].bullet);
                        plane->bullets[i] = plane->bullets[plane->num_bullets - 1];
                        plane->num_bullets--;

                        // Update enemy destruction count, player's score, and print information
                        game->enemies[j].destroy_enemy++;
                        playersPtr[PLAYER_1].score += 20;
                        printf("enemy X POSITION=%f~%f\n", game->enemies[j].x, game->enemies[j].x + game->enemies[j].width);
                        printf("enemy Y POSITION=%f~%f\n", game->enemies[j].y, game->enemies[j].y + game->enemies[j].height);
                        printf("plane Bullet POSITION=(%f,%f)\n", plane->bullets[i].x, plane->bullets[i].y);
                        printf("\n");
                        break;
                    }
                }
            }
        }
    }

    // Check collision between player's bullets (level 2) and enemies
    if (playersPtr[PLAYER_1].score >= 560)
    {
        for (int i = 0; i < plane->num_bullets2; ++i)
        {
            for (int j = 0; j < game->num_enemies; ++j)
            {
                if (PLAYER_1 == 0)
                {
                    if (check_collision(plane->bullets2[i].x, plane->bullets2[i].y,
                                        plane->bullets2[i].width, plane->bullets2[i].height,
                                        game->enemies[j].x, game->enemies[j].y-20,
                                        game->enemies[j].width - 20, game->enemies[j].height))
                    {
                        // Remove bullet upon collision
                        al_destroy_bitmap(plane->bullets2[i].bullet);
                        plane->bullets2[i] = plane->bullets2[plane->num_bullets2 - 1];
                        plane->num_bullets2--;

                        // Update enemy destruction count, player's score, and print information
                        game->enemies[j].destroy_enemy = game->enemies[j].destroy_enemy + 2;
                        playersPtr[PLAYER_1].score += 20;
                        printf("enemy X POSITION=%f~%f\n", game->enemies[j].x, game->enemies[j].x + game->enemies[j].width);
                        printf("enemy Y POSITION=%f~%f\n", game->enemies[j].y, game->enemies[j].y + game->enemies[j].height);
                        printf("plane Bullet POSITION=(%f,%f)\n", plane->bullets2[i].x, plane->bullets2[i].y);
                        printf("\n");
                        break;
                    }
                }
            }
        }
    }

    // Remove enemies marked for destruction
    for (int i = 0; i < game->num_enemies; ++i)
    {
        if (game->enemies[i].destroy_enemy >= 2)
        {
            // Other destruction code for enemy resources

            // Remove destroyed enemy
            game->enemies[i] = game->enemies[game->num_enemies - 1];
            game->num_enemies--;
        }
    }

    // Spawn new enemies based on player's score milestones
    if (playersPtr[PLAYER_1].score == 200)
    {
        spawn_new_enemies(game);
    }

    if (playersPtr[PLAYER_1].score == 320)
    {
        spawn_new_enemies2(game);
    }

    if (playersPtr[PLAYER_1].score == 560)
    {
        spawn_new_enemies3(game);
    }

    // Check for victory or defeat conditions
    if (game->num_enemies == 0)
    {   
        printf("You WIN\n");
        
        scorevalue = playersPtr[PLAYER_1].score;
       
        drawlevel(game, 1);
        ScoreFileSave (scorevalue);
        cleanup(game);
        cleanup_enemies(game);
        cleanup_plane(plane);
        al_destroy_display(display);
    }

    if (plane->health <= 0)
    {
        printf("You LOSE\n");
        
        scorevalue = playersPtr[PLAYER_1].score;
        
        
        drawlevel(game, 2);
        ScoreFileSave (scorevalue);
        cleanup(game);
        cleanup_enemies(game);
        cleanup_plane(plane);
        al_destroy_display(display);
    }
}
