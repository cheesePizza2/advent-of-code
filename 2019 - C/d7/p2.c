#include <stdio.h>
#include <string.h>

#include "../utils.h"

int checkPhase(int *in_intcode, int *phase);

// i'm not sure how exactly to pass in- and output between functions, so i'm just going to copy my current intcode computer and refit it for this program.
// something tells me i'm going to be doing that a lot for this event...
void main()
{
    getFile("example");
    openFile;

    int *intcode = malloc(250 * sizeof(int));

    char *instring = malloc(1000 * sizeof(char));
    char *token = malloc(5 * sizeof(char));

    fscanf(curfile, "%s", instring);

    int i = 0;

    while (token = strsep(&instring, ","))
    {
        intcode[i] = atoi(token);
        i++;
    }

    free(token);
    free(instring);

    int maxsol = 0;
    // not the most efficient but whatever.
    for(int a = 5; a < 10; a++)
    {
        for(int b = 5; b < 10; b++)
        {
            if(b == a) { continue; }
            for(int c = 5; c < 10; c++)
            {
                if((c == a) || (c == b)) { continue; }
                for(int d = 5; d < 10; d++)
                {
                    if((d == a) || (d == b) || (d == c)) { continue; }
                    int e = 35 - a - b - c - d;
                    printf("%i%i%i%i%i - ", a, b, c, d, e);

                    int phase[5] = {a, b, c, d, e};
                    int temp = checkPhase(intcode, phase);

                    printf("%i\n", temp);

                    maxsol = (temp > maxsol) ? temp : maxsol;
                }
            }
        }
    }

    printf("%i\n", maxsol);
}

// HERE IS THE PROBLEM:
// right now we're collecting one output and immediately shoving it in as input to the next one
// that is, A runs with one input until it gets one output, then B runs with that input until it gets an output, and so on
// but the problem description implies that is not what we want.
// instead, you want A to keep running, producing a list of outputs, and pausing when it hits an input instruction that's unfilled
// then B runs with that list of inputs until it hits an unfilled input instruction.
// and so on with C, D, and E
// which implies we want some kind of concurrency - different threads for A B C D and E, when A hits an output it waits until B hits an input, they match, integer is sent, keep running
// which means all the following code needs to be wiped FUCK

int checkPhase(int *in_intcode, int *phase)
{
    int *intcodes = malloc(250 * 5 * sizeof(int));
    int out = 0;
    char first[5] = {1, 1, 1, 1, 1};
    int indices[5] = {0, 250, 500, 750, 1000};

    for(int i = 0; i < 250; i++)
    {
        intcodes[i] = in_intcode[i];
        intcodes[i + 250] = intcodes[i];
        intcodes[i + 500] = intcodes[i];
        intcodes[i + 750] = intcodes[i];
        intcodes[i + 1000] = intcodes[i];
    }

    while(1)
    {
        int buffer = out;
        for(int amp = 0; amp < 5; amp++)
        {
            int intval;
            int opcode;
            int par1, par2, par3;
            char exit = 0;
            int i = indices[amp];

            while(exit == 0)
            {
                intval = intcodes[i];
                opcode = intval % 100;

                par1 = (intval % 1000) / 100;
                par2 = (intval % 10000) / 1000;
                par3 = (intval % 100000) / 10000;

                switch(opcode)
                {
                    case 1:
                        if(par3 != 0) { printf("Error occurred: got par3 %i with opcode 1 at %i\n", par3, i); return -1; }

                        intcodes[intcodes[i + 3]] = getParameter(par1, i + 1, intcodes) + getParameter(par2, i + 2, intcodes);

                        i += 4;
                        break;
                    case 2:
                        if(par3 != 0) { printf("Error occurred: got par3 %i with opcode 2 at %i\n", par3, i); return -1; }

                        intcodes[intcodes[i + 3]] = getParameter(par1, i + 1, intcodes) * getParameter(par2, i + 2, intcodes);

                        i += 4;
                        break;
                    case 3:
                        if(par1 != 0) { printf("Error occurred: got par1 %i with opcode 3 at %i\n", par1, i); return -1; }

                        if(first[amp] == 1)
                        {
                            intcodes[intcodes[i + 1]] = phase[amp];
                            first[amp] = 0;
                        } else {
                            intcodes[intcodes[i + 1]] = buffer;
                        }

                        i += 2;
                        break;
                    case 4:
                        buffer = getParameter(par1, i + 1, intcodes);
                        exit = 1;
                        break;
                    case 5:
                        if(getParameter(par1, i + 1, intcodes))
                        {
                            i = getParameter(par2, i + 2, intcodes) + (250 * amp);
                        }
                        else
                        {
                            i += 3;
                        }
                        break;
                    case 6:
                        if(getParameter(par1, i + 1, intcodes) == 0)
                        {
                            i = getParameter(par2, i + 2, intcodes) + (250 * amp);
                        }
                        else
                        {
                            i += 3;
                        }
                        break;
                    case 7:
                        // par3 is assumed to be immediate for some reason
                        par3 = 1;
                        if(getParameter(par1, i + 1, intcodes) < getParameter(par2, i + 2, intcodes))
                        {
                            intcodes[getParameter(par3, i + 3, intcodes)] = 1;
                        }
                        else
                        {
                            intcodes[getParameter(par3, i + 3, intcodes)] = 0;
                        }
                        i += 4;
                        break;
                    case 8:
                        // par3 is assumed to be immediate for some reason
                        par3 = 1;
                        if(getParameter(par1, i + 1, intcodes) == getParameter(par2, i + 2, intcodes))
                        {
                            intcodes[getParameter(par3, i + 3, intcodes)] = 1;
                        }
                        else
                        {
                            intcodes[getParameter(par3, i + 3, intcodes)] = 0;
                        }
                        i += 4;
                        break;
                    case 99:
                        return out;
                    default:
                        printf("Error occurred: got instruction %i at %i\n", intcodes[i], i);
                        return -1;
                }
            }
            printf("loop ");
            if((indices[amp] == i) && (out == buffer)) { return out; }

            indices[amp] = i;
        }

        out = buffer;
    }
}
