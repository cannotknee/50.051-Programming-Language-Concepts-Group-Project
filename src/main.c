#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "types.h"
#include "pages.h"
#include "pet.h"
#include "main.h"

int main(int argc, char *argv[])
{
    actionresult = (char *)malloc(255 * sizeof(char));
    statusreport = (char *)malloc(255 * sizeof(char));

    while (running)
    {
        #ifdef _WIN32 
            system("cls");
        #elif __APPLE__ 
            system("clear");
        #elif __linux__ 
            system("clear");
        #endif 
        
        if (update_page)
        {
            display_page();
            update_page = 0;
        }
        if(display_report)
        {
            printf("====================================================\n");
            printf("%s\n", actionresult);
            printf("%s\n", statusreport);
            display_report = 0;
        }

        if (skip_input) {
            skip_input = 0;
        } else {
            printf("====================================================\n");
            printf("\nEnter a number to select an option: \n");
            fgets(input, BUFFER_SIZE, stdin);
            sscanf(input, "%d", &input_buffer);

            handle_input(input_buffer);
        }
    }

    free(actionresult);
    free(statusreport);
    printf("Goodbye\n");

    exit(0);
}
