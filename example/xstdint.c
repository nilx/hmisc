/**
 * @file xstdint.c
 * @brief xstdint.h usage example
 */

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "xstdint.h"

#define TEST(TYPE, N) {                                 \
        TYPE prev = 1, cur = 1;                         \
        int bits = 0;                                   \
        do {                                            \
            prev = cur;                                 \
            cur += cur;                                 \
            bits++;                                     \
        } while (cur > prev && cur / 2 == prev);        \
        assert(N == bits);                              \
    }

int main(void)
{
    /* test 8 bit type */
    TEST(uint8_t, 8);
    printf(" 8 ");

    /* test 16 bit type */
    TEST(uint16_t, 16);
    printf("16 ");

    /* test 32 bit type */
    TEST(uint32_t, 32);
    printf("32 ");

#ifdef UINT64_MAX
    /* test 64bit type */
    TEST(uint64_t, 64);
    printf("64 ");
#else
    printf("   ");
#endif

    printf("\n");

    return EXIT_SUCCESS;
}
