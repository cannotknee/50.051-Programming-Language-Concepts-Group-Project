#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/pet.h"
#include "../include/pet_display.h"

void print_image_txt(const char *filename) {
    //print each line in the file
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: File not found\n");
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);
    }
    
    fclose(file);
}

void display_curr_pet(level currlevel){
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
    print_image_txt(filename);
}

int main() {
    level curr_level = BABY;
    display_curr_pet(curr_level);
}