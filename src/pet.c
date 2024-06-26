#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "types.h"
#include "pet.h"
#include "display_page.h"

void init_pet(pet *p)
{
    int i;
    p->name = (char *)malloc(NAME_LENGTH * sizeof(char));
    p->stat_name = (stat *)malloc(STAT_COUNT * sizeof(stat));
    p->stat_state = (state *)malloc(STAT_COUNT * sizeof(state));
    p->multiplier = (double *)malloc(STAT_COUNT * sizeof(double));
    p->offsets = (double *)malloc(STAT_COUNT * sizeof(double));
    p->since_last_change = (int *)malloc(STAT_COUNT * sizeof(int));
    for (i = 0; i < STAT_COUNT; i++)
    {
        p->stat_name[i] = (stat)i;
        p->stat_state[i] = NORMAL_STATE;
        p->multiplier[i] = 0.1; /*Currently just set all to 0.1, will need to somehow randomise this or use template in future*/
        p->offsets[i] = 0;
        p->since_last_change[i] = 0;
    }
    p->growth = (level *)malloc(sizeof(level));
    p->exp = (int *)malloc(sizeof(int));
    p->value = (int *)malloc(sizeof(int));
    *p->growth = EGG;
    randomize_pet_display(p, *p->growth);
}

void set_name(pet *p, char *name)
{
    strcpy(p->name, name);
}

void set_personality(pet *p)
{
    /*TODO introduce random choice and more templates, currently only using 1 test template*/
    set_multipliers(p, testpersonality);
    /*TODO include value in personality, easy, medium hard???*/
    *p->value = 10;
}

void set_multipliers(pet *p, const double *template)
{
    int i;
    for (i = 0; i < STAT_COUNT; i++)
    {
        p->multiplier[i] = template[i];
    }
}

void free_pet(pet *p)
{
    free(p->name);
    free(p->stat_name);
    free(p->stat_state);
    free(p->multiplier);
    free(p->since_last_change);
    free(p->offsets);
    free(p->growth);
    free(p->exp);
    free(p->value);
    p = NULL;
}

int update_stat(state *s, int since_last_change, double multiplier, float offset)
{
    double randval;
    randval = (double)rand() / RAND_MAX; /*Rand val btwn 0 & 1*/
    if (randval < since_last_change * multiplier + offset && *s > 0)
    {
        *s = *s - 1;
        return 1;
    }
    return 0;
    /*Danger state will be handled in wrapper func update_all_stats*/
}

void update_offsets(pet *p)
{
    /*TODO any -1 offset due to GOOD_STATEs*/
    int i;
    int x = 0;
    p->offsets[STAT_FATIGUE] = 0.2 * (int)(NORMAL_STATE - p->stat_state[STAT_HEALTH]);
    p->offsets[STAT_HEALTH] = 0.1 * (int)(NORMAL_STATE - p->stat_state[STAT_CLEANLINESS]);
    p->offsets[STAT_HAPPINESS] = 0.0;
    /*Check stats other than happiness*/
    for (i = 1; i < STAT_COUNT; i++)
    {
        /*If any danger state increase happiness transition chance by 30%*/
        if (p->stat_state[i] == DANGER_STATE)
        {
            p->offsets[STAT_HAPPINESS] += 0.3;
        }
        x += p->stat_state[i];
    }
    /*Increase transition chance by 10% if total of other stats is less than 6, 2 bad or 1 danger + 1 bad*/
    if (x < 6)
    {
        p->offsets[STAT_HAPPINESS] += 0.1;
    }
}

