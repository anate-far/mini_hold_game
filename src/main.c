#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <termios.h>
#include "game_content.h"
#include "ft_lib.h"

int main()
{
    char recov_key = 0;
    int state_of_player = 0;
    struct termios old_setting, new_setting;

    //save current setting of terminal
    tcgetattr(STDIN_FILENO, &old_setting);
    //set new setting on terrminal
    //disable display keys and disable keys enter validation
    new_setting = old_setting;
    new_setting.c_lflag &= ~(ICANON | ECHO);// the '|' melts bit, the '~' reverse them and the '&=' disable bit
                                            //00000100 00000010 -> 00000110 -> 11111001 -> disable bit with AND DOOR
    tcsetattr(STDIN_FILENO, TCSANOW, &new_setting);

    //init srand fo random pos
    srand(time(NULL));
    //init map
    t_map *map = init_map(30, 30);
    //init player
    map->player = init_entitie(15, 15, '@');
    map_set_ellement(map, map->player->sprite, map->player->pos_x, map->player->pos_y);
    //init hole
    spawn_hole(map, 5);
    //display first map
    ft_display_map(map);
    //loop for game exit press escape
    while(1 && recov_key != '\033' && state_of_player != -1 && ! check_win(map))
    {
        //clean map if the player is stoped
        if(state_of_player == 1)
        {
            write(1, "\033[H\033[J", 6);
            ft_display_map(map);
        }
        //ask to input player -> up / down / left / right
        recov_key = ft_getchar(STDIN_FILENO);
        //move player
        state_of_player = player_movement(map, &recov_key);
        //gen a new hold
        if(check_keys_is_good(recov_key))
            spawn_hole(map, 1);
    }
    clean_map_and_ellement(map);

    //restaurs setting of terminal
    tcsetattr(STDIN_FILENO, TCSANOW, &old_setting);
    return(0);
}