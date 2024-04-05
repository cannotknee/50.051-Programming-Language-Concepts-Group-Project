#ifndef _HAVE_PAGES
#define _HAVE_PAGES

extern int running;
extern int update_page;
extern int display_report;
extern Page curr_page;
extern char *actionresult;
extern char *statusreport;

/* Either sets curr_page to next page to be displayed or calls appropriate functions to handle input or both */
void handle_input(int input);

/* Wrapper func to display current page, calls relavent funcs, may need to pass in global variables to those funcs */
void display_page(void);

/*Simple check for if any actions left in the day, returns 1 and sets up report if no actions left*/
int day_check(void);

/*Wrapper func for handling actions on pet page*/
void generic_action(pet *p, action action);

/* check if current pet exist*/
int pet_exist(pet *p);

/* display message on screen when players give an invalid input*/
void display_invalid_input(void);

#endif
