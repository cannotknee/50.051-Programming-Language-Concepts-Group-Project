#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "types.h"
#include "pet_file_io.h"

void read_pet_state_from_csv(const char *filename, pet *p) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: Could not open file %s\n", filename);
        return;
    }

    /* Allocate memory for name attribute */
    p->name = (char *)malloc(NAME_LENGTH * sizeof(char));
    if (p->name == NULL) {
        printf("Error: Memory allocation failed\n");
        fclose(file);
        return;
    }

    /* Read pet state from CSV file */
    if (fscanf(file, "%19[^,],%d,%d,%lf,%lf,%d\n", p->name, (int*)&p->stat_name[0],
               (int*)&p->stat_state[0], &p->multiplier[0], &p->offsets[0],
               &p->since_last_change[0]) != STAT_COUNT) {
        printf("Error: Invalid file format in %s\n", filename);
        fclose(file);
        free(p->name);
        return;
    }

    fclose(file);
}

void write_pet_state_to_csv(const char *filename, const pet *p) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error: Could not open file %s\n", filename);
        return;
    }

    /* Write pet state to CSV file */
    fprintf(file, "%s,%d,%d,%.2lf,%.2lf,%d\n", p->name, p->stat_name[STAT_GROWTH],
            p->stat_state[STAT_GROWTH], p->multiplier[STAT_GROWTH], p->offsets[STAT_GROWTH],
            p->since_last_change[STAT_GROWTH]);

    fclose(file);
}
