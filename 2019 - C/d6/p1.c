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

    int sum = 0;
    int curlevel = 0;
    int levelsize;

    char *queueb = malloc(2500 * 3 * sizeof(char));
    char *queuet = queueb + 3;
    
    queueb[0] = 'C';
    queueb[1] = 'O';
    queueb[2] = 'M';

    while(queueb != queuet)
    {
        levelsize = (queuet - queueb) / 3;
        for(int i = 0; i < levelsize; i++)
        {
            sum += curlevel;
            
            for(int j = 0; j < 2500; j++)
            {
                if((queueb[0] == inarr[j * 8]) && (queueb[1] == inarr[(j * 8) + 1]) && (queueb[2] == inarr[(j * 8) + 2]))
                {
                    queuet[0] = inarr[(j * 8) + 4];
                    queuet[1] = inarr[(j * 8) + 5];
                    queuet[2] = inarr[(j * 8) + 6];

                    queuet += 3;
                }
            }

            queueb += 3;
        }
        curlevel++;
    }

    printf("%i\n", sum);

    free(inarr);
}
