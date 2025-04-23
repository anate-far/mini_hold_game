#include "game_content.h"

//function
int entitie_move(t_map *map, t_entitie *player, int new_pos_x, int new_pos_y)
{

        //check if next pos isn't outside the map boundaries
        int obstacle_new_pos = check_new_pos(map, new_pos_x, new_pos_y);

        //if player try to exit map, we can't give hime the permission
        if(obstacle_new_pos == -1)
            return(1);
        //if obstacle is a hold display game over screen
        if(obstacle_new_pos == 1)
        {
            display_game_over_screen(map);
            return(-1);
        }

        //clean old postion
        map->array_of_map[player->pos_x][player->pos_y] = '.';
        //set new pos
        map->array_of_map[new_pos_x][new_pos_y] = player->sprite;
        player->pos_x = new_pos_x;
        player->pos_y = new_pos_y;
        //display map
        ft_display_map(map);
        return(0);
}

t_entitie *init_entitie(int pos_x, int pos_y, char sprite)
{
    t_entitie *entitie;


    entitie = malloc(sizeof(t_entitie));
    entitie->pos_x = pos_x;
    entitie->pos_y = pos_y;
    entitie->sprite = sprite;
    return(entitie);
}

void spawn_hole(t_map *map, int nb_hole)
{
    int i;
    int pos_x;
    int pos_y;

    //max is the total number of cell in map
    i = -1;
    while(++i < nb_hole)
    {
        //check if all position is complete 
        if(i >= map->height * map->length)
            return;
        //set random position to x and y pos 
        pos_x = rand() % ((map->height - 1) - 0  + 1);
        pos_y = rand() % ((map->length -1) - 0 + 1);
        //check if isn't entitie on this pos else recalculate new position
        while(map->array_of_map[pos_x][pos_y] != map->default_sprite)
        {
            //set random position to x and y pos 
            pos_x = rand() % ((map->height -1) - 0  + 1);
            pos_y = rand() % ((map->length -1) - 0 + 1);
        }
        //set hole on map array
        map->array_of_map[pos_x][pos_y] = '*';
    }
}

int check_new_pos(t_map *map, int new_pos_x, int new_pos_y)
{
    //check if player want exit in the map
    if(new_pos_x < 0 || new_pos_x >= map->height
        || new_pos_y < 0 || new_pos_y >= map->length)
        return(-1);
    //check if ther are one hole in new pos
    if(map->array_of_map[new_pos_x][new_pos_y] == '*')
        return(1);
    return(0);
}