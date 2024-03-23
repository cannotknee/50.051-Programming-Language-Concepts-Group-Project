#include <stdio.h>

/*Options to display on page are not finalised yet, some options may need to be hidden depending on state of game */
/*TODO how to handle confirmation screens i.e. save completed quit?, confirm buy/sell, confirm read report. */

void display_main(){
    printf("This is the main menu page\n");
    printf("1. New Game\n");
    printf("2. Load Game\n");
    printf("0. Quit\n");
    printf("\nEnter a number to select an option: ");
}

void display_home(){
    printf("This is the home page\n");
    printf("1. Pet 1\n");
    printf("2. Pet 2\n");
    printf("3. Pet 3\n");
    printf("4. Store\n");
    printf("5. Save\n");
    printf("0. Exit\n");
    printf("\nEnter a number to select an option: ");
}

void display_store(){
    printf("This is the store page\n");
    printf("1. Buy\n");
    printf("2. Buy\n");
    printf("3. Buy\n");
    printf("0. Exit\n");
    printf("\nEnter a number to select an option: ");
}

void display_pet(){
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
