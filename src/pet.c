#include <stdio.h>
#include "../include/pet.h"

void print_pet_action_menu(void) {
    printf("1. Feed the pet\n");
    printf("2. Play with the pet\n");
    printf("3. Clean the pet\n");
    printf("4. Put the pet to sleep\n");
    printf("5. Do nothing\n");
}

void input_pet_action(Pet *pet, Action action) {
    switch (action) {
        case ACTION_PLAY:
            printf("You played with the pet\n");
            pet_play(pet);
        case ACTION_FEED:
            printf("You fed the pet\n");
            pet_feed(pet);
        case ACTION_SHOWER:
            printf("You cleaned the pet\n");
            pet_shower(pet);
        case ACTION_SLEEP:
            printf("You put the pet to sleep\n");
            pet_sleep(pet);
        default:
            printf("Invalid action\n");
            break;
    }
}

void pet_play(Pet *pet) {
    if (pet->stats.energy < 5) {
        printf("Your pet is too tired to play\n");
        return;
    }
    if (pet->stats.hunger_full < 5) {
        printf("Your pet is too hungry to play\n");
        return;
    }
    if (pet->stats.hygiene < 5) {
        printf("Your pet is too dirty to play\n");
        return;
    }
    
    if (pet->stats.happiness >= MAX_HAPPINESS - 2) {
        printf("Your pet has played enough!\n");
        return;
    }

    pet->stats.happiness += 2;
    pet->stats.energy -= 5;
    pet->stats.hunger_full -= 5;
    pet->stats.hygiene -= 5;
}

void pet_feed(Pet *pet) {
    if (pet->stats.hunger_full >= ) {
        printf("Your pet is not hungry\n");
        return;
    }


    pet->stats.happiness += 2;
    pet->stats.energy += 5;
    pet->stats.hunger_full += 5;
    pet->stats.hygiene -= 5;
}

void pet_shower(Pet *pet) {
    pet->stats.happiness += 2;
    pet->stats.hygiene += 5;
}

void pet_sleep(Pet *pet) {
    pet->stats.happiness += 2;
    pet->stats.energy += 5;
    pet->stats.hunger_full -= 5;
}