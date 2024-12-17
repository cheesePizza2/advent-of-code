#include <string.h>
#include "../utils.h"
//#include <stdbool.h>

#define GRID_SIZE 25000

void main()
{
    getFile("input");
    openFile;

    char *infirstring = malloc(2000 * sizeof(char));
    char *insecstring = malloc(2000 * sizeof(char));

    fscanf(curfile, "%s", infirstring);
    fscanf(curfile, "%s", insecstring);

    char *token = malloc(5 * sizeof(char));

    char *grid = malloc(GRID_SIZE * GRID_SIZE * sizeof(char));

    int curx = (GRID_SIZE / 2) - 1;
    int cury = (GRID_SIZE / 2) - 1;

    unsigned long step = 0;

    while (token = strsep(&infirstring, ","))
    {
        int val = atoi(token+1);

        for(int i = 0; i < val; i++)
        {
            step++;
            switch(token[0])
            {
                case 'R':
                    curx++;
                    break;
                case 'L':
                    curx--;
                    break;
                case 'U':
                    cury++;
                    break;
                case 'D':
                    cury--;
                    break;
            }
            grid[(GRID_SIZE * curx) + cury] = 1;
        }
    }

    free(infirstring);
    curx = (GRID_SIZE / 2) - 1;
    cury = (GRID_SIZE / 2) - 1;

    unsigned int cur_min_inter = ~0;

    while (token = strsep(&insecstring, ","))
    {
        int val = atoi(token+1);

        for(int i = 0; i < val; i++)
        {
            switch(token[0])
            {
                case 'R':
                    curx++;
                    break;
                case 'L':
                    curx--;
                    break;
                case 'U':
                    cury++;
                    break;
                case 'D':
                    cury--;
                    break;
            }

            if(grid[(GRID_SIZE * curx) + cury])
            {
                int distance = abs(curx - ((GRID_SIZE / 2) - 1)) + abs(cury - ((GRID_SIZE / 2) - 1));
                cur_min_inter = (distance < cur_min_inter) ? distance : cur_min_inter;
            }
        }
    }

    printf("%i\n", cur_min_inter);
    
    free(token);
    free(insecstring);
    free(grid);
}
