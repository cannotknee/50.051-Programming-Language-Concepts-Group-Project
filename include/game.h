#ifndef _HAVE_GAME
#define _HAVE_GAME

#ifndef F_OK
#define F_OK 0
#endif

extern const int MAX_ACTIONS;
extern game *global_game;
extern const int NAME_LENGTH;

/*maybe we define a directory here as a constant to use for save files?*/

/*malloc and init new game*/
void init_game(game *g, char *name);

/*free game on exit to main menu*/
void free_game(game *g);

/*Save the player data to (player name) file in ??? directory specified in argument (to add)*/
int save(game *g, int index);

/*malloc game and Load specified file, path to add to arguments???*/
int load(int index);

/*Read directory for save files (which should be player names) to display on loadgame page*/
char **get_save_files(void);

#endif
