/**
 * @file tqsort.c
 * @brief tqsort.h usage example
 */

#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

#include "tqsort.h"

static size_t size = 8; 

int main(void)
{
    char data_char[size];
    short data_shrt[size];
    int data_int[size];
    long data_long[size];
    unsigned char data_uchar[size];
    unsigned short data_ushrt[size];
    unsigned int data_uint[size];
    unsigned long data_ulong[size];
    float data_flt[size];
    double data_dbl[size];
    size_t i;

    /* fill the arrays with pseudorandon data */
    for (i=0; i<size; i++) {
	data_char[i] = rand() % CHAR_MAX;
	data_shrt[i] = rand() % SHRT_MAX;
	data_int[i] = rand() % INT_MAX;
	data_long[i] = rand() % LONG_MAX;
	data_uchar[i] = rand() % UCHAR_MAX;
	data_ushrt[i] = rand() % USHRT_MAX;
	data_uint[i] = rand() % UINT_MAX;
	data_ulong[i] = rand() % ULONG_MAX;
	data_flt[i] = rand() / (float) RAND_MAX;
	data_dbl[i] = rand() / (double) RAND_MAX;
    }

    /* sort the arrays */
    qsort_char(data_char, size);
    qsort_shrt(data_shrt, size);
    qsort_int(data_int, size);
    qsort_long(data_long, size);
    qsort_uchar(data_uchar, size);
    qsort_ushrt(data_ushrt, size);
    qsort_uint(data_uint, size);
    qsort_ulong(data_ulong, size);
    qsort_flt(data_flt, size);
    qsort_dbl(data_dbl, size);

    /* print the arrays */
    for (i=0; i<size; i++) {
	printf("%li\t%li\t%li\t%li\t", data_char[i], data_shrt[i], data_int[i], data_long[i]);
	printf("%lu\t%lu\t%lu\t%lu\t", data_uchar[i], data_ushrt[i], data_uint[i], data_ulong[i]);
	printf("%lf\t%lf\n", data_flt[i], data_dbl[i]);
    }

    return EXIT_SUCCESS;
}
