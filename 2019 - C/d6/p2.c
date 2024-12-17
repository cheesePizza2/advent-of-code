#include <stdio.h>
#include "../utils.h"

void main()
{
    getFile("input");
    openFile;

    // 2500 lines, 8 chars per line
    char *inarr = malloc(2500 * 8 * sizeof(char));

    for(int i = 0; i < 2500; i++)
    {
        fscanf(curfile, "%s", inarr + (i * 8));
    }

    char *loc = malloc(4 * sizeof(char));

    char *youpath = malloc(500 * 3 * sizeof(char));
    char *add = youpath;
    loc[0] = 'Y';
    loc[1] = 'O';
    loc[2] = 'U';

    while((loc[0] != 'C') || (loc[1] != 'O') || (loc[2] != 'M'))
    {
        for(int i = 0; i < 2500; i ++)
        {
            if((loc[0] == inarr[(i * 8) + 4]) && (loc[1] == inarr[(i * 8) + 5]) && (loc[2] == inarr[(i * 8) + 6]))
            {
                loc[0] = inarr[i * 8];
                loc[1] = inarr[(i * 8) + 1];
                loc[2] = inarr[(i * 8) + 2];

                add[0] = loc[0];
                add[1] = loc[1];
                add[2] = loc[2];

                add += 3;
            }
        }
    }

    char *sanpath = malloc(500 * 3 * sizeof(char));
    add = sanpath;
    loc[0] = 'S';
    loc[1] = 'A';
    loc[2] = 'N';

    while((loc[0] != 'C') || (loc[1] != 'O') || (loc[2] != 'M'))
    {
        for(int i = 0; i < 2500; i ++)
        {
            if((loc[0] == inarr[(i * 8) + 4]) && (loc[1] == inarr[(i * 8) + 5]) && (loc[2] == inarr[(i * 8) + 6]))
            {
                loc[0] = inarr[i * 8];
                loc[1] = inarr[(i * 8) + 1];
                loc[2] = inarr[(i * 8) + 2];

                add[0] = loc[0];
                add[1] = loc[1];
                add[2] = loc[2];

                add += 3;
            }
        }
    }

    for(int i = 0; i < 500; i++)
    {
        for(int j = 0; j < 500; j++)
        {
            if((youpath[(i * 3)] == sanpath[(j * 3)]) && (youpath[(i * 3) + 1] == sanpath[(j * 3) + 1]) && (youpath[(i * 3) + 2] == sanpath[(j * 3) + 2]))
            {
                printf("%i\n", i + j);
                return;
            }
        }
    }
}
