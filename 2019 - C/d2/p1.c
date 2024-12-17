#include <string.h>
#include "../utils.h"

void main(int argc, char **argv)
{
    if(argc != 3)
    {
        printf("Wrong number of arguments! Got %i and expected 2!\n", (argc - 1));
        return;
    }

    getFile("input");
    openFile;

    long long *intcode = malloc(200 * sizeof(long long));

    char *instring = malloc(200 * sizeof(char));
    char *token = malloc(5 * sizeof(char));

    fscanf(curfile, "%s", instring);

    int i = 0;

    while (token = strsep(&instring, ","))
    {
        intcode[i++] = atoll(token);
    }

    free(instring);
    free(token);

    intcode[1] = atoll(argv[1]);
    intcode[2] = atoll(argv[2]);

    runIntComp(intcode);
    
    printf("%lli\n", intcode[0]);

    free(intcode);
}