int update_all_stats(pet *p, char *actionresult, char *statusreport)
{
    /*Stat update*/
    int i;
    int updated;
    /*Scuff since if doesnt seem to work? and don't want this whole chunk twice in the growth update section*/
    switch (*p->growth){
        case EGG:
            break;
        case ADULT:
            break;
        default:
            for (i = 0; i < STAT_COUNT; i++)
            {
                if (p->stat_state[i] == DANGER_STATE)
                {
                    /*pet dies if left in danger state for more than 2 turns*/
                    if (p->since_last_change[i] > 1)
                    {
                        return 1;
                    }
                    p->since_last_change[i]++;
                }
                else if (p->stat_name[i] == STAT_FATIGUE)
                {
                    handle_action(p, ACTION_SLEEP, actionresult, statusreport);
                }

                else
                {
                    updated = update_stat(&p->stat_state[i], p->since_last_change[i], p->multiplier[i], p->offsets[i]);
                    if (updated)
                    {
                        p->since_last_change[i] = 0;
                    }
                    else
                    {
                        p->since_last_change[i]++;
                    }
                }
            }
            update_offsets(p);
    }

    *p->exp += 1;
    switch (*p->growth)
    {
    case EGG:
        strcpy(actionresult, "Your pet had a good night's sleep...I think? It's an egg, does it sleep?");
        strcpy(statusreport, "The egg sits there, menacingly...");
        if (*p->exp > 3)
        {
            *p->growth = BABY;
            randomize_pet_display(p, *p->growth);
            *p->exp -= 3;
            strcpy(statusreport, "Your pet has hatched from its egg!");
        }
        break;
    case BABY:
        if (*p->exp > 15)
        {
            *p->growth = YOUNG;
            randomize_pet_display(p, *p->growth);
            *p->exp -= 15;
            strcpy(statusreport, "Your pet has grown bigger!");
        }
        break;
    case YOUNG:
        if (*p->exp > 40)
        {
            *p->growth = ADULT;
            randomize_pet_display(p, *p->growth);
            *p->exp -= 40;
            strcpy(statusreport, "Your pet has grown too beeg! It needs a new home now");
        }
        break;
    case ADULT:
        strcpy(actionresult, "Your pet is all grown up now!");
        strcpy(statusreport, "Sell it off for some quick bucks!");
        break;
    default:
        break;
    }
    
    return 0;
}

double calc_action_super_chance(pet *p, action a)
{
    int i;
    double chance = 0;
    switch (a)
    {
    case ACTION_FEED:
        chance = 0.1;
        break;
    case ACTION_PLAY:
        chance = 0.1;
        break;
    case ACTION_BATHE:
        chance = 0.3;
        break;
    case ACTION_TRAIN:
        for (i = 0; i < STAT_COUNT; i++)
        {
            if (p->stat_state[i] == GOOD_STATE)
            {
                chance += 0.3;
            }
        }
        break;
    case ACTION_SLEEP:
        chance = 0.1;
        break;
    case ACTION_MEDICINE:
        break;
    case ACTION_VET:
        break;
    default:
        break;
    }
    return chance;
}

double calc_action_fail_chance(pet *p, action a)
{
    int i;
    double chance = 0;
    switch (a)
    {
    case ACTION_FEED:
        if (p->stat_state[STAT_HUNGER] > BAD_STATE)
        {
            chance = 1;
        }
        else
        {
            chance += 0.3 * (int)(NORMAL_STATE - p->stat_state[STAT_HEALTH]);
            chance += 0.3 * (int)(NORMAL_STATE - p->stat_state[STAT_FATIGUE]);
        }
        break;
    case ACTION_PLAY:
        chance += 0.5 * (int)(NORMAL_STATE - p->stat_state[STAT_HEALTH]);
        chance += 0.5 * (int)(NORMAL_STATE - p->stat_state[STAT_FATIGUE]);
        break;
    case ACTION_BATHE:
        chance += 0.3 * (int)(NORMAL_STATE - p->stat_state[STAT_HEALTH]);
        chance += 0.1 * (int)(NORMAL_STATE - p->stat_state[STAT_HAPPINESS]);
        break;
    case ACTION_TRAIN:
        for (i = 0; i < STAT_COUNT; i++)
        {
            if (p->stat_state[i] == DANGER_STATE)
            {
                chance = 1;
                break;
            }
            else
            {
                chance += 0.2 * (int)(NORMAL_STATE - p->stat_state[i]);
            }
        }
        break;
    case ACTION_SLEEP:
        chance += 0.3 * (int)(NORMAL_STATE - p->stat_state[STAT_HEALTH]);
        break;
    case ACTION_MEDICINE:
        if (p->stat_state[STAT_HEALTH] == BAD_STATE)
        {
            chance = 0.3;
        }
        else if (p->stat_state[STAT_HEALTH] == DANGER_STATE)
        {
            chance = 0.8;
        }
        else
        {
            chance = 1;
        }
        break;
    case ACTION_VET:
        break;
    default:
        break;
    }
    return chance;
}

