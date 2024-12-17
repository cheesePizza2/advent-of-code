#include <stdio.h>
#include <string.h>

#include "../utils.h"

int checkPhase(int *intcode, int *phase);
int runAmplifier(int *memory, int input, int setting);

// i'm not sure how exactly to pass in- and output between functions, so i'm just going to copy my current intcode computer and refit it for this program.
// something tells me i'm going to be doing that a lot for this event...
void main()
{
    getFile("input");
    openFile;

    int *intcode = malloc(200 * sizeof(int));
    int *backup = malloc(200 * sizeof(int));

    char *instring = malloc(1000 * sizeof(char));
    char *token = malloc(5 * sizeof(char));

    fscanf(curfile, "%s", instring);

    int i = 0;

    while (token = strsep(&instring, ","))
    {
        intcode[i] = atoi(token);
        backup[i] = intcode[i];
        i++;
    }

    free(token);
    free(instring);

    int maxsol = 0;
    // not the most efficient but whatever.
    for(int a = 0; a < 5; a++)
    {
        for(int b = 0; b < 5; b++)
        {
            if(b == a) { continue; }
            for(int c = 0; c < 5; c++)
            {
                if((c == a) || (c == b)) { continue; }
                for(int d = 0; d < 5; d++)
                {
                    if((d == a) || (d == b) || (d == c)) { continue; }
                    int e = 10 - a - b - c - d;

                    int phase[5] = {a, b, c, d, e};
                    int temp = checkPhase(intcode, phase);

                    maxsol = (temp > maxsol) ? temp : maxsol;
                }
            }
        }
    }

    printf("%d\n", maxsol);
}

int checkPhase(int *intcode, int *phase)
{
    int buffer = 0;
    for(int i = 0; i < 5; i++)
    {
        buffer = runAmplifier(intcode, buffer, phase[i]);
    }
    return buffer;
}

int runAmplifier(int *memory, int input, int setting)
{
    int in_count = 0;
    int intval;
    int opcode;
    int par1, par2, par3;

    for(int i = 0; ; )
    {
        intval = memory[i];
        opcode = intval % 100;

        par1 = (intval % 1000) / 100;
        par2 = (intval % 10000) / 1000;
        par3 = (intval % 100000) / 10000;

        switch(opcode)
        {
            case 1:
                if(par3 != 0) { printf("Error occurred: got par3 %i with opcode 1 at %i\n", par3, i); return -1; }

                memory[memory[i + 3]] = getParameter(par1, i + 1, memory) + getParameter(par2, i + 2, memory);

                i += 4;
                break;
            case 2:
                if(par3 != 0) { printf("Error occurred: got par3 %i with opcode 2 at %i\n", par3, i); return -1; }

                memory[memory[i + 3]] = getParameter(par1, i + 1, memory) * getParameter(par2, i + 2, memory);

                i += 4;
                break;
            case 3:
                if(par1 != 0) { printf("Error occurred: got par1 %i with opcode 3 at %i\n", par1, i); return -1; }

                switch(in_count)
                {
                    case 0:
                        memory[memory[i + 1]] = setting;
                        break;
                    case 1:
                        memory[memory[i + 1]] = input;
                        break;
                    default:
                        printf("Error occurred: ran input for the third time.\n");
                        return -1;
                }

                in_count++;
                i += 2;
                break;
            case 4:
                return getParameter(par1, i + 1, memory);
            case 5:
                if(getParameter(par1, i + 1, memory))
                {
                    i = getParameter(par2, i + 2, memory);
                }
                else
                {
                    i += 3;
                }
                break;
            case 6:
                if(getParameter(par1, i + 1, memory) == 0)
                {
                    i = getParameter(par2, i + 2, memory);
                }
                else
                {
                    i += 3;
                }
                break;
            case 7:
                // par3 is assumed to be immediate for some reason
                par3 = 1;
                if(getParameter(par1, i + 1, memory) < getParameter(par2, i + 2, memory))
                {
                    memory[getParameter(par3, i + 3, memory)] = 1;
                }
                else
                {
                    memory[getParameter(par3, i + 3, memory)] = 0;
                }
                i += 4;
                break;
            case 8:
                // par3 is assumed to be immediate for some reason
                par3 = 1;
                if(getParameter(par1, i + 1, memory) == getParameter(par2, i + 2, memory))
                {
                    memory[getParameter(par3, i + 3, memory)] = 1;
                }
                else
                {
                    memory[getParameter(par3, i + 3, memory)] = 0;
                }
                i += 4;
                break;
            default:
                printf("Error occurred: got instruction %i at %i\n", memory[i], i);
                return -1;
        }
    }
}
