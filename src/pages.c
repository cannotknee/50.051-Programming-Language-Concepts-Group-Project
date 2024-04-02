#include <stdio.h>
#include <stdlib.h>

#include "types.h"
#include "pages.h"
#include "display_page.h"
#include "pet.h"
#include "game.h"

void handle_input(int input)
{
    int i;
    pet *newpet = NULL;
    switch (curr_page)
    {
    case PAGE_MAIN:
        switch ((MainOptions)input)
        {
        case MAIN_NEW_GAME:
            curr_page = PAGE_HOME;
            global_game = (game *)malloc(sizeof(game));
            init_game(global_game, "TestGame");

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
        switch (input)
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
            curr_page = PAGE_SAVEGAME;
            update_page = 1;
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
        switch (input)
        {
        case STORE_BUY_1:
            printf("Buy\n");
            /* TODO: initialize pet and store in pets_owned*/
            init_pet(newpet);
            set_name(newpet, "Pikachu");
            set_personality(newpet);

            if (global_game->money >= 50)
            {
                global_game->money -= 50;
                for (i = 0; i < 10; i++)
                {
                    if (global_game->pets_owned[i] == NULL)
                    {
                        global_game->pets_owned[i] = newpet;
                        update_page = 1;
                        break;
                    }
                }
            }
            else
            {
                printf("Not enough money!\n");
            }

            break;
        case STORE_BUY_2:
            printf("Buy\n");
            break;
        case STORE_BUY_3:
            printf("Buy\n");
            break;
        case STORE_BUY_MEDICINE:
            /* if there is enough money, purchase medicine*/
            if (global_game->money >= 10)
            {
                global_game->money -= 10;
                global_game->medicine_owned++;
                update_page = 1;
            }
            else
            {
                printf("Not enough money!\n");
            }

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
        switch (input)
        {
        case PET_FEED:
            printf("Feed\n");
            break;
        case PET_PLAY:
            printf("Play\n");
            update_day(global_game);
            update_page = 1;
            break;
        case PET_CLEAN:
            printf("Clean\n");
            update_day(global_game);
            update_page = 1;
            break;
        case PET_TRAIN:
            printf("Train\n");
            update_day(global_game);
            update_page = 1;
            break;
        case PET_SLEEP:
            printf("Sleep\n");
            break;
        case PET_MEDICINE:
            if (global_game->medicine_owned > 0)
            {
                global_game->medicine_owned--;
                update_page = 1;
            }
            else
            {
                printf("No medicine!\n");
            }

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
        switch (input)
        {
        case 0:
            curr_page = PAGE_MAIN;
            update_page = 1;
            break;
        default:
            if (
                load(input))
            {
                curr_page = PAGE_HOME;
                update_page = 1;
            }
            else
            {
                printf("Invalid Input\n");
            }
            break;
        }
        break;
    case PAGE_SAVEGAME:
        switch (input)
        {
        case 0:
            curr_page = PAGE_HOME;
            update_page = 1;
            break;
        default:
            if (save(global_game, input))
            {
                printf("Save Successful\n");
                curr_page = PAGE_HOME;
                update_page = 1;
            }
            break;
        }
    }
}

void display_page(void)
{
    switch (curr_page)
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
        display_pet_menu();
        break;
    case PAGE_LOADGAME:
        display_loadgame();
        break;
    case PAGE_SAVEGAME:
        display_savegame();
        break;
    default:
        printf("B0rken Page\n");
        break;
    }
}
