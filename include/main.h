#ifndef _HAVE_MAIN
#define _HAVE_MAIN

const int BUFFER_SIZE = 256;
const int STAT_COUNT = 6;
const int NAME_LENGTH = 20;
const double testpersonality[] = {0, 0.05, 0.05, 0.2, 0.3, 0.3};
const int MAX_ACTIONS = 3;

/* global vars */
int running = 1;     /*set to 0 to break loop and exit game*/
int update_page = 1; /*Used to indicate if the terminal should be cleared and page refreshed/updated/changed*/
int input_buffer;
char input[256];
Page curr_page = PAGE_MAIN;
game *global_game;

#endif