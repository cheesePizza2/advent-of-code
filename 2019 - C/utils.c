#include <stdio.h>
#include <string.h>

#include "utils.h"

void runIntComp(long long *memory)
{
    long long intval;
    long long opcode;
    long long par1, par2, par3;

    long long positional = 0;

    for(long long i = 0; ; )
    {
        intval = memory[i];
        opcode = intval % 100;

        par1 = (intval % 1000) / 100;
        par2 = (intval % 10000) / 1000;
        par3 = (intval % 100000) / 10000;

        switch(opcode)
        {
            case 1:
                long long sum = getParameter(par1, i + 1, memory, positional) + getParameter(par2, i + 2, memory, positional);

                if(par3 == 0)
                {
                    memory[memory[i + 3]] = sum;
                } else {
                    memory[memory[i + 3] + positional] = sum;
                }

                i += 4;
                break;
            case 2:
                long long prod = getParameter(par1, i + 1, memory, positional) * getParameter(par2, i + 2, memory, positional);

                if(par3 == 0)
                {
                    memory[memory[i + 3]] = prod;
                } else {
                    memory[memory[i + 3] + positional] = prod;
                }

                i += 4;
                break;
            case 3:
                long long scanned;
                scanf("%lli", &scanned);

                if(par1 == 0)
                {
                    memory[memory[i + 1]] = scanned;
                } else {
                    memory[memory[i + 1] + positional] = scanned;
                }

                i += 2;
                break;
            case 4:
                printf("%lli\n", getParameter(par1, i + 1, memory, positional));

                i += 2;
                break;
            case 5:
                if(getParameter(par1, i + 1, memory, positional))
                {
                    i = getParameter(par2, i + 2, memory, positional);
                }
                else
                {
                    i += 3;
                }
                break;
            case 6:
                if(getParameter(par1, i + 1, memory, positional) == 0)
                {
                    i = getParameter(par2, i + 2, memory, positional);
                }
                else
                {
                    i += 3;
                }
                break;
            case 7:
                if(getParameter(par1, i + 1, memory, positional) < getParameter(par2, i + 2, memory, positional))
                {
                    switch(par3)
                    {
                        // positional mode is immediate for some reason
                        case 0:
                        case 1:
                            memory[memory[i + 3]] = 1;
                            break;
                        case 2:
                            memory[memory[i + 3] + positional] = 1;
                            break;
                    }
                }
                else
                {
                    switch(par3)
                    {
                        // positional mode is immediate for some reason
                        case 0:
                        case 1:
                            memory[memory[i + 3]] = 0;
                            break;
                        case 2:
                            memory[memory[i + 3] + positional] = 0;
                            break;
                    }
                }
                i += 4;
                break;
            case 8:
                if(getParameter(par1, i + 1, memory, positional) == getParameter(par2, i + 2, memory, positional))
                {
                    switch(par3)
                    {
                        // positional mode is immediate for some reason
                        case 0:
                        case 1:
                            memory[memory[i + 3]] = 1;
                            break;
                        case 2:
                            memory[memory[i + 3] + positional] = 1;
                            break;
                    }
                }
                else
                {
                    switch(par3)
                    {
                        // positional mode is immediate for some reason
                        case 0:
                        case 1:
                            memory[memory[i + 3]] = 0;
                            break;
                        case 2:
                            memory[memory[i + 3] + positional] = 0;
                            break;
                    }
                }
                i += 4;
                break;
            case 9:
                positional += getParameter(par1, i + 1, memory, positional);
                i += 2;
                break;
            case 99:
                return;
            default:
                printf("Error occurred: got instruction %lli at %lli\n", memory[i], i);
                return;
        }
    }
}

long long getParameter(long long mode, long long pos, long long *memory, long long positional)
{
    switch(mode)
    {
        case 0:
            return memory[memory[pos]];
        case 1:
            return memory[pos];
        case 2:
            return memory[memory[pos] + positional];
        default:
            printf("Error occurred: got parameter %lli at %lli\n", mode, pos);
            return 0;
    }
}
