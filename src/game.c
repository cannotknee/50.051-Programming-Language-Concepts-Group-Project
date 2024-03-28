#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "pet.h"
#include "pages.h"
#include "game.h"


void init_game(game *g, char *name)
{
    g->name = name;
    g->day = 0;
    g->actions = MAX_ACTIONS;
    g->money = 100;
    g->pet = (pet *)malloc(sizeof(pet));
    init_pet(g->pet);
}

void free_game(game *g)
{
    free_pet(g->pet);
    free(g->name);
}

