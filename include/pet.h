typedef enum {
    LEVEL_BABY = 1,
    LEVEL_CHILD = 5,
    LEVEL_TEEN = 10,
    LEVEL_ADULT = 15
} Level;

typedef enum {
    MAX_LEVEL = LEVEL_ADULT,
    MAX_HAPPINESS = 30,
    MAX_ENERGY = 30,
    MAX_HUNGER_FULL = 30,
    MAX_HYGIENE = 30
} MaxStats;

typedef enum {
    MOOD_HAPPY,
    MOOD_SAD,
    MOOD_ANGRY,
    MOOD_SLEEPY
} Mood;

typedef struct {
    int curr_level; // EXP Level
    float happiness; // Play+, Food+, Shower+
    float energy; // Sleep+, Food+, Play-
    float hunger_full; // Food+, Play-, Sleep-
    float hygiene; // Shower+, Play-, Food-
} PetStats;

typedef struct {
    char name[20];
    Mood mood;
    PetStats stats;
} Pet;

typedef enum {
    ACTION_PLAY,
    ACTION_FEED,
    ACTION_SHOWER,
    ACTION_SLEEP
} Action;

void print_pet_action_menu(void);
// void pet_init(Pet *pet, const char *name);
// void pet_update(Pet *pet, Action action);
// void pet_print(const Pet *pet);
// void pet_action(Pet *pet, Action action);