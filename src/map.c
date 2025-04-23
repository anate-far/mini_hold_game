#include "game_content.h"

void ft_display_map(t_map *map)
{
    int i;
    int y;

    //clean terminal
    //\033 = escape [H = cursor on to of terminal  [J = clean terminal
    write(1, "\033[H\033[J", 6);
    display_margin(map, M_TOP);
    i = -1;
    //display map and content line to line
    while(++i < map->height)
    {
        y = -1;
        display_margin(map, M_RIGHT);
        while (++y < map->length)
        {
            //display map
            write(1, &map->array_of_map[i][y], 1);
            write(1, " ", 1);
        }
        write(1, "\n", 1);
    }
    //display option for mooving
    write(1,"\n",1);
    display_margin(map, M_RIGHT);
    write(1, "w [up] | s [down] | a [left] | d [right] | esp [exit]\n", 55);
}

t_map *init_map(int height, int lenght)
{
    t_map *map;
    int i;
    int y;

    map = malloc(sizeof(t_map));
    //set size
    map->height = height;
    map->length = lenght;
    //set default sprite
    map->default_sprite = '.';
    //set size of array of map
    map->array_of_map = malloc(sizeof(char*) * height);
    i = -1;
    while(++i < height)
        map->array_of_map[i] = malloc(sizeof(char) * lenght);
    //set map with noting entities
    i = -1;
    while(++i < map->height)
    {
        y = -1;
        while(++y < map->length)
        {
            map->array_of_map[i][y] = map->default_sprite;
        }
    }

    return (map);
}

char **map_set_ellement(t_map *map, char sprite_ellement, int pos_x, int pos_y)
{
    if(pos_x < map->height && pos_y < map->length)
        map->array_of_map[pos_x][pos_y] = sprite_ellement;
    else
        return(NULL);
    return (map->array_of_map);
}

void clean_map_and_ellement(t_map *map)
{
    int i;

    //destroy player
    free(map->player);
    //destroy array of map
    i = -1;
    while(++i < map->height)
        free(map->array_of_map[i]);
    free(map->array_of_map);
    //destroy map
    free(map);
}

void display_game_over_screen(t_map *map)
{
    //clean terminal
    //\033 = escape [H = cursor on to of terminal  [J = clean terminal
    write(1, "\033[H\033[J", 6);
    display_margin(map, M_TOP);
    display_margin(map, M_RIGHT);
    write(1, "#############################################\n", 46);
    display_margin(map, M_RIGHT);
    write(1, "                 GAME OVER\n", 27);
    display_margin(map, M_RIGHT);
    write(1, "               your are falling\n", 32);
    display_margin(map, M_RIGHT);
    write(1, "#############################################\n", 46);
    display_margin(map, M_TOP);
}

void display_win_screen(t_map *map)
{
    //clean terminal
    //\033 = escape [H = cursor on to of terminal  [J = clean terminal
    write(1, "\033[H\033[J", 6);
    display_margin(map, M_TOP);
    display_margin(map, M_RIGHT);
    write(1, "#############################################\n", 46);
    display_margin(map, M_RIGHT);
    write(1, "                  YOUR WIN\n", 27);
    display_margin(map, M_RIGHT);
    write(1, "                your are survie\n", 32);
    display_margin(map, M_RIGHT);
    write(1, "#############################################\n", 46);
    display_margin(map, M_TOP);
}

void display_margin(t_map *map, int margin)
{
    int row;
    int col;
    int number_of_margin;
    int i;

    //get size of terminal
    ft_get_terminal_size(&row, &col);

    //write margin
    i = -1;
    switch(margin)
    {
        case M_TOP:
            number_of_margin = (row - map->height) / 2;
            while(++i < number_of_margin)
                write(1, "\n", 1);
            break;
        case M_RIGHT:
            number_of_margin = (col / 2) - map->length;
            while (++i < number_of_margin)
                write(1, " ", 1);
            break;
    }
}

int check_keys_is_good(char key)
{
    if(key == K_UP
        || key == K_DOWN
        || key == K_RIGHT
        || key == K_LEFT
        || key == K_EXIT)
        return(1);
    return(0);
}

int player_movement(t_map *map, char *key)
{
    int state_of_player = 0;

    switch (*key)
    {
    //deplacement temporaire 
    case K_UP:
        state_of_player = entitie_move(map, map->player, map->player->pos_x -1, map->player->pos_y);
        break;
    case K_DOWN:
        state_of_player = entitie_move(map, map->player, map->player->pos_x +1, map->player->pos_y);
        break;
    case K_RIGHT:
        state_of_player =  entitie_move(map, map->player, map->player->pos_x, map->player->pos_y -1);
        break;
    case K_LEFT:
        state_of_player = entitie_move(map, map->player, map->player->pos_x, map->player->pos_y +1);
        break;
        
    default:
        break;
    }
    return(state_of_player);
}

int check_win(t_map *map)
{
    int i;
    int y;

    i = -1;
    while(++i < map->height)
    {
        y = -1;
        while(++y < map->length)
        {
            if(map->array_of_map[i][y] == map->default_sprite)
                return(0);
        }
    }
    display_win_screen(map);
    return(1);
}
