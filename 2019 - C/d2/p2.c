#include <string.h>
#include "../utils.h"

void main()
{
    getFile("input");
    openFile;

    long long *intcode = malloc(200 * sizeof(long long));
    long long *backup = malloc(200 * sizeof(long long));

    char *instring = malloc(200 * sizeof(char));
    char *token = malloc(5 * sizeof(char));

    long long noun = 0;
    long long verb = 0;

    fscanf(curfile, "%s", instring);

    int i = 0;

    while (token = strsep(&instring, ","))
    {
        intcode[i] = atoll(token);
        backup[i] = intcode[i];
        i++;
    }

    free(token);
    free(instring);

    while(1)
    {
        intcode[1] = noun;
        intcode[2] = verb;

        runIntComp(intcode);

        if(intcode[0] == 19690720)
        {
            printf("Noun: %lli\nVerb: %lli\n", noun, verb);

            free(intcode);
            free(backup);
            return;
        }

        if(verb == 99)
        {
            noun++;
            verb = 0;
        }
        else
        {
            verb++;
        }

        for(int i = 0; i < 200; i++)
        {
            intcode[i] = backup[i];
        }
    }
}
