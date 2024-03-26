#include <stdlib.h>
#include <stdio.h>

#include "pet.h"

void init_pet(pet* p) {
    int i;

    p->name = (char*)malloc(NAME_LENGTH * sizeof(char));
    p->stat_name = (stat*)malloc(STAT_COUNT * sizeof(stat));
    p->stat_state = (state*)malloc(STAT_COUNT * sizeof(state));
    p->multiplier = (double*)malloc(STAT_COUNT * sizeof(double));
    p->offsets = (double*)malloc(STAT_COUNT * sizeof(double));
    p->since_last_change = (int*)malloc(STAT_COUNT * sizeof(int));
    for (i = 0; i < STAT_COUNT; i++) {
        p->stat_name[i] = (stat)i;
        p->stat_state[i] = NORMAL_STATE;
        p->multiplier[i] = 0.1; /*Currently just set all to 0.1, will need to somehow randomise this or use template in future*/
        p->since_last_change[i] = 0;
    }
}

void free_pet(pet* p) {
    free(p->name);
    free(p->stat_name);
    free(p->stat_state);
    free(p->multiplier);
    free(p->since_last_change);
    p = NULL;
}

int update_stat(state* s, int since_last_change, double multiplier, float offset) {
    double randval;
    randval = rand() / RAND_MAX; /*Rand val btwn 0 & 1*/
    if (randval < since_last_change * multiplier + offset && *s >0) {
        *s = *s - 1;
        return 1;
    }
    return 0;
    /*Danger state will be handled in wrapper func update_all_stats*/
}

void update_offsets(pet* p){
    /*TODO any -1 offset due to GOOD_STATEs*/
    int i;
    int x = 0;
    p->offsets[STAT_FATIGUE] = 0.2 * (NORMAL_STATE - p->stat_state[STAT_HEALTH]);
    p->offsets[STAT_HEALTH] = 0.1 * (NORMAL_STATE - p->stat_state[STAT_CLEANLINESS]);
    p->offsets[STAT_HAPPINESS] = 0.0;
    for (i = 2; i < STAT_COUNT; i++) {
        /*If any danger state increase happiness transition chance by 30%*/
        if (p->stat_state[i] == DANGER_STATE) {
            p->offsets[STAT_HAPPINESS] += 0.3;
        }
        x += p->stat_state[i];
    }
    /*Increase transition chance by 10% if total of other stats is less than 6, 2 bad or 1 danger + 1 bad*/
    if (x < 6) {
        p->offsets[STAT_HAPPINESS] += 0.1;
    }
}

int update_all_stats(pet* p) {
    int i;
    int updated;
    update_offsets(p);
    /*use update_stat for all stats but growth*/
    for (i = 1; i < STAT_COUNT; i++) {
        if (p->stat_state[i] == DANGER_STATE) {
            /*pet dies if left in danger state for more than 2 turns*/
            if (p->since_last_change[i] > 1) {
                return 1;
            }
        }else {
            updated = update_stat(&p->stat_state[i], p->since_last_change[i], p->multiplier[i], p->offsets[i]);
            if (updated) {
                p->since_last_change[i] = 0;
            }
        }
    }
    return 0;
}

double calc_action_super_chance(pet *p, action a){
    int i;
    double chance = 0;
    switch (a) {
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
            for (i = 1; i < STAT_COUNT; i++) {
                if (p->stat_state[i] == GOOD_STATE) {
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

double calc_action_fail_chance(pet *p, action a){
    int i;
    double chance = 0;
    switch (a) {
        case ACTION_FEED:
            if (p->stat_state[STAT_HUNGER] > BAD_STATE) {
                chance = 1;
            }else{
                chance += 0.3 * (NORMAL_STATE - p->stat_state[STAT_HEALTH]);
                chance += 0.3 * (NORMAL_STATE - p->stat_state[STAT_FATIGUE]);
            }
            break;
        case ACTION_PLAY:
            if (p->stat_state[STAT_HAPPINESS] > BAD_STATE) {
                chance = 1;
            }else {
                chance += 0.5 * (NORMAL_STATE - p->stat_state[STAT_HEALTH]);
                chance += 0.5 * (NORMAL_STATE - p->stat_state[STAT_FATIGUE]);
            }
            break;
        case ACTION_BATHE:
            if (p->stat_state[STAT_CLEANLINESS] > BAD_STATE) {
                chance = 1;
            }else {
                chance += 0.3 * (NORMAL_STATE - p->stat_state[STAT_HEALTH]);
                chance += 0.1 * (NORMAL_STATE - p->stat_state[STAT_HAPPINESS]);
            }
            break;
        case ACTION_TRAIN:
            for (i = 1; i < STAT_COUNT; i++) {
                if (p->stat_state[i] == DANGER_STATE) {
                    chance = 1;
                    break;
                }else {
                    chance += 0.2 * (NORMAL_STATE - p->stat_state[i]);
                }
            }
            break;
        case ACTION_SLEEP:
            if (p->stat_state[STAT_FATIGUE] > BAD_STATE) {
                chance = 1;
            }else {
                chance += 0.3 * (NORMAL_STATE - p->stat_state[STAT_HEALTH]);
            }
            break;
        case ACTION_MEDICINE:
            if (p->stat_state[STAT_HEALTH] == BAD_STATE) {
                chance = 0.3;
            }else if (p->stat_state[STAT_HEALTH] == DANGER_STATE){
                chance = 0.8;
            }else{
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

int handle_action(pet *p, action a){
    /*
    double randval;
    randval = rand() / RAND_MAX; Rand val btwn 0 & 1*/
    
    switch (a) {
        case ACTION_FEED:
            break;
        case ACTION_PLAY:
            break;
        case ACTION_BATHE:
            break;
        case ACTION_TRAIN:
            break;
        case ACTION_SLEEP:
            break;
        case ACTION_MEDICINE:
            break;
        case ACTION_VET:
            return 1;
            break;
        default:
            return 0;
    }
    return 0;
}