int calc_action(pet *p, action a)
{

    double randval;
    double failchance;
    double superchance;

    randval = rand() / RAND_MAX; /*Rand val btwn 0 & 1*/
    failchance = calc_action_fail_chance(p, a);
    superchance = calc_action_super_chance(p, a);
    if (randval < failchance)
    {
        return 0;
    }
    else if (randval < superchance)
    {
        return 2;
    }
    else
    {
        return 1;
    }
}

void report_result(pet *p, action a, int success, char *actionresult, char *statusreport)
{
    int i;
    int randval;
    int badcount;
    state badlist[10];

    switch (success)
    {
    case 0:
        strcpy(actionresult, action_fail_messages[a]);
        break;
    case 1:
        strcpy(actionresult, action_success_messages[a]);
        break;
    case 2:
        strcpy(actionresult, action_super_messages[a]);
        break;
    default:
        break;
    }

    badcount = 0;
    for (i = 0; i < STAT_COUNT; i++)
    {
        /*If any danger state, report it*/
        if (p->stat_state[i] == DANGER_STATE)
        {
            strcpy(statusreport, danger_state_messages[i]);
            return;
        }
        else if (p->stat_state[i] == BAD_STATE)
        {
            badlist[badcount] = (state)p->stat_name[i];
            badcount++;
        }
    }
    /*otherwise report a random bad state*/
    if (badcount)
    {
        randval = rand() % badcount;
        strcpy(statusreport, bad_state_messages[badlist[randval]]);
    }
    else
    {
        /*otherwise report a random stat*/
        randval = rand() % (STAT_COUNT);
        if (p->stat_state[randval] == NORMAL_STATE)
        {
            strcpy(statusreport, normal_state_messages[randval]);
        }
        else if (p->stat_state[randval] == GOOD_STATE)
        {
            strcpy(statusreport, good_state_messages[randval]);
        }
        else
        {
            printf("Error: this should be unreachable in report_result()\n");
        }
    }
}

