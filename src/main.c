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
        system("clear");
        system("cls");
        if (update_page)
        {
            printf("\033[H\033[J"); /*Clear screen, might want to find a more elegant way*/
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
        printf("====================================================\n");
        printf("\nEnter a number to select an option: ");

        if (skip_input) {
            skip_input = 0;
        } else {
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

/*for testing purposes*/
int main1(int argc, char *argv[])
{
    pet *newpet = (pet *)malloc(sizeof(pet));

    init_pet(newpet);
    /*print_stats(newpet);*/
    printf("We got here yay\n");
    set_name(newpet, "TestPet");
    free(newpet);
    return 0;
}
