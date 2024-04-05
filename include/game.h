#ifndef _HAVE_GAME
#define _HAVE_GAME

#ifndef F_OK
#define F_OK 0
#endif

extern const int MAX_ACTIONS;
extern game *global_game;
extern const int NAME_LENGTH;
extern const int MAX_PETS;

/*maybe we define a directory here as a constant to use for save files?*/

/*malloc and init new game*/
void init_game(game *g, char *name);

/* update the period of the day*/
void update_day(game *g);

/*Reset the day*/
void end_day(game *g);

/*free game on exit to main menu*/
void free_game(game *g);

/*Save the player data to (player name) file in ??? directory specified in argument (to add)*/
int save_game(game *g, int index);

/* malloc and load game from file based on index */
int load_game(game *g, int index);

/* Load pets based on index */
int load_pets(game *g, int index);

/*Read directory for save files (which should be player names) to display on loadgame page*/
char **get_save_files(void);

#endif
