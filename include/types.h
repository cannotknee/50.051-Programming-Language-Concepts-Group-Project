#ifndef _HAVE_TYPES
#define _HAVE_TYPES

#define MAX_FILENAME_LENGTH 30

typedef enum
{
    PAGE_MAIN,
    PAGE_HOME,
    PAGE_STORE,
    PAGE_PET,
    PAGE_LOADGAME,
    PAGE_SAVEGAME,
    PAGE_CONFIRMATION,
    PAGE_SETTINGS
} Page;

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
    HOME_PET_4 = 4,
    HOME_PET_5 = 5,
    HOME_STORE = 6,
    HOME_SETTINGS = 7,
    HOME_SAVE = 8,
    HOME_END_DAY = 9,
    HOME_EXIT = 0
} HomeOptions;

typedef enum
{
    STORE_BUY = 1,
    STORE_BUY_MEDICINE = 2,
    STORE_EXIT = 0
} StoreOptions;

typedef enum
{
    PET_FEED = 1,
    PET_PLAY = 2,
    PET_CLEAN = 3,
    PET_TRAIN = 4,
    PET_MEDICINE = 5,
    PET_SELL = 6,
    PET_EXIT = 0
} PetOptions;

typedef enum
{
    YES = 1,
    NO = 2
} ConfirmationOptions;

typedef enum
{
    ENABLE_DISABLE_CONFIRMATION = 1,
    EXIT = 0
} SettingsOptions;

typedef enum
{
    EGG = 0,
    BABY = 1,
    YOUNG = 2,
    ADULT = 3
} level;

typedef enum
{
    DANGER_STATE = 0,
    BAD_STATE = 1,
    NORMAL_STATE = 2,
    GOOD_STATE = 3
} state;

typedef enum
{
    STAT_HAPPINESS = 0,
    STAT_HEALTH = 1,
    STAT_CLEANLINESS = 2,
    STAT_FATIGUE = 3,
    STAT_HUNGER = 4
} stat;

typedef enum
{
    ACTION_FEED = 0,
    ACTION_PLAY = 1,
    ACTION_BATHE = 2,
    ACTION_TRAIN = 3,
    ACTION_SLEEP = 4,
    ACTION_MEDICINE = 5,
    ACTION_VET = 6
} action;

typedef struct lepet
{
    char *name; /*Up to 20 characters*/
    stat *stat_name;
    state *stat_state;      /*stat*/
    double *multiplier;     /*for calculations of state transition, basically personality*/
    double *offsets;        /*for update_stat, calculated based on current state of other stats*/
    int *since_last_change; /*turns since last change*/
    char display_filename[MAX_FILENAME_LENGTH];
    level *growth;
    int *exp;
    int *value;
} pet;

typedef struct legame
{
    char *name;
    int part_of_day;
    char **period_of_day;
    int actions;
    int money;
    int medicine_owned;
    int action_confirmation; /* if action_confirmation is true, enable the confirmation page*/
    pet **pets_owned;        /* store an array of pet that the player currently owns*/
} game;

typedef struct leAdultCost{
    char *petImageName;
    int petCost;
} adultPetCost;

#endif
