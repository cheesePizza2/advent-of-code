#include <string.h>
#include <stdio.h>
#include <stdlib.h>

char validate_int(int val);

void main(int argc, char** argv)
{
    if(argc != 3)
    {
        printf("Wrong number of arguments! Got %i and expected 2!\n", (argc - 1));
        return;
    }

    int min = atoi(argv[1]);
    int max = atoi(argv[2]);

    int count = 0;

    for(int i = min; i <= max; i++)
    {
        count += validate_int(i);
    }

    printf("%i\n", count);
}

char validate_int(int val)
{
    char *val_s = malloc(10 * sizeof(char));
    sprintf(val_s, "%d", val);

    char reqs = 0;

    for(int i = 1; i < 6; i++)
    {
        if(val_s[i - 1] == val_s[i])
        {
            reqs = reqs | 1;
        }
        else if(val_s[i - 1] > val_s[i])
        {
            reqs = reqs | 2;
        }
    }

    if(reqs == 1)
    {
        return 1;
    }
    return 0;
}
