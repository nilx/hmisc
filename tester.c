#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

/* include the c89stdint definitions */
#include "c89stdint.h"


int main(void)
{
    /* test 8 bit type */
    {
        uint8_t prev = 1, cur = 1;
        int bits = 0;

        do {
            prev = cur;
            cur += cur;
            bits++;
        } while (cur > prev && cur / 2 == prev);

        assert(8 == bits);
    }
    printf(" 8 ");

    /* test 16 bit type */
    {
        uint16_t prev = 1, cur = 1;
        int bits = 0;

        do {
            prev = cur;
            cur += cur;
            bits++;
        } while (cur > prev && cur / 2 == prev);

        assert(16 == bits);
    }
    printf("16 ");

    /* test 32bit type */
    {
        uint32_t prev = 1, cur = 1;
        int bits = 0;

        do {
            prev = cur;
            cur += cur;
            bits++;
        } while (cur > prev && cur / 2 == prev);

        assert(32 == bits);
    }
    printf("32 ");

#ifdef UINT64_MAX
    /* test 64bit type */
    {
        uint64_t prev = 1, cur = 1;
        int bits = 0;

        do {
            prev = cur;
            cur += cur;
            bits++;
        } while (cur > prev && cur / 2 == prev);

        assert(64 == bits);
    }
    printf("64 ");
#else
    printf("   ");
#endif

    return EXIT_SUCCESS;
}
