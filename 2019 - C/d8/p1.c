#include <stdio.h>
#include "../utils.h"

void main()
{
    getFile("input");
    openFile;

    char *instring = malloc((25 * 6 * 100 + 1) * sizeof(char));

    fscanf(curfile, "%s\n", instring);

    unsigned int leastzeros = -1;
    unsigned int leastlayer = -1;

    for(int i = 0; i < 100; i++)
    {
        int curzeros = 0;
        for(int j = 0; j < 150; j++)
        {
            if(instring[(i * 150) + j] == '0') { curzeros++; }
        }

        if(curzeros < leastzeros)
        {
            leastzeros = curzeros;
            leastlayer = i;
        }
    }
    
    int onedigs = 0;
    int twodigs = 0;

    for(int k = 0; k < 150; k++)
    {
        if(instring[(leastlayer * 150) + k] == '1') { onedigs++; }
        else if(instring[(leastlayer * 150) + k] == '2') { twodigs++; }
    }

    printf("%i\n", onedigs * twodigs);
}
