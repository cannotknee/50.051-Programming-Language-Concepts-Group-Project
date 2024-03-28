#ifndef _HAVE_DISPLAY_PAGE
#define _HAVE_DISPLAY_PAGE

extern game *global_game;

/* Displays the main page */
void display_main(void);

/* Displays the home page */
void display_home(void);

/* Displays the store page */
void display_store(void);

/* Will probably need to take arguments to choose which pet to display, yet to figure out */
void display_pet(void);

/* Displays available games to load*/
void display_loadgame(void);

/* Displays available slots to save game*/
void display_savegame(void);

#endif
