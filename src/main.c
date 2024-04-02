#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "types.h"
#include "pages.h"
#include "pet.h"
#include "main.h"

int main1(int argc, char *argv[])
{
    actionresult = (char *)malloc(255 * sizeof(char));
    statusreport = (char *)malloc(255 * sizeof(char));

    while (running)
    {
        if (update_page)
        {
            printf("\033[H\033[J"); /*Clear screen, might want to find a more elegant way*/
            display_page();
            update_page = 0;
        }

        fgets(input, BUFFER_SIZE, stdin);
        sscanf(input, "%d", &input_buffer);

        handle_input(input_buffer);
    }

    free(actionresult);
    free(statusreport);
    printf("Goodbye\n");

    exit(0);
}

/*for testing purposes*/
int main(int argc, char *argv[])
{
    pet *newpet;
    init_pet(newpet);
    print_stats(newpet);
    printf("We got here yay\n");
    set_name(newpet, "TestPet");
    return 0;
}
