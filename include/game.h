#ifndef _HAVE_GAME
#define _HAVE_GAME

extern const int MAX_ACTIONS;

typedef struct legame
{
    char *name;
    int day;
    int actions;
    int money;
    pet *pet;
} game;

/*maybe we define a directory here as a constant to use for save files?*/

/*malloc and init new game*/
void init_game(game *g, char *name);

/*free game on exit to main menu*/
void free_game(game *g);

/*Save the player data to (player name) file in ??? directory specified in argument (to add)*/
void save(game *g);

/*malloc game and Load specified file, path to add to arguments???*/
void load(game *g);

/*Read directory for save files (which should be player names) to display on loadgame page*/
char **get_save_files();

#endif