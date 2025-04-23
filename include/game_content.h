#ifndef GAME_CONTENT_H
#define GAME_CONTENT_H

#endif

#include <stdlib.h>
#include <unistd.h>
#include "ft_lib.h"

//MACRO
enum margin{M_TOP, M_RIGHT};
enum keys{K_UP = 'w', K_DOWN = 's', K_RIGHT = 'a', K_LEFT = 'd', K_EXIT = '\033'};

//struct
typedef struct s_entitie
{
    //graphical look
    char sprite;
    //position on map
    int pos_x;
    int pos_y;
}t_entitie;

typedef struct s_map
{
    //array for content of map
    char **array_of_map;
    //default sprite 
    char default_sprite;
    //size of map
    int height;
    int length;
    //player
    t_entitie *player;

}t_map;



//map function
void ft_display_map(t_map *map);
t_map *init_map(int height, int lenght);
void clean_map_and_ellement(t_map *map);
char **map_set_ellement(t_map *map, char sprite_ellement, int pos_x, int pos_y);
void display_game_over_screen(t_map *map);
void display_win_screen(t_map *map);
void display_margin(t_map *map, int margin);
int check_keys_is_good(char key);
int player_movement(t_map *map, char *key);
int check_win(t_map *map);

//entities function
int entitie_move(t_map *map, t_entitie *player, int new_pos_x, int new_pos_y);
t_entitie *init_entitie(int pos_x, int pos_y, char sprite);
void spawn_hole(t_map *map, int nb_hole);
int check_new_pos(t_map *map, int new_pos_x, int new_pos_y);