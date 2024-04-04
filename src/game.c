#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>

#include "types.h"
#include "game.h"

void init_game(game *g, char *name)
{
    int i;
    g->name = malloc(strlen(name) + 1);
    strcpy(g->name, name);
    g->part_of_day = 0;
    g->period_of_day = (char **)malloc(4 * sizeof(char *));
    g->period_of_day[0] = "Morning";
    g->period_of_day[1] = "Afternoon";
    g->period_of_day[2] = "Evening";
    g->period_of_day[3] = "Night";
    g->actions = MAX_ACTIONS;
    g->money = 100;
    g->medicine_owned = 0;
    g->pets_owned = (pet **)malloc(10 * sizeof(pet *));
    for (i = 0; i < 10; i++)
    {
        g->pets_owned[i] = NULL;
    }
    g->action_confirmation = 1;
}

void update_day(game *g)
{
    if (g->part_of_day < 3)
    {
        g->part_of_day++;
    }
    else
    {
        printf("Error: This should not be reachable, day updated when should have blocked due to no actions left\n");
    }
}

void end_day(game *g){
    g->part_of_day = 0;
}

void free_game(game *g)
{
    int i;
    /*To check for any pet pointers and free them if necessary*/
    for (i = 0; i < 10; i++)
    {
        free(g->pets_owned[i]);
    }
    free(g->period_of_day);
    free(g->name);
    free(g);
}

int save(game *g, int index)
{
    char filename[50];
    FILE *file;

    /* Check if the slot is within valid range (1 to 3) */
    if (index < 1 || index > 3)
    {
        printf("Invalid slot index. Slot index must be between 1 and 3.\n");
        return 0;
    }

    /* Construct filename based on the slot index */
    sprintf(filename, "save_files/save%d.csv", index);

    /* Check if the file already exists */
    if (access(filename, F_OK) == 0)
    {
        char response;
        printf("A saved game already exists in slot %d. Do you want to overwrite it? (y/n): ", index);
        scanf(" %c", &response);

        /* Clear input buffer */
        while (getchar() != '\n')
            ;

        if (response != 'y' && response != 'Y')
        {
            printf("Save operation aborted.\n");
            return 0;
        }
    }

    /* Open the file for writing */
    file = fopen(filename, "w");
    if (file == NULL)
    {
        printf("Error: Could not create save file %s\n", filename);
        return 0;
    }

    /* Check if game data and pet data are valid */
    if (g == NULL || g->pets_owned == NULL || g->name == NULL)
    {
        printf("Error: Invalid current game data. Please restart the game.\n");
        fclose(file);
        return 0;
    }

    /* Write game state to save file */
    fprintf(file, "%d,%d,%d\n", g->part_of_day, g->actions, g->money);

    fclose(file);
    printf("Game saved successfully to slot %d.\n", index);
    return 1;
}

int load(int index)
{
    char filename[50];
    FILE *file;
    int i;

    /* Declare variables at the beginning of the function */
    game *g;

    /* Determine the filename based on the index provided */
    sprintf(filename, "save_files/save%d.csv", index);

    /* Open the file for reading */
    file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Error: Could not open file %s\n", filename);
        return 0;
    }

    /* Allocate memory for the game structure */
    g = (game *)malloc(sizeof(game));
    if (g == NULL)
    {
        printf("Error: Memory allocation failed for game structure\n");
        fclose(file);
        return 0;
    }

    /* Allocate memory for pet structure within the game */
    g->pets_owned = (pet **)malloc(10 * sizeof(pet *)); /* currently set to a max of 10 pets*/
    if (g->pets_owned == NULL)
    {
        printf("Error: Memory allocation failed for pet structure\n");
        fclose(file);
        free(g);
        return 0;
    }

    /* Allocate memory for pet name attribute */
    g->name = (char *)malloc(NAME_LENGTH * sizeof(char));
    if (g->name == NULL)
    {
        printf("Error: Memory allocation failed for game name\n");
        fclose(file);
        for (i = 0; i < 10; i++)
        {
            free(g->pets_owned[i]);
        }
        free(g);
        return 0;
    }

    /* Read game state from save file */
    if (fscanf(file, "%d,%d,%d,%s\n", &g->part_of_day, &g->actions, &g->money, g->name) != 4)
    {
        printf("Error: Invalid file format in %s\n", filename);
        fclose(file);
        free(g->name);
        for (i = 0; i < 10; i++)
        {
            free(g->pets_owned[i]);
        }
        free(g);
        return 0;
    }

    /* TODO: Initialize game attributes */
    init_game(g, g->name);

    fclose(file);
    printf("Loaded game state from slot %d\n", index);

    if (global_game != NULL)
    {
        free_game(global_game);
    }
    global_game = g;

    return 1;
}

char **get_save_files(void)
{
    DIR *dir;
    struct dirent *entry;
    int num_files = 0;
    int j;
    int start;
    int end;
    char **save_files = (char **)malloc(100 * sizeof(char *));
    if (save_files == NULL)
    {
        printf("Error: Memory allocation failed\n");
        return NULL;
    }

    /* Open the directory "save_files" */
    dir = opendir("./save_files");
    if (!dir)
    {
        printf("Error: Could not open directory\n");
        free(save_files);
        return NULL;
    }

    /* Read each entry in the directory */
    while ((entry = readdir(dir)) != NULL && num_files < 100)
    {
        /* Skip entries for the current directory and parent directory */
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
        {
            continue;
        }

        /* Allocate memory for the file name */
        save_files[num_files] = (char *)malloc((strlen(entry->d_name) + 1) * sizeof(char));
        if (save_files[num_files] == NULL)
        {
            printf("Error: Memory allocation failed\n");
            closedir(dir);
            /* Free previously allocated memory */
            for (j = 0; j < num_files; j++)
            {
                free(save_files[j]);
            }
            free(save_files);
            return NULL;
        }

        /* Copy the file name into the array */
        strcpy(save_files[num_files], entry->d_name);
        num_files++;
    }

    closedir(dir);

    /* Reverse the save_files array */
    start = 0;
    end = num_files - 1;
    while (start < end)
    {
        char *temp = save_files[start];
        save_files[start] = save_files[end];
        save_files[end] = temp;
        start++;
        end--;
    }

    return save_files;
}
