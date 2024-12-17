#include "../utils.h"

void main()
{
    getFile("input");
    openFile;

    char curstring[50];
    int output = 0;

    while(fscanf(curfile, "%s\n", curstring) != EOF)
    {
        int curint = atoi(curstring);
        output += (curint / 3) - 2;
    }

    printf("%i\n", output);
}
