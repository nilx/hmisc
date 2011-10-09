/**
 * @file debug.c
 * @brief debug.h usage example
 */

#include <stdlib.h>
#include <math.h>

#include "debug.h"

#define LOOP_SIZE 1024*100

/* qcmp() comparison function for long */
static int cmp(const void *a, const void *b)
{
    return (int) (((*(const long *) a) > (*(const long *) b))
                  - ((*(const long *) a) < (*(const long *) b)));
}

int main(void)
{
    size_t i, j;
    double pi;
#ifndef NDEBUG
    long cycles[LOOP_SIZE];
    long cost;
#endif

    /* print some info, only if NDEBUG is not defined */
    DBG_PRINTF0("This is a debug message.\n");
    DBG_PRINTF1("This is a debug message from %s.\n", __FILE__);
    DBG_PRINTF2("This is a debug message from %s line %i.\n",
                __FILE__, __LINE__);
    DBG_PRINTF3("This is a debug message from %s line %i. "
                "And today is %s.\n", __FILE__, __LINE__, __DATE__);
    DBG_PRINTF4("%s, %s, %s, %s.\n", "blah", "blah", "blah", "blah");

    /* measure the total CPU time */
    printf("compute PI...\n");
    pi = 0.;
    DBG_CLOCK_START(0);
    for (i = 0; i < LOOP_SIZE; i++)
        pi += (4. / (8. * i + 1.)
               - 2. / (8. * i + 4)
               - 1. / (8. * i + 5)
               - 1. / (8. * i + 6)) / pow(16, i);
    DBG_CLOCK_TOGGLE(0);
    printf("PI = %1.16f\n", pi);
    DBG_PRINTF1("total CPU time spent : %0.3fs\n", DBG_CLOCK_S(0));

    /* measure the total CPU cycles */
    printf("recompute PI...\n");
    pi = 0.;
    DBG_CYCLE_START(0);
    for (i = 0; i < LOOP_SIZE; i++)
        pi += (4. / (8. * i + 1.)
               - 2. / (8. * i + 4)
               - 1. / (8. * i + 5)
               - 1. / (8. * i + 6)) / pow(16, i);
    DBG_CYCLE_TOGGLE(0);
    printf("PI = %1.16f\n", pi);
    DBG_PRINTF1("total CPU cycles spent : %ld\n", DBG_CYCLE(0));

    /* measure the CPU cycles per loop */
    printf("recompute PI...\n");
    pi = 0.;
#ifndef NDEBUG
    for (i = 0; i < LOOP_SIZE; i++) {
        DBG_CYCLE_START(0);
        DBG_CYCLE_TOGGLE(0);
        cycles[i] = DBG_CYCLE(0);
    }
    qsort(cycles, sizeof(long), LOOP_SIZE, &cmp);
    cost = cycles[LOOP_SIZE / 2];
#endif

    for (i = 0; i < LOOP_SIZE; i++) {
        DBG_CYCLE_START(0);
        pi += (4. / (8. * i + 1.)
               - 2. / (8. * i + 4)
               - 1. / (8. * i + 5)
               - 1. / (8. * i + 6)) / pow(16, i);
        DBG_CYCLE_TOGGLE(0);
#ifndef NDEBUG
        cycles[i] = DBG_CYCLE(0);
#endif
    }
    printf("PI = %1.16f\n", pi);
    DBG_PRINTF1("median CPU cycles per loop : %ld\n",
                (qsort(cycles, sizeof(long), LOOP_SIZE, &cmp),
                 cycles[LOOP_SIZE / 2] - cost));

    return EXIT_SUCCESS;
}
