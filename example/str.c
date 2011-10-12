/**
 * @file str.c
 * @brief str.h usage example
 */

#include <stdlib.h>
#include <stdio.h>

#include "str.h"

int main()
{
    char str[] = "Lorem ipsum dolor sit amet, "
        "consectetur adipisicing elit, "
        "sed do eiusmod tempor incididunt ut labore et dolore magna aliqua.";
    char *pfx, *sfx;

    printf("The example string is:\n'%s'\n\n", str);

    /* allocate pfx and sfx at the length of str */
    pfx = (char *) malloc(strlen(str) * sizeof(char));
    sfx = (char *) malloc(strlen(str) * sizeof(char));

    /* split at the first comma */
    str_split2(str, ',', pfx, sfx);
    printf("Splitting at the first comma:\n- '%s'\n- '%s'\n\n", pfx, sfx);

    /* convert to uppercase and lowercase */
    (void) str_toupper(str);
    printf("Uppercase:\n'%s'\n", str);
    /* you can also use the return value */
    printf("Lowercase:\n'%s'\n", str_tolower(str));

    free(pfx);
    free(sfx);
    return EXIT_SUCCESS;
}
