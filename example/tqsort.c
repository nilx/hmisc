/**
 * @file tqsort.c
 * @brief tqsort.h usage example
 */

#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

#include "tqsort.h"

#define DATA_SIZE 8

int main(void)
{
    char data_char[DATA_SIZE];
    short data_shrt[DATA_SIZE];
    int data_int[DATA_SIZE];
    long data_long[DATA_SIZE];
    unsigned char data_uchar[DATA_SIZE];
    unsigned short data_ushrt[DATA_SIZE];
    unsigned int data_uint[DATA_SIZE];
    unsigned long data_ulong[DATA_SIZE];
    float data_flt[DATA_SIZE];
    double data_dbl[DATA_SIZE];
    size_t i;

    /* fill the arrays with pseudorandon data */
    for (i = 0; i < DATA_SIZE; i++) {
        data_char[i] = (char) (rand() % CHAR_MAX);
        data_shrt[i] = (short) (rand() % SHRT_MAX);
        data_int[i] = (int) (rand() % INT_MAX);
        data_long[i] = (long) (rand() % LONG_MAX);
        data_uchar[i] = (unsigned char) (rand() % UCHAR_MAX);
        data_ushrt[i] = (unsigned short) (rand() % USHRT_MAX);
        data_uint[i] = (unsigned int) (rand() % UINT_MAX);
        data_ulong[i] = (unsigned long) (rand() % ULONG_MAX);
        data_flt[i] = (float) (rand() / (float) RAND_MAX);
        data_dbl[i] = (double) (rand() / (double) RAND_MAX);
    }

    /* sort the arrays */
    qsort_char(data_char, DATA_SIZE);
    qsort_shrt(data_shrt, DATA_SIZE);
    qsort_int(data_int, DATA_SIZE);
    qsort_long(data_long, DATA_SIZE);
    qsort_uchar(data_uchar, DATA_SIZE);
    qsort_ushrt(data_ushrt, DATA_SIZE);
    qsort_uint(data_uint, DATA_SIZE);
    qsort_ulong(data_ulong, DATA_SIZE);
    qsort_flt(data_flt, DATA_SIZE);
    qsort_dbl(data_dbl, DATA_SIZE);

    /* print the arrays */
    for (i = 0; i < DATA_SIZE; i++) {
        printf("%i\t%i\t%i\t%li\t", data_char[i], data_shrt[i],
               data_int[i], data_long[i]);
        printf("%u\t%u\t%u\t%lu\t", data_uchar[i], data_ushrt[i],
               data_uint[i], data_ulong[i]);
        printf("%f\t%f\n", data_flt[i], data_dbl[i]);
    }

    return EXIT_SUCCESS;
}
