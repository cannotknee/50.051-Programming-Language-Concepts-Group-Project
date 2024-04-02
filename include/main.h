#ifndef _HAVE_MAIN
#define _HAVE_MAIN

const int BUFFER_SIZE = 256;
const int STAT_COUNT = 5;
const int NAME_LENGTH = 20;
const int MAX_ACTIONS = 1;

const double testpersonality[] = {0.05, 0.05, 0.2, 0.3, 0.3};

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
    "It seems to be feeling much better",
    "Error: This action should not have super success"};

const char *danger_state_messages[] = {
    "Insert growth adult state message",
    "Insert happiness danger state message",
    "Insert health danger state message",
    "Insert cleanliness danger state message",
    "Insert fatigue danger state message",
    "Insert hunger danger state message",
};

const char *bad_state_messages[] = {
    "Insert growth young state message",
    "Insert happiness bad state message",
    "Insert health bad state message",
    "Insert cleanliness bad state message",
    "Insert fatigue bad state message",
    "Insert hunger bad state message",
};

const char *normal_state_messages[] = {
    "Insert growth baby state message",
    "Insert happiness normal state message",
    "Insert health normal state message",
    "Insert cleanliness normal state message",
    "Insert fatigue normal state message",
    "Insert hunger normal state message",
};

const char *good_state_messages[] = {
    "Insert growth egg state message",
    "Insert happiness good state message",
    "Insert health good state message",
    "Insert cleanliness good state message",
    "Insert fatigue good state message",
    "Insert hunger good state message",
};

/* global vars */
int running = 1;     /*set to 0 to break loop and exit game*/
int update_page = 1; /*Used to indicate if the terminal should be cleared and page refreshed/updated/changed*/
int input_buffer;
char input[256];
Page curr_page = PAGE_MAIN;
game *global_game;

#endif
