#ifndef _HAVE_PET
#define _HAVE_PET

extern const int STAT_COUNT;
extern const int NAME_LENGTH;
extern const double testpersonality[];
/*result messages*/
extern const char *action_fail_messages[];

extern const char *action_success_messages[];

extern const char *action_super_messages[];

extern const char *danger_state_messages[];

extern const char *bad_state_messages[];

extern const char *normal_state_messages[];

extern const char *good_state_messages[];

/*malloc for pet attributes and init everything but name*/
void init_pet(pet *p);

/*free pet attributes and set p to nullptr*/
void free_pet(pet *p);

/*Set name of pet*/
void set_name(pet *p, char *name);

/*Chooses random personality template, TO DO currently only uses test template*/
void set_personality(pet *p);

/*Set multipliers based on personality template, to be used by choose_personality*/
void set_multipliers(pet *p, const double *personality);

/*Update specified stat except growth, offset provided by other conditions such as state of other stats*/
/*return 1 if state transitioned, else 0*/
int update_stat(state *s, int since_last_change, double multiplier, float offset);

/*Look at other stats and update offsets*/
void update_offsets(pet *p);

/*Update all stats on turn end*/
/*also handles updating the since_last_change attribute*/
/*Returns 0 by default, return 1 if pet died*/
int update_all_stats(pet *p);

/*Calculate chances for super success*/
double calc_action_super_chance(pet *p, action a);

/*calculate chances for failed action*/
double calc_action_fail_chance(pet *p, action a);

/*calculate success of action and update stats accordingly*/
/*Return 0 if action failed, 1 if action succeeded, 2 if action was super successful*/
int calc_action(pet *p, action a);

/*Generate report of action and store it in provided result ptr*/
void report_result(pet *p, action a, int success, char *actionresult, char *statusreport);

/*Calculates success of action and updates the state and result*/
void handle_action(pet *p, action a, int success, char *actionresult, char *statusreport);

/*test funcs*/
void reset_pet(pet *p);
void print_stats(pet *p);
void print_multipliers(pet *p);
void print_offsets(pet *p);
void print_since_last_change(pet *p);

#endif
