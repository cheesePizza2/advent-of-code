#include "../utils.h"

int reccalcfuel(int x);

void main()
{
    getFile("input");
    openFile;

    char curstring[50];
    int output = 0;

    while(fscanf(curfile, "%s\n", curstring) != EOF)
    {
        int curint = atoi(curstring);
        output += reccalcfuel(curint);
    }

    printf("%i\n", output);
}

int reccalcfuel(int x)
{
    int curfuel = (x / 3) - 2;

    if(curfuel > 0)
    {
        return curfuel + reccalcfuel(curfuel);
    }
    return 0;
}
