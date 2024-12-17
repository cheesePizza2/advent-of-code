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

    unsigned long *grid = malloc(GRID_SIZE * GRID_SIZE * sizeof(unsigned long));

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
            if(grid[(GRID_SIZE * curx) + cury] == 0)
            {
                grid[(GRID_SIZE * curx) + cury] = step;
            }
        }
    }

    free(infirstring);
    curx = (GRID_SIZE / 2) - 1;
    cury = (GRID_SIZE / 2) - 1;
    step = 0;

    unsigned long cur_min_steps = ~0;

    while (token = strsep(&insecstring, ","))
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

            if(grid[(GRID_SIZE * curx) + cury])
            {
                int steps = step + grid[(GRID_SIZE * curx) + cury];
                cur_min_steps = (steps < cur_min_steps) ? steps : cur_min_steps;
            }
        }
    }

    printf("%li\n", cur_min_steps);
    
    free(token);
    free(insecstring);
    free(grid);
}
