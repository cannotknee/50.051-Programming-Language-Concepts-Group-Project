#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>

#include "types.h"
#include "game.h"
#include "pet.h"

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
    g->pets_owned = (pet **)malloc(MAX_PETS * sizeof(pet *));
    for (i = 0; i < MAX_PETS; i++)
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

void end_day(game *g)
{
    g->part_of_day = 0;
}

void free_game(game *g)
{
    int i;
    /*To check for any pet pointers and free them if necessary*/
    for (i = 0; i < MAX_PETS; i++)
    {
        free(g->pets_owned[i]);
    }
    free(g->period_of_day);
    free(g->name);
    free(g);
}

int save_game(game *g, int index)
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
        printf("A saved game already exists in slot %d. Do you want to overwrite it? (Y/n): ", index);
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

    /* Write game state to save file */
    fprintf(file, "%s,%d,%d,%d,%d,%d\n", g->name, g->part_of_day, g->actions, g->money, g->medicine_owned, g->action_confirmation);

    if (save_pets(g, index) == 0)
    {
        printf("Error: Could not save pets to file %s\n", filename);
        fclose(file);
        return 0;
    }

    fclose(file);
    printf("Game saved successfully to slot %d.\n", index);
    return 1;
}

int save_pets(game *g, int index)
{
    char filename[50];
    FILE *file;
    int i;

    /* Construct filename based on the slot index */
    sprintf(filename, "save_files/save%d.csv", index);

    /* Open the file for writing */
    file = fopen(filename, "w");
    if (file == NULL)
    {
        printf("Error: Could not create save file %s\n", filename);
        return 0;
    }

    /* Write game state to save file */
    fprintf(file, "%s,%d,%d,%d,%d,%d\n", g->name, g->part_of_day, g->actions, g->money, g->medicine_owned, g->action_confirmation);

    /* Write pet data to save file */
    for (i = 0; i < MAX_PETS; i++)
    {
        if (g->pets_owned[i] != NULL)
        {
            fprintf(file, "%s,%d,%d,%d,%d,%d,%lf,%lf,%d,%s,%d,%d,%d\n", g->pets_owned[i]->name,
                    g->pets_owned[i]->stat_name[0], g->pets_owned[i]->stat_name[1],
                    g->pets_owned[i]->stat_name[2], g->pets_owned[i]->stat_name[3],
                    g->pets_owned[i]->stat_name[4], *g->pets_owned[i]->multiplier,
                    *g->pets_owned[i]->offsets, *g->pets_owned[i]->since_last_change,
                    g->pets_owned[i]->display_filename, *g->pets_owned[i]->growth,
                    *g->pets_owned[i]->exp, *g->pets_owned[i]->value);
        }
    }

    fclose(file);
    return 1;
}

int load_game(game *g, int input)
{
    char filename[50];
    FILE *file;

    /* Check if the slot is within valid range (1 to 3) */
    if (input < 1 || input > 3)
    {
        printf("Invalid slot index. Slot index must be between 1 and 3.\n");
        return 0;
    }

    if (g == NULL)
    {
        printf("Critical error: Game not initialised. Please restart.\n");
        return 0;
    }

    /* Construct filename based on the slot index */
    sprintf(filename, "save_files/save%d.csv", input);

    /* Open the file for reading */
    file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Error: Could not open file %s\n", filename);
        return 0;
    }

    /* Initialize game attributes */
    init_game(g, "This is as big as a filename can be"); // Pass maximum length of name

    /* Read data from the file and populate the game structure */
    if (fscanf(file, "%[^,],%d,%d,%d,%d,%d\n", g->name, &g->part_of_day, &g->actions, &g->money, &g->medicine_owned, &g->action_confirmation) != 6)
    {
        printf("Error: Invalid data format in file %s\n", filename);
        fclose(file);
        free(g);
        return 0;
    }

    if (load_pets(g, input) == 0)
    {
        printf("Error: Could not load pets from file %s\n", filename);
        fclose(file);
        free(g);
        return 0;
    }

    fclose(file);
    return 1;
}

int load_pets(game *g, int input)
{
    char filename[50], line[100];
    FILE *file;
    int num_pets = 0; // Start counting from 0

    /* Construct filename based on the slot index */
    sprintf(filename, "save_files/save%d.csv", input);

    /* Open the file for reading */
    file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Error: Could not open file %s\n", filename);
        return 0;
    }

    // Skip the first line
    if (fgets(line, sizeof(line), file) == NULL)
    {
        printf("Error: Could not read first line from file %s\n", filename);
        fclose(file);
        return 0;
    }

    while (fgets(line, sizeof(line), file) != NULL)
    {
        // Allocate memory for the pet
        g->pets_owned[num_pets] = (pet *)malloc(sizeof(pet));
        if (g->pets_owned[num_pets] == NULL)
        {
            printf("Error: Memory allocation failed\n");
            fclose(file);
            return 0;
        }
        // Initialize the pet
        init_pet(g->pets_owned[num_pets]);

        // Read attributes from the line
        if (sscanf(line, "%[^,],%d,%d,%d,%d,%d,%lf,%lf,%d,%[^,],%d,%d,%d\n", g->pets_owned[num_pets]->name,
                   &g->pets_owned[num_pets]->stat_name[0], &g->pets_owned[num_pets]->stat_name[1],
                   &g->pets_owned[num_pets]->stat_name[2], &g->pets_owned[num_pets]->stat_name[3],
                   &g->pets_owned[num_pets]->stat_name[4], &(*g->pets_owned[num_pets]->multiplier),
                   &(*g->pets_owned[num_pets]->offsets), &(*g->pets_owned[num_pets]->since_last_change),
                   g->pets_owned[num_pets]->display_filename, &(*g->pets_owned[num_pets]->growth),
                   &(*g->pets_owned[num_pets]->exp), &(*g->pets_owned[num_pets]->value)) != 13)
        {
            printf("Error: Invalid data format in file %s\n", filename);
            fclose(file);
            return 0;
        }

        // Increment the number of pets
        num_pets++;
    }

    fclose(file);
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
    while ((entry = readdir(dir)) != NULL && num_files < 4)
    {
        /* Skip entries for the current directory, parent directory & child directory */
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
        {
            continue;
        }

        /* Allocate memory for the game name */
        save_files[num_files] = (char *)malloc(strlen(entry->d_name) + 1);
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
