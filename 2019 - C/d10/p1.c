#include <stdio.h>
#include "../utils.c"

int checkAstView(int x, int y, char *map);
int gcd(int a, int b);

void main()
{
    getFile("input");
    openFile;

    char *instring = malloc(36 * 36 * sizeof(char));

    for(int y = 0; y < 36; y++)
    {
        for(int x = 0; x < 36; x++)
        {
            instring[(y * 36) + x] = fgetc(curfile);
        }
        fgetc(curfile);
    }

    int bestview = 0;

    for(int y = 0; y < 36; y++)
    {
        for(int x = 0; x < 36; x++)
        {
            if(instring[(y * 36) + x] == '.') { continue; }

            int cur = checkAstView(x, y, instring);
            bestview = (cur > bestview) ? cur : bestview;
        }
    }

    printf("%i\n", bestview);
}

int checkAstView(int x, int y, char *map)
{
    int sum = 0;

    for(int i = 0; i < 36; i++)
    {
        for(int j = 0; j < 36; j++)
        {
            if((i == x) && (j == y)) { continue; }
            if(map[i + (j * 36)] == '.') { continue; }

            int difx = i - x;
            int dify = j - y;

            int cd = gcd((difx > -1) ? difx : -difx, (dify > -1) ? dify : -dify);

            if (cd == 1) { sum++; continue; } // line does not pass over any spaces

            difx /= cd;
            dify /= cd;

            int step = 1;
            char col = 0; // bool flag

            while(step < cd)
            {
                if(map[(x + (difx * step)) + ((y + (dify * step)) * 36)] == '#') { col = 1; }

                step++;
            }
            if(col == 0) { sum++; }
        }
    }

    return sum;
}

int gcd(int a, int b)
{
    if (a == 0) { return b; }
    if (b == 0) { return a; }
    if (a == b) { return a; }

    return (a > b) ? gcd(b, a % b) : gcd(a, b % a);
}
