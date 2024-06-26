#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "types.h"
#include "display_page.h"
#include "game.h"

void display_main(void)
{

    printf("This is the main menu page\n");
    printf("1. New Game\n");
    printf("2. Load Game\n");
    printf("0. Quit\n");
}

void display_home(void)
{
    int i;
    printf("This is the home page     %s\n", global_game->period_of_day[global_game->part_of_day]);
    if (global_game->pets_owned != NULL)
    {
        for (i = 0; i < MAX_PETS; i++)
        {
            if (global_game->pets_owned[i] != NULL)
            {
                printf("%d. %s\n", i + 1, global_game->pets_owned[i]->name);
            }
            else
            {
                printf("%d. Empty\n", i + 1);
            }
        }
    }
    printf("6. Store\n");
    printf("7. Settings\n");
    printf("8. Save\n");
    printf("9. End day\n");
    printf("0. Exit\n");
}

void display_store(void)
{
    printf("This is the store page      ");
    printf("Currency: %d     ", global_game->money);
    printf("%s\n", global_game->period_of_day[global_game->part_of_day]);

    printf("1. Buy New Egg\n");
    printf("2. Buy Medicine   (currently owned: %d)\n", global_game->medicine_owned);
    printf("0. Exit\n");
}

void display_settings(void)
{
    printf("Settings\n");
    if (global_game->action_confirmation == 1)
    {
        printf("1. disable action confirmation\n");
    }
    else
    {
        printf("1. enable action confirmation\n");
    }
    printf("0. Exit\n");
}

void display_pet_menu(pet *p)
{
    display_pet_image(p);
    printf("This is the pet page     %s\n", global_game->period_of_day[global_game->part_of_day]);
    printf("1. Feed\n");
    printf("2. Play\n");
    printf("3. Clean\n");
    printf("4. Train\n");
    printf("5. Medicine   (currently owned: %d)\n", global_game->medicine_owned); /* for testing purposes only, since feeding medicine is a free action*/
    printf("6. Sell\n");
    printf("0. Exit\n");
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
            printf("%d. Slot %d\n", i + 1, i + 1);
            i++;
        }
        free(save_files);
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
}

void display_confirmation(void)
{
    printf("Doing this will take up time, are you sure?\n");
    printf("1. Yes\n");
    printf("2. No\n");
}

/* display pet image from file*/
void display_pet_image(pet *p)
{
    char line[256];
    FILE *file = fopen(p->display_filename, "r");
    if (file == NULL)
    {
        printf("Error: File not found\n");
    }

    while (fgets(line, sizeof(line), file))
    {
        printf("%s", line);
    }
    printf("\n");

    fclose(file);
}

/* randomize pet display image on level change */
void randomize_pet_display(pet *p, level currlevel)
{
    char filename[MAX_FILENAME_LENGTH];
    if (currlevel == EGG)
    {
        int rand_int = (rand() % NUM_EGG_STAGE_FILES) + 1;
        snprintf(filename, MAX_FILENAME_LENGTH, "image" PATH_SEPARATOR "egg_display_%d.txt", rand_int);
    }
    else if (currlevel == BABY)
    {
        int rand_int = (rand() % NUM_BABY_STAGE_FILES) + 1;
        snprintf(filename, MAX_FILENAME_LENGTH, "image" PATH_SEPARATOR "baby_display_%d.txt", rand_int);
    }
    else if (currlevel == YOUNG)
    {
        int rand_int = (rand() % NUM_YOUNG_STAGE_FILES) + 1;
        snprintf(filename, MAX_FILENAME_LENGTH, "image" PATH_SEPARATOR "young_display_%d.txt", rand_int);
    }
    else if (currlevel == ADULT)
    {
        int rand_int = (rand() % NUM_ADULT_STAGE_FILES) + 1;
        snprintf(filename, MAX_FILENAME_LENGTH, "image" PATH_SEPARATOR "adult_display_%d.txt", rand_int);
    }
    else
    {
        printf("Error: Invalid level\n");
        return;
    }

    strcpy(p->display_filename, filename);
}