void handle_action(pet *p, action a, char *actionresult, char *statusreport)
{
    int success;
    int updated;

    switch (*p->growth){
        case EGG:
            strcpy(actionresult, meme_egg_actions[a]);
            strcpy(statusreport, "Your egg is still an egg");
            return;
        case ADULT:
            strcpy(actionresult, "Your pet is all grown up now!");
            strcpy(statusreport, "Sell it off for some quick bucks!");
            return;
        default:
            break;
    }

    success = calc_action(p, a);

    switch (a)
    {
    case ACTION_FEED:
        if (success)
        {
            if (success == 2)
            {
                if (p->stat_state[STAT_HUNGER] == DANGER_STATE)
                {
                    p->stat_state[STAT_HUNGER] = GOOD_STATE;
                }
            }
            if (p->stat_state[STAT_HUNGER] == NORMAL_STATE || p->stat_state[STAT_HUNGER] == BAD_STATE)
            {
                p->stat_state[STAT_HUNGER] = GOOD_STATE;
            }
            else if (p->stat_state[STAT_HUNGER] == DANGER_STATE)
            {
                p->stat_state[STAT_HUNGER] = NORMAL_STATE;
            }
            p->since_last_change[STAT_HUNGER] = 0;
        }
        break;
    case ACTION_PLAY:
        if (success)
        {
            updated = update_stat(&p->stat_state[STAT_FATIGUE], p->since_last_change[STAT_FATIGUE], p->multiplier[STAT_FATIGUE], p->offsets[STAT_FATIGUE]);
            if (updated)
            {
                p->since_last_change[STAT_FATIGUE] = 0;
            }
            else
            {
                p->since_last_change[STAT_FATIGUE]++;
            }

            updated = update_stat(&p->stat_state[STAT_CLEANLINESS], p->since_last_change[STAT_CLEANLINESS], p->multiplier[STAT_CLEANLINESS], p->offsets[STAT_CLEANLINESS]);
            if (updated)
            {
                p->since_last_change[STAT_CLEANLINESS] = 0;
            }
            else
            {
                p->since_last_change[STAT_CLEANLINESS]++;
            }

            *p->exp += 3;
            if (p->stat_state[STAT_HAPPINESS] == DANGER_STATE)
            {
                p->stat_state[STAT_HAPPINESS] = BAD_STATE;
            }
            else if (p->stat_state[STAT_HAPPINESS] == BAD_STATE)
            {
                p->stat_state[STAT_HAPPINESS] = NORMAL_STATE;
            }

            if (success == 2)
            {
                p->stat_state[STAT_HAPPINESS] = GOOD_STATE;
            }
            p->since_last_change[STAT_HAPPINESS] = 0;
        }
        break;
    case ACTION_BATHE:
        if (success)
        {
            if (p->stat_state[STAT_CLEANLINESS] == DANGER_STATE)
            {
                if (success == 2)
                {
                    p->stat_state[STAT_CLEANLINESS] = GOOD_STATE;
                }
                else
                {
                    p->stat_state[STAT_CLEANLINESS] = NORMAL_STATE;
                }
            }
            else if (p->stat_state[STAT_CLEANLINESS] == BAD_STATE || p->stat_state[STAT_CLEANLINESS] == NORMAL_STATE)
            {
                p->stat_state[STAT_CLEANLINESS] = GOOD_STATE;
            }
            p->since_last_change[STAT_CLEANLINESS] = 0;
        }
        break;
    case ACTION_TRAIN:
        if (success)
        {
            updated = update_stat(&p->stat_state[STAT_FATIGUE], p->since_last_change[STAT_FATIGUE], p->multiplier[STAT_FATIGUE], p->offsets[STAT_FATIGUE]);
            if (updated)
            {
                p->since_last_change[STAT_FATIGUE] = 0;
            }
            else
            {
                p->since_last_change[STAT_FATIGUE]++;
            }

            updated = update_stat(&p->stat_state[STAT_CLEANLINESS], p->since_last_change[STAT_CLEANLINESS], p->multiplier[STAT_CLEANLINESS], p->offsets[STAT_CLEANLINESS]);
            if (updated)
            {
                p->since_last_change[STAT_CLEANLINESS] = 0;
            }
            else
            {
                p->since_last_change[STAT_CLEANLINESS]++;
            }

            if (success == 1)
            {
                *p->exp += 3;
                *p->value *= 1.1;
            }
            else if (success == 2)
            {
                *p->exp += 5;
                *p->value *= 1.2;
            }
        }
        break;
    case ACTION_SLEEP:
        if (success)
        {
            if (p->stat_state[STAT_FATIGUE] == DANGER_STATE)
            {
                p->stat_state[STAT_FATIGUE] = BAD_STATE;
            }
            else if (p->stat_state[STAT_FATIGUE] == BAD_STATE)
            {
                p->stat_state[STAT_FATIGUE] = NORMAL_STATE;
            }

            if (success == 2)
            {
                p->stat_state[STAT_FATIGUE] = GOOD_STATE;
            }
            p->since_last_change[STAT_FATIGUE] = 0;
        }
        break;
    case ACTION_MEDICINE:
        if (success)
        {
            p->stat_state[STAT_HEALTH] = NORMAL_STATE;
            p->since_last_change[STAT_HEALTH] = 0;
        }
        break;
    case ACTION_VET:
        if (success)
        {
            p->stat_state[STAT_HEALTH] = GOOD_STATE;
            p->since_last_change[STAT_HEALTH] = 0;
        }
        break;
    default:
        break;
    }

    report_result(p, a, success, actionresult, statusreport);
}

/*Testing funcs*/

void reset_pet(pet *p)
{
    int i;
    for (i = 0; i < STAT_COUNT; i++)
    {
        p->stat_state[i] = NORMAL_STATE;
        p->multiplier[i] = 0.1;
        p->offsets[i] = 0;
        p->since_last_change[i] = 0;
    }
}

void print_stats(pet *p)
{
    int i;
    printf("Stats: %s\n", p->name);
    for (i = 0; i < STAT_COUNT; i++)
    {
        printf("%d: %d\n", p->stat_name[i], p->stat_state[i]);
    }
}

void print_multipliers(pet *p)
{
    int i;
    printf("Multipliers: %s\n", p->name);
    for (i = 0; i < STAT_COUNT; i++)
    {
        printf("%d: %f\n", p->stat_name[i], p->multiplier[i]);
    }
}

void print_offsets(pet *p)
{
    int i;
    printf("Offsets: %s\n", p->name);
    for (i = 0; i < STAT_COUNT; i++)
    {
        printf("%d: %f\n", p->stat_name[i], p->offsets[i]);
    }
}

void print_since_last_change(pet *p)
{
    int i;
    printf("Since last change: %s\n", p->name);
    for (i = 0; i < STAT_COUNT; i++)
    {
        printf("%d: %d\n", p->stat_name[i], p->since_last_change[i]);
    }
}
