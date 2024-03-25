#include <stdlib.h>
#include <stdio.h>

#include "pet.h"

void init_pet(pet* p) {
    int i;

    p->name = (char*)malloc(NAME_LENGTH * sizeof(char));
    p->stat_name = (stat*)malloc(STAT_COUNT * sizeof(stat));
    p->stat_state = (state*)malloc(STAT_COUNT * sizeof(state));
    p->multiplier = (double*)malloc(STAT_COUNT * sizeof(double));
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

void update_stat(state* s, int since_last_change, double multiplier, float offset) {
    double randval;
    randval = rand() / RAND_MAX; /*Rand val btwn 0 & 1*/
    if (randval < since_last_change * multiplier + offset && *s >0) {
        *s = *s - 1;
    }
    /*Danger state will be handled in wrapper func update_stats*/
}