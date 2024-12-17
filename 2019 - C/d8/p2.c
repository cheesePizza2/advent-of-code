#include <stdio.h>
#include "../utils.h"

void main()
{
    getFile("input");
    openFile;

    char *instring = malloc((25 * 6 * 100 + 1) * sizeof(char));

    fscanf(curfile, "%s\n", instring);

    int layer;

    for(int i = 0; i < 6; i++)
    {
        for(int j = 0; j < 25; j++)
        {
            layer = 0;
            while(instring[(layer * 150) + (i * 25) + j] == '2') { layer++; }
            if(instring[(layer * 150) + (i * 25) + j] == '0') { printf(" "); } else { printf("#"); }
        }
        printf("\n");
    }
}
