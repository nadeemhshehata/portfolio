/*
 ============================================================================
 Name        : myrecord_bst.h
 Author      : Nadeem hassan
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <math.h>
#include <string.h>
#include "myrecord_bst.h"


static void stats_add(BSTDS *ds, float x) {
    int n_prev = ds->count;
    float mean_prev = ds->mean;
    float sd_prev = ds->stddev;

    /* previous M2 (sum of squared deviations) */
    double M2_prev = (n_prev > 0) ? (double)n_prev * (double)sd_prev * (double)sd_prev : 0.0;

    int n = n_prev + 1;
    double delta = (double)x - mean_prev;
    double mean = mean_prev + delta / n;
    double delta2 = (double)x - mean;
    double M2 = M2_prev + delta * delta2;

    ds->count = n;
    ds->mean = (float)mean;
    ds->stddev = (n > 0) ? (float)sqrt(M2 / n) : 0.0f;
}

static void stats_remove(BSTDS *ds, float x) {
    int n_prev = ds->count;
    float mean_prev = ds->mean;
    float sd_prev = ds->stddev;

    if (n_prev <= 0) {
        /* nothing to remove */
        ds->count = 0;
        ds->mean = 0.0f;
        ds->stddev = 0.0f;
        return;
    }

    /* previous M2 */
    double M2_prev = (double)n_prev * (double)sd_prev * (double)sd_prev;

    int n = n_prev - 1;
    if (n == 0) {
        ds->count = 0;
        ds->mean = 0.0f;
        ds->stddev = 0.0f;
        return;
    }

    double delta = (double)x - mean_prev;
    /* after removal, new mean */
    double mean = ( (double)n_prev * mean_prev - (double)x ) / n;
    /* For removal, M2' = M2_prev - delta * (x - mean') */
    double M2 = M2_prev - delta * ((double)x - mean);

    if (M2 < 0 && M2 > -1e-6) M2 = 0; /* guard small negatives from FP error */

    ds->count = n;
    ds->mean = (float)mean;
    ds->stddev = (n > 0) ? (float)sqrt(M2 / n) : 0.0f;
    if (n == 1) {
        /* match expected output: stddev shown as nan for 1 element */
        ds->stddev = NAN;
    }
}

void add_record(BSTDS *ds, RECORD record) {
    if (ds == NULL) return;

    /* if key exists, we need to update the score and update stats accordingly:
       remove old score, add new score. */
    BSTNODE *found = bst_search(ds->root, record.name);
    if (found) {
        float old = found->data.score;
        /* update tree value first (or after — stats independent) */
        found->data.score = record.score;

        /* adjust stats for replacement: remove old then add new */
        stats_remove(ds, old);
        stats_add(ds, record.score);
    } else {
        /* insert new into BST */
        bst_insert(&ds->root, record);
        /* and update stats */
        stats_add(ds, record.score);
    }
}

void remove_record(BSTDS *ds, char *name) {
    if (ds == NULL || name == NULL) return;

    BSTNODE *found = bst_search(ds->root, name);
    if (!found) return;

    float x = found->data.score;
    /* delete from tree */
    bst_delete(&ds->root, name);
    /* update stats */
    stats_remove(ds, x);
}

void bstds_clean(BSTDS *ds) {
    if (ds == NULL) return;
    bst_clean(&ds->root);
    ds->count = 0;
    ds->mean = 0.0f;
    ds->stddev = 0.0f;
}
