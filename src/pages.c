#include <stdio.h>

#include "pages.h"
#include "display_page.h"

void handle_input(int input){
    switch(curr_page)
    {
        case PAGE_MAIN:
            switch((MainOptions)input)
            {
                case MAIN_NEW_GAME:
                    curr_page = PAGE_HOME;
                    update_page = 1;
                    break;
                case MAIN_LOAD_GAME:
                    curr_page = PAGE_LOADGAME;
                    update_page = 1;
                    break;
                case MAIN_QUIT:
                    running = 0;
                    break;
                default:
                    printf("Invalid Input\n");
                    break;
            }
            break;
        case PAGE_HOME:
            switch(input)
            {
                case HOME_PET_1:
                    curr_page = PAGE_PET;
                    update_page = 1;
                    break;
                case HOME_PET_2:
                    curr_page = PAGE_PET;
                    update_page = 1;
                    break;
                case HOME_PET_3:
                    curr_page = PAGE_PET;
                    update_page = 1;
                    break;
                case HOME_STORE:
                    curr_page = PAGE_STORE;
                    update_page = 1;
                    break;
                case HOME_SAVE:
                    printf("Save\n");
                    break;
                case HOME_EXIT:
                    curr_page = PAGE_MAIN;
                    update_page = 1;
                    break;
                default:
                    printf("Invalid Input\n");
                    break;
            }
            break;
        case PAGE_STORE:
            switch(input)
            {
                case STORE_BUY_1:
                    printf("Buy\n");
                    break;
                case STORE_BUY_2:
                    printf("Buy\n");
                    break;
                case STORE_BUY_3:
                    printf("Buy\n");
                    break;
                case STORE_EXIT:
                    curr_page = PAGE_HOME;
                    update_page = 1;
                    break;
                default:
                    printf("Invalid Input\n");
                    break;
            }
            break;
        case PAGE_PET:
            switch(input)
            {
                case PET_FEED:
                    printf("Feed\n");
                    break;
                case PET_PLAY:
                    printf("Play\n");
                    break;
                case PET_CLEAN:
                    printf("Clean\n");
                    break;
                case PET_TRAIN:
                    printf("Train\n");
                    break;
                case PET_SLEEP:
                    printf("Sleep\n");
                    break;
                case PET_MEDICINE:
                    printf("Medicine\n");
                    break;
                case PET_SEll:
                    printf("Sell\n");
                    break;
                case PET_EXIT:
                    curr_page = PAGE_HOME;
                    update_page = 1;
                    break;
                default:
                    printf("Invalid Input\n");
                    break;
            }
            break;
        case PAGE_LOADGAME:
            switch(input)
            {
                case 0:
                    curr_page = PAGE_MAIN;
                    update_page = 1;
                    break;
                default:
                    printf("Invalid Input\n");
                    break;
            }
            break;
        default:
            printf("Invalid Input\n");
            break;
    }   
}

void display_page(){
    switch(curr_page)
    {
        case PAGE_MAIN:
            display_main();
            break;
        case PAGE_HOME:
            display_home();
            break;
        case PAGE_STORE:
            display_store();
            break;
        case PAGE_PET:
            display_pet();
            break;
        case PAGE_LOADGAME:
            display_loadgame();
            break;
        default:
            printf("B0rken Page\n");
            break;
    }
}
