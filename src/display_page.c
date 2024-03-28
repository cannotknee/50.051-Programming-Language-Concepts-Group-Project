#include <stdio.h>

#include "pet.h"
#include "game.h"
#include "display_page.h"
#include "game.h"

/*Options to display on page are not finalised yet, some options may need to be hidden depending on state of game */
/*TODO how to handle confirmation screens i.e. save completed quit?, confirm buy/sell, confirm read report. */

void display_main(void)
{

    printf("This is the main menu page\n");
    printf("1. New Game\n");
    printf("2. Load Game\n");
    printf("0. Quit\n");
    printf("\nEnter a number to select an option: ");
}

void display_home(void)
{
    printf("This is the home page\n");
    /* TODO: Print pet names dynamically */
    printf("1. Pet 1\n");
    printf("2. Pet 2\n");
    printf("3. Pet 3\n");
    printf("4. Store\n");
    printf("5. Save\n");
    printf("0. Exit\n");
    printf("\nEnter a number to select an option: ");
}

void display_store(void)
{
    printf("This is the store page      ");
    printf("Currency: %d\n", global_game->money);

    printf("1. Buy\n");
    printf("2. Buy\n");
    printf("3. Buy\n");
    printf("0. Exit\n");
    printf("\nEnter a number to select an option: ");
}

void display_pet(void)
{

    printf("This is the pet page\n");
    printf("1. Feed\n");
    printf("2. Play\n");
    printf("3. Clean\n");
    printf("4. Train\n");
    printf("5. Sleep\n");
    printf("6. Medicine\n");
    printf("7. Sell\n");
    printf("0. Exit\n");
    printf("\nEnter a number to select an option: ");
}

void display_loadgame(void)
{
    int i = 0;
    char **save_files = get_save_files();
    printf("This is the load game page\n");
    if (save_files == NULL)
    {
        printf("Nothing to see here\n");
        printf("0. Exit\n");
        return;
    }
    else
    {
        while (save_files[i] != NULL)
        {
            printf("%d. %s\n", i + 1, save_files[i]);
            i++;
        }
        printf("0. Exit\n");
    }
}

void display_savegame(void)
{
    printf("This is the save game page, choose a slot to save into:\n");
    /* TODO: Dynamically show if slot has existing file */
    printf("1. Slot 1\n");
    printf("2. Slot 2\n");
    printf("3. Slot 3\n");
    printf("0. Exit\n");
    printf("\nEnter a number to select an option: ");
}
