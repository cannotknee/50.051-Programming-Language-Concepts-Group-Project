#include <stdio.h>

#include "display_page.h"
#include "../include/pet.h"

/*Options to display on page are not finalised yet, some options may need to be hidden depending on state of game */
/*TODO how to handle confirmation screens i.e. save completed quit?, confirm buy/sell, confirm read report. */

void display_main(void){
    printf("This is the main menu page\n");
    printf("1. New Game\n");
    printf("2. Load Game\n");
    printf("0. Quit\n");
    printf("\nEnter a number to select an option: ");
}

void display_home(void){
    printf("This is the home page\n");
    printf("1. Pet 1\n");
    printf("2. Pet 2\n");
    printf("3. Pet 3\n");
    printf("4. Store\n");
    printf("5. Save\n");
    printf("0. Exit\n");
    printf("\nEnter a number to select an option: ");
}

void display_store(void){
    printf("This is the store page\n");
    printf("1. Buy\n");
    printf("2. Buy\n");
    printf("3. Buy\n");
    printf("0. Exit\n");
    printf("\nEnter a number to select an option: ");
}

void display_pet_menu(void){
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

void display_loadgame(void) {
    printf("This is the load game page\n");
    printf("Nothing to see here\n");
    printf("0. Exit\n");
}

// display pet image from file
void display_pet_image(pet *p) {
    FILE *file = fopen(p->display_filename, "r");
    if (file == NULL) {
        printf("Error: File not found\n");
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);
    }
    
    fclose(file);
}

// randomize pet display image on level change
void randomize_pet_display(pet *p, level currlevel){
    char filename[256]; // Assuming a maximum filename length of 20 characters
    if (currlevel == EGG) {
        int rand_int = (rand() % NUM_EGG_STAGE_FILES) + 1;
        sprintf(filename, "image/%s_%d.txt", EGG_STAGE_FILE, rand_int);
    }
    else if (currlevel == BABY)
    {
        int rand_int = (rand() % NUM_BABY_STAGE_FILES) + 1;
        sprintf(filename, "image/%s_%d.txt", BABY_STAGE_FILE, rand_int);
    }
    else if (currlevel == YOUNG)
    {
        int rand_int = (rand() % NUM_YOUNG_STAGE_FILES) + 1;
        sprintf(filename, "image/%s_%d.txt", YOUNG_STAGE_FILE, rand_int);
    }
    else if (currlevel == ADULT)
    {
        int rand_int = (rand() % NUM_ADULT_STAGE_FILES) + 1;
        sprintf(filename, "image/%s_%d.txt", ADULT_STAGE_FILE, rand_int);
    }
    else {
        printf("Error: Invalid level\n");
        return;
    }

    printf("Displaying pet image: %s\n", filename);
    display_pet_image(filename);
    p -> display_filename = filename;
}