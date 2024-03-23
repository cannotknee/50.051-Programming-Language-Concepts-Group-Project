#ifndef _HAVE_MAIN
#define _HAVE_MAIN

#include "pages.h"

#define BUFFER_SIZE 256

/* global vars */
int running = 1; /*set to 0 to break loop and exit game*/
int update_page = 1; /*Used to indicate if the terminal should be cleared and page refreshed/updated/changed*/
int input_buffer;
char input[BUFFER_SIZE];
Page curr_page = PAGE_MAIN;

#endif