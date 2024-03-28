#ifndef _HAVE_DISPLAY_PAGE
#define _HAVE_DISPLAY_PAGE

#define IMAGE_FILE_DIR "../images/"
#define EGG_STAGE_FILE "egg_display"
#define NUM_EGG_STAGE_FILES 1
#define BABY_STAGE_FILE "baby_display"
#define NUM_BABY_STAGE_FILES 3
#define YOUNG_STAGE_FILE "young_display"
#define NUM_YOUNG_STAGE_FILES 3
#define ADULT_STAGE_FILE "adult_display"
#define NUM_ADULT_STAGE_FILES 5

extern game *global_game;

/* Displays the main page */
void display_main(void);

/* Displays the home page */
void display_home(void);

/* Displays the store page */
void display_store(void);

/* Will probably need to take arguments to choose which pet to display, yet to figure out */
void display_pet_menu(void);

/* Displays available games to load*/
void display_loadgame(void);
/* Display pet image */
void display_pet_image(pet *p);

/* Upgrade pet image on level up */
void randomize_pet_display(pet *p, level currlevel);
/* Displays available slots to save game*/
void display_savegame(void);

#endif
