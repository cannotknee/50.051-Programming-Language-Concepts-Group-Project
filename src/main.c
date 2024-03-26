#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "main.h"
#include "pages.h"

#include "pet.h"

int main123 (int argc, char *argv[]) {

    while (running)
    {
        if (update_page) {
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
int main (int argc, char *argv[]){
    pet* p;
    int i;
    p = (pet*)malloc(sizeof(pet));
    init_pet(p);
    set_name(p, "TestPet");
    set_personality(p);

    for (i = 0; i < 10; i++) {
        update_all_stats(p);
        print_stats(p);
        print_since_last_change(p);
    }

    free_pet(p);
    return 0;
}