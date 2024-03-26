#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "main.h"
#include "pages.h"

int main (int argc, char *argv[]) {

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