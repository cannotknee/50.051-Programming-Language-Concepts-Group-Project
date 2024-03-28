/* BEGIN: abpxx6d04wxr */
#ifndef _HAVE_STAT
#define _HAVE_STAT

#define STAT_COUNT 6
#define NAME_LENGTH 20

typedef enum {
    EGG = 0,
    BABY = 1,
    YOUNG = 2,
    ADULT = 3
} level;


typedef enum {
    DANGER_STATE = 0,
    BAD_STATE = 1,
    NORMAL_STATE = 2,
    GOOD_STATE = 3
} state;


/*Cleanliness: independent of other stats, affected by play/train/bathe
Fatigue: affected by health, affected by play/train/bathe/sleep
Hunger: independent of other stats, affected by feed
Health: affected by cleanliness, affected by medicine/vet
Happiness: affected by everything, affected by play*/
typedef enum {
    STAT_GROWTH = 0,
    STAT_HAPPINESS = 1,
    STAT_HEALTH = 2,
    STAT_CLEANLINESS = 3,
    STAT_FATIGUE = 4,
    STAT_HUNGER = 5
} stat;

/*Feed: hunger, health, fatigue
Play: happiness, health, fatigue
Bathe: happiness, health
Train: everything
Sleep: fatigue, health
Medicine: health
Vet: nothing */
typedef enum {
    ACTION_FEED,
    ACTION_PLAY,
    ACTION_BATHE,
    ACTION_TRAIN,
    ACTION_SLEEP,
    ACTION_MEDICINE,
    ACTION_VET
} action;

typedef struct lepet {
    char* name; /*Up to 20 characters*/
    stat* stat_name;
    state* stat_state; /*stat*/
    double* multiplier; /*for calculations of state transition, basically personality*/
    double* offsets; /*for update_stat, calculated based on current state of other stats*/
    int* since_last_change; /*turns since last change*/
    char* display_filename;
} pet;

/*malloc for pet attributes and init everything but name*/
void init_pet(pet* p);

/*free pet attributes and set p to nullptr*/
void free_pet(pet* p);

/*Update specified stat except growth, offset provided by other conditions such as state of other stats*/
/*return 1 if state transitioned, else 0*/
int update_stat(state* s, int since_last_change, double multiplier, float offset);

/*Look at other stats and update offsets*/
void update_offsets(pet* p);

/*Update all stats on turn end*/
/*Returns 0 by default, return 1 if pet died*/
int update_all_stats(pet* p);

/*calculate success of action and update stats accordingly*/
/*Return 0 if action failed, 1 if action succeeded, 2 if action was super successful*/
int handle_action(pet* p, action a);


#endif
