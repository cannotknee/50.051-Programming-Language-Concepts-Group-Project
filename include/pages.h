#ifndef _HAVE_PAGES
#define _HAVE_PAGES

extern int running;
extern int update_page;
extern Page curr_page;
extern char *actionresult;
extern char *statusreport;

/* Either sets curr_page to next page to be displayed or calls appropriate functions to handle input or both */
void handle_input(int input);

/* Wrapper func to display current page, calls relavent funcs, may need to pass in global variables to those funcs */
void display_page(void);

#endif