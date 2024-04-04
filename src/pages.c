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
    int died;
    pet *newpet;
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
        case HOME_END_DAY:
            end_day(global_game);
            /*TODO if multiple pets are to be implemented, need a way to cycle through them and update all stats for all*/
            died = update_all_stats(global_game->pets_owned[0], actionresult, statusreport);
            if (died)
            {
                printf("Your pet has died\n");
                curr_page = PAGE_MAIN;
                update_page = 1;
                break;
            }else {
                printf("%s\n", actionresult);
                printf("%s\n", statusreport);
            }
            break;
        case HOME_EXIT:
            curr_page = PAGE_MAIN;
            update_page = 1;
            break;
        case HOME_SETTINGS:
            curr_page = PAGE_SETTINGS;
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
            /* TODO: initialize pet and store in pets_owned*/
            newpet = (pet *)malloc(sizeof(pet));
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
        /*TODO select pet, currently default pet at index 0*/
        switch (input)
        {
        case PET_FEED:
            if (global_game->part_of_day > 2) {
                printf("It is too late to do anything, wait until tomorrow\n");
                break;
            }
            handle_action(global_game->pets_owned[0], ACTION_FEED, actionresult, statusreport);
            printf("%s\n", actionresult);
            printf("%s\n", statusreport);
            update_day(global_game);
            break;
        case PET_PLAY:
            if (global_game->part_of_day > 2) {
                printf("It is too late to do anything, wait until tomorrow\n");
                break;
            }
            handle_action(global_game->pets_owned[0], ACTION_PLAY, actionresult, statusreport);
            printf("%s\n", actionresult);
            printf("%s\n", statusreport);
            update_day(global_game);
            break;
        case PET_CLEAN:
            if (global_game->part_of_day > 2) {
                printf("It is too late to do anything, wait until tomorrow\n");
                break;
            }
            handle_action(global_game->pets_owned[0], ACTION_BATHE, actionresult, statusreport);
            printf("%s\n", actionresult);
            printf("%s\n", statusreport);
            update_day(global_game);
            break;
        case PET_TRAIN:
            if (global_game->part_of_day > 2) {
                printf("It is too late to do anything, wait until tomorrow\n");
                break;
            }
            handle_action(global_game->pets_owned[0], ACTION_TRAIN, actionresult, statusreport);
            printf("%s\n", actionresult);
            printf("%s\n", statusreport);
            update_day(global_game);
            break;
        case PET_MEDICINE:
            if (global_game->part_of_day > 2) {
                printf("It is too late to do anything, wait until tomorrow\n");
                break;
            }
            if (global_game->medicine_owned > 0)
            {
                global_game->medicine_owned--;
                handle_action(global_game->pets_owned[0], ACTION_MEDICINE, actionresult, statusreport);
                printf("%s\n", actionresult);
                printf("%s\n", statusreport);
                update_day(global_game);
            }
            else
            {
                printf("No medicine!\n");
            }

            break;
        case PET_SEll:
            printf("Sell not implemented yet\n");
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
        break;
    case PAGE_CONFIRMATION:
        switch (input)
        {
        case YES:
            curr_page = PAGE_PET;
            update_day(global_game);
            update_page = 1;
            break;
        case NO:
            curr_page = PAGE_PET;
            update_page = 1;
            break;
        default:
            printf("Invalid Input\n");
            break;
        }
        break;
    case PAGE_SETTINGS:
        switch (input)
        {
        case ENABLE_DISABLE_CONFIRMATION:
            if (global_game->action_confirmation == 1)
            {
                global_game->action_confirmation = 0;
            }
            else
            {
                global_game->action_confirmation = 1;
            }
            update_page = 1;
            break;
        case EXIT:
            curr_page = PAGE_HOME;
            update_page = 1;
            break;
        default:
            printf("Invalid Input\n");
            break;
        }
        break;
    default:
        printf("Error: This shouldn't be reachable\n");
        break;
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
    case PAGE_CONFIRMATION:
        display_confirmation();
        break;
    case PAGE_SETTINGS:
        display_settings();
        break;
    default:
        printf("Broken Page\n");
        break;
    }
}
