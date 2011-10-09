/**
 * @file xmtime.c
 * @brief xmtime.h usage example
 */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "xmtime.h"

int main()
{
    unsigned long timer;
    size_t i, j;
    double pi = 0.;

    /* measure the initial time */
    timer = xmtime();

    /*
     * compute PI with BBP
     * http://en.wikipedia.org/wiki/Bailey-Borwein-Plouffe_formula
     */
    /*
     * naive slow and inaccurate implementation, and 10 steps are
     * enough, but that's not our focus...
     */
    printf("compute PI...\n");
    for (i = 0; i < 1024 * 1024; i++)
	pi += (4. / (8. * i + 1.)
	       - 2. / (8. * i + 4)
	       - 1. / (8. * i + 5)
	       - 1. / (8. * i + 6)) / pow(16, i);
    printf("PI = %1.16f\n", pi);

    /* measure the elapsed time */
    timer = xmtime() - timer;
    printf("elapsed time is %lums\n", timer);
    printf("elapsed time is %0.3fs\n", timer / 1000.);

    return EXIT_SUCCESS;
}
