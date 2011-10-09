/**
 * @file smem.c
 * @brief smem.h usage example
 */

#include <stdlib.h>
#include <stdio.h>

#include "smem.h"

int main()
{
    float *ptr;

    /*
     * if there is not enough free moemory on the machine,
     * the program execution will be aborted
     */

    /* allocate an array of 1024 floats */
    ptr = SMALLOC(1024, float);
    printf("ptr = %d\n", ptr);

    /* reallocate to 2048 floats */
    ptr = SREALLOC(ptr, 2048, float);
    printf("ptr = %d\n", ptr);

    /* free the array; ptr is reset to NULL */
    SFREE(ptr);
    printf("ptr = %d\n", ptr);

    /* free once again; ptr is NULL, nothing is done */
    SFREE(ptr);
    printf("ptr = %d\n", ptr);

    /* allocate an aray with calloc(); the array content is set to 0 */
    ptr = SCALLOC(1024, float);
    printf("ptr = %d\n", ptr);

    /* ask for too much memory ~ 4G */
    ptr = SREALLOC(ptr, 1024 * 1024 * 1024, float);
    printf("ptr = %d\n", ptr);

    return EXIT_SUCCESS;
}
