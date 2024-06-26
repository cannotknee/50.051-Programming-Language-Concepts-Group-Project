#ifndef _HAVE_MAIN
#define _HAVE_MAIN

const int BUFFER_SIZE = 256;
const int STAT_COUNT = 5;
const int NAME_LENGTH = 255;
const int MAX_ACTIONS = 1;
const int MAX_PETS = 5;

pet *current_pet = NULL;

/*Happiness, Health, Cleanliness, Fatigue, Hunger*/
const double testpersonality[] = {0.05, 0.05, 0.2, 0.5, 0.5};

/*result messages*/
const char *action_fail_messages[] = {
    "It showed no interest in the food",
    "It did not want to play",
    "It struggled too much to bathe it",
    "It refused to listen",
    "It seemed unable to sleep well",
    "The medicine seemed to have no effect",
    "Error: This action should not fail"};

const char *action_success_messages[] = {
    "It ate the food happily",
    "It played with you",
    "It is now clean",
    "It learned something new",
    "It slept soundly",
    "It seems to be feeling better",
    "It looks a lot better after returning from the vet"};

const char *action_super_messages[] = {
    "It ate so much and looks so happy!",
    "It played with you with great enthusiasm",
    "It is now sparkling clean",
    "It learned something new and is already demonstrating it",
    "It seems like it had a nice dream",
    "Error: This action should not have super success",
    "Error: This action should not have super success"};

const char *danger_state_messages[] = {
    "Your pet is depressed. It needs more attention.",
    "Your pet is critically ill. It needs some medicine.",
    "Your pet has flesh-eating bacteria. It needs a bath.",
    "Your pet is sleep-deprived. It needs some rest.",
    "Your pet is starving. It needs some food.",
};

const char *bad_state_messages[] = {
    "Your pet is unhappy. It needs more attention.",
    "Your pet is sick. It needs some medicine.",
    "Your pet is dirty. It needs a bath.",
    "Your pet is tired. It needs some rest.",
    "Your pet is hungry. It needs some food.",
};

const char *normal_state_messages[] = {
    "Your pet is happy.",
    "Your pet is healthy.",
    "Your pet is clean.",
    "Your pet is well-rested.",
    "Your pet is well-fed.",
};

const char *good_state_messages[] = {
    "Your pet is ecstatic!",
    "Your pet is in perfect health!",
    "Your pet is sparkling clean!",
    "Your pet is well-rested and energetic!",
    "Your pet is full and satisfied!",
};

const char *meme_egg_actions[] = {
    "Feed...an egg?",
    "Don't...just don't",
    "Your egg is so shiny now",
    "Your egg learned to......sit there. Good job.",
    "Error: this should not be reachable, check meme_egg_actions",
    "That won't make it hatch any faster, this isn't lab-grown or anything",
    "The vet thanks you for the free cash"
};

/* global vars */
int running = 1;        /*set to 0 to break loop and exit game*/
int update_page = 1;    /*Used to indicate if the terminal should be cleared and page refreshed/updated/changed*/
int display_report = 0; /*Used to indicate if the status report should be displayed*/
int skip_input = 0;
int input_buffer;
char input[256];
Page curr_page = PAGE_MAIN;
game *global_game;
char *actionresult;
char *statusreport;

#endif
