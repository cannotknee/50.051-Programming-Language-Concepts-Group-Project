#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pet.h"
#include "pages.h"

#include "game.h"
#include "main.h"

int main(int argc, char *argv[])
{

    while (running)
    {
        if (update_page)
        {
            printf("\033[H\033[J"); /*Clear screen, might want to find a more elegant way*/
            display_page(curr_page);
            update_page = 0;
        }

        fgets(input, BUFFER_SIZE, stdin);
        sscanf(input, "%d", &input_buffer);

        handle_input(input_buffer);
    }
    printf("Goodbye\n");

    exit(0);
}

/*for testing purposes*/
int main123(int argc, char *argv[])
{
    int i;
    game *global_game = (game *)malloc(sizeof(game));
    init_game(global_game, "TestGame");
    set_name(global_game->pet, "TestPet");
    set_personality(global_game->pet);

    for (i = 0; i < 10; i++)
    {
        update_all_stats(global_game->pet);
        print_stats(global_game->pet);
        print_since_last_change(global_game->pet);
    }

    free_pet(global_game->pet);
    return 0;
}