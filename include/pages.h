#ifndef _HAVE_PAGES
#define _HAVE_PAGES

typedef enum
{
    PAGE_MAIN,
    PAGE_HOME,
    PAGE_STORE,
    PAGE_PET,
    PAGE_LOADGAME
} Page;
/*Confirmation page where*/

typedef enum
{
    MAIN_NEW_GAME = 1,
    MAIN_LOAD_GAME = 2,
    MAIN_QUIT = 0
} MainOptions;

typedef enum
{
    HOME_PET_1 = 1,
    HOME_PET_2 = 2,
    HOME_PET_3 = 3,
    HOME_STORE = 4,
    HOME_SAVE = 5,
    HOME_EXIT = 0
} HomeOptions;

typedef enum
{
    STORE_BUY_1 = 1, /*temp*/
    STORE_BUY_2 = 2, /*temp*/
    STORE_BUY_3 = 3, /*temp*/
    STORE_EXIT = 0
} StoreOptions;

typedef enum
{
    PET_FEED = 1,
    PET_PLAY = 2,
    PET_CLEAN = 3,
    PET_TRAIN = 4,
    PET_SLEEP = 5,
    PET_MEDICINE = 6,
    PET_SEll = 7,
    PET_EXIT = 0
} PetOptions;

extern int running;
extern int update_page;
extern Page curr_page;

/* Either sets curr_page to next page to be displayed or calls appropriate functions to handle input or both */
void handle_input(int input);

/* Wrapper func to display current page, calls relavent funcs, may need to pass in global variables to those funcs */
void display_page();

#endif
