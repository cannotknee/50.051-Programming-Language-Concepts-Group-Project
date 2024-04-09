#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
            display_invalid_input();
            break;
        }
        break;
    case PAGE_HOME:
        switch (input)
        {
        case HOME_PET_1:
            current_pet = global_game->pets_owned[0];
            if (!pet_exist(current_pet))
            {
                update_page = 1;
                break;
            }
            curr_page = PAGE_PET;
            update_page = 1;
            break;
        case HOME_PET_2:
            current_pet = global_game->pets_owned[1];
            if (!pet_exist(current_pet))
            {
                update_page = 1;
                break;
            }
            curr_page = PAGE_PET;
            update_page = 1;
            break;
        case HOME_PET_3:
            current_pet = global_game->pets_owned[2];
            if (!pet_exist(current_pet))
            {
                update_page = 1;
                break;
            }
            curr_page = PAGE_PET;
            update_page = 1;
            break;
        case HOME_PET_4:
            current_pet = global_game->pets_owned[3];
            if (!pet_exist(current_pet))
            {
                update_page = 1;
                break;
            }
            curr_page = PAGE_PET;
            update_page = 1;
            break;
        case HOME_PET_5:
            current_pet = global_game->pets_owned[4];
            if (!pet_exist(current_pet))
            {
                update_page = 1;
                break;
            }
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
            /*TODO Death/game over function*/
            /*TODO daily report thingy for all pets instead of just last pet*/
            for (i = 0; i < MAX_PETS; i++)
            {
                if (global_game->pets_owned[i] != NULL)
                {
                    died = update_all_stats(global_game->pets_owned[i], actionresult, statusreport);
                    if (died)
                    {
                        global_game->pets_owned[i] = NULL;
                    }
                }
            }
            update_page = 1;
            display_report = 1;
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
            display_invalid_input();
            break;
        }
        break;
    case PAGE_STORE:
        switch (input)
        {
        case STORE_BUY_1:
            /* TODO: initialize pet and store in pets_owned*/
            if (global_game->money >= 50)
            {
                global_game->money -= 50;
                
                for (i = 0; i < MAX_PETS; i++)
                {   
                    if (global_game->pets_owned[i] == NULL)
                    {   
                        char pet_name[50];
                        newpet = (pet *)malloc(sizeof(pet));
                        init_pet(newpet);
                        set_personality(newpet);
                        printf("Enter a name for your pet: ");
                        scanf("%s", pet_name);
                        set_name(newpet, pet_name);

                        global_game->pets_owned[i] = newpet;
                        update_page = 1;

                        strcpy(actionresult, "You have successfully bought a new pet egg!");
                        strcpy(statusreport, "Now just to wait for it to hatch");
                        display_report = 1;
                        free(newpet);

                        skip_input = 1;
                        input_buffer = STORE_EXIT;
                        break;
                    }
                }
                strcpy(actionresult, "You have too many pets");
                strcpy(statusreport, "You can oly have 5 pets at a time");
                display_report = 1;
            }
            else
            {
                strcpy(actionresult, "Not enough money");
                strcpy(statusreport, "Lowly peasant");
                display_report = 1;
            }
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
                strcpy(actionresult, "Not enough money");
                strcpy(statusreport, "Lowly peasant");
                display_report = 1;
            }

            break;
        case STORE_EXIT:
            curr_page = PAGE_HOME;
            update_page = 1;
            break;
        default:
            display_invalid_input();
            break;
        }
        break;
    case PAGE_PET:

        if (day_check() && input != PET_EXIT)
        {
            break;
        }
        /*TODO select pet, currently default pet at index 0*/
        switch (input)
        {
        case PET_FEED:
            generic_action(current_pet, ACTION_FEED);
            break;
        case PET_PLAY:
            generic_action(current_pet, ACTION_PLAY);
            break;
        case PET_CLEAN:
            generic_action(current_pet, ACTION_BATHE);
            break;
        case PET_TRAIN:
            generic_action(current_pet, ACTION_TRAIN);
            break;
        case PET_MEDICINE:
            if (global_game->medicine_owned > 0)
            {
                global_game->medicine_owned--;
                generic_action(current_pet, ACTION_MEDICINE);
            }
            else
            {
                strcpy(actionresult, "No Medicine");
                strcpy(statusreport, "Go buy some in the store");
                display_report = 1;
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
            display_invalid_input();
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
            global_game = (game *)malloc(sizeof(game));
            if (
                load_game(global_game, input))
            {
                curr_page = PAGE_HOME;
                update_page = 1;
            }
            else
            {
                display_invalid_input();
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
            if (save_game(global_game, input))
            {
                printf("Save Successful\n");
                printf("Enter 0 to return to home\n");
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
            display_invalid_input();
            printf("File is corrupted\n");
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
            display_invalid_input();
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
        display_pet_menu(current_pet);
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

int day_check(void)
{
    if (global_game->part_of_day > 2)
    {
        strcpy(actionresult, "It is too late to do anything, wait until tomorrow");
        update_page = 1;
        display_report = 1;
        return 1;
    }
    return 0;
}

void generic_action(pet *p, action action)
{
    handle_action(p, action, actionresult, statusreport);
    update_day(global_game);
    update_page = 1;
    display_report = 1;
}

int pet_exist(pet *p)
{
    if (p == NULL)
    {
        strcpy(actionresult, "No pet to perform action on");
        strcpy(statusreport, "Go buy one in the store");
        display_report = 1;
        return 0;
    }
    else
    {
        return 1;
    }
}

void display_invalid_input(void)
{
    strcpy(actionresult, "Invalid Input");
    strcpy(statusreport, "Please key in one of the available options");
    display_report = 1;
    update_page = 1;
}
