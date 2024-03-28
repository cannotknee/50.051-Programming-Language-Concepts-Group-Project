#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pet.h"
#include "pages.h"

#include "game.h"
#include "main.h"

int main1(int argc, char *argv[])
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
int main(int argc, char *argv[])
{
    int i;
    char* actionresult = (char *)malloc(256);
    char* statusreport = (char *)malloc(256);
    game *global_game = (game *)malloc(sizeof(game));
    init_game(global_game, "TestGame");
    set_name(global_game->pet, "TestPet");
    set_personality(global_game->pet);
    global_game->pet->stat_state[STAT_FATIGUE] = BAD_STATE;
    global_game->pet->stat_state[STAT_HUNGER] = BAD_STATE;
    global_game->pet->stat_state[STAT_CLEANLINESS] = BAD_STATE;

    for (i = 0; i < 7; i++)
    {
        report_result(global_game->pet, (action) i, 2, actionresult, statusreport);
        printf("%d\n", i);
        printf("%s\n", actionresult);
        printf("%s\n", statusreport);
    }
    
    printf("done\n");
    free_game(global_game);
    return 0;
}