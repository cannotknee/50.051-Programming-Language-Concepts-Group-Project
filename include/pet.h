#ifndef _HAVE_STAT
#define _HAVE_STAT

#define STAT_COUNT 6
#define NAME_LENGTH 20

typedef enum {
    DANGER_STATE = 0,
    BAD_STATE = 1,
    NORMAL_STATE = 2,
    GOOD_STATE = 3
} state;

typedef enum {
    STAT_GROWTH = 0,
    STAT_CLEANLINESS = 1,
    STAT_FATIGUE = 2,
    STAT_HAPPINESS = 3,
    STAT_HEALTH = 4,
    STAT_HUNGER = 5
} stat;

typedef enum {
    ACTION_FEED,
    ACTION_PLAY,
    ACTION_BATHE,
    ACTION_TRAIN,
    ACTION_SLEEP,
    ACTION_MEDICINE
} action;

typedef struct lepet {
    char* name; //Up to 20 characters
    stat* stat_name;
    state* stat_state; //stat
    double* multiplier; //for calculations of state transition, basically personality
    int* since_last_change; //turns since last change
} pet;

//malloc for pet attributes and init everything but name
void init_pet(pet* p);

//free pet attributes and set p to nullptr
void free_pet(pet* p);

//Update specified stat, offset provided by other conditions such as state of other stats
void update_stat(state* s, int since_last_change, double multiplier, float offset);

//Update all stats on turn end
void update_stats(pet* p);

//calculate success of action and update stats accordingly
//Return 0 if action failed, 1 if action succeeded, 2 if action was super successful
int handle_action(pet* p, action a);


#endif
