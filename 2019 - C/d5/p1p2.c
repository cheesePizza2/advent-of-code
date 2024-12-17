#include <string.h>
#include "../utils.h"

void main()
{
    getFile("input");
    openFile;

    long long *intcode = malloc(3000 * sizeof(long long));

    char *instring = malloc(3000 * sizeof(char));
    char *token = malloc(8 * sizeof(char));

    fscanf(curfile, "%s", instring);

    int i = 0;

    while (token = strsep(&instring, ","))
    {
        intcode[i++] = atoll(token);
    }

    free(instring);
    free(token);

    runIntComp(intcode);

    free(intcode);
}
