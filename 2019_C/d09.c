#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INTCOMP_SIZE 10000

long long getParameter(long long mode, long long pos, long long *memory, long long positional) {
  switch(mode) {
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

long long runIntComp(long long *memory, long long input) {
  long long positional = 0;

  for(long long i = 0; ; ) {
    long long intval = memory[i];
    long long opcode = intval % 100;

    long long par1 = (intval % 1000) / 100;
    long long par2 = (intval % 10000) / 1000;
    long long par3 = (intval % 100000) / 10000;

    switch(opcode) {
    case 1:
      long long sum = getParameter(par1, i + 1, memory, positional) + getParameter(par2, i + 2, memory, positional);

      switch(par3) {
      case 0:
      case 1:
        memory[memory[i + 3]] = sum;
        break;
      case 2:
        memory[memory[i + 3] + positional] = sum;
        break;
      }

      i += 4;
      break;
    case 2:
      long long prod = getParameter(par1, i + 1, memory, positional) * getParameter(par2, i + 2, memory, positional);
      
      switch(par3) {
      case 0:
      case 1:
        memory[memory[i + 3]] = prod;
        break;
      case 2:
        memory[memory[i + 3] + positional] = prod;
        break;
      }

      i += 4;
      break;
    case 3:
      if(par1 == 0) {
        memory[memory[i + 1]] = input;
      } else {
        memory[memory[i + 1] + positional] = input;
      }

      i += 2;
      break;
    case 4:
      return getParameter(par1, i + 1, memory, positional);
      i += 2;
      break;
    case 5:
      if(getParameter(par1, i + 1, memory, positional)) {
        i = getParameter(par2, i + 2, memory, positional);
      } else {
        i += 3;
      }
      break;
    case 6:
      if(getParameter(par1, i + 1, memory, positional) == 0) {
        i = getParameter(par2, i + 2, memory, positional);
      } else {
        i += 3;
      }
      break;
    case 7:
      if(getParameter(par1, i + 1, memory, positional) < getParameter(par2, i + 2, memory, positional)) {
        switch(par3) {
        case 0:
        case 1:
          memory[memory[i + 3]] = 1;
          break;
        case 2:
          memory[memory[i + 3] + positional] = 1;
          break;
        }
      } else {
        switch(par3) {
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
      if(getParameter(par1, i + 1, memory, positional) == getParameter(par2, i + 2, memory, positional)) {
        switch(par3) {
        case 0:
        case 1:
          memory[memory[i + 3]] = 1;
          break;
        case 2:
          memory[memory[i + 3] + positional] = 1;
          break;
        }
      } else {
        switch(par3) {
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
    default:
      printf("Error occurred: got instruction %lli at %lli\n", memory[i], i);
      return 0;
    }
  }
}

int main(int argc, char **argv) {
  if (argc != 2) {
    printf("Invalid number of arguments. Please enter the name of the input file as an argument.\n");
    return 1;
  }

  FILE *curfile = fopen(argv[1], "r");
  if(curfile == NULL) { printf("Unable to find file.\n"); return 2; }

  long long *intcode1 = malloc(10000 * sizeof(long long));
  long long *intcode2 = malloc(10000 * sizeof(long long));

  char *instring = malloc(4000 * sizeof(char));
  char *token = malloc(20 * sizeof(char));

  fscanf(curfile, "%s", instring);

  int i = 0;
  while (token = strsep(&instring, ",")) {
      intcode1[i] = atoll(token);
      intcode2[i++] = intcode1[i];
    }

  free(instring);
  free(token);

  printf("Part 1 solution: %lli\nPart 2 solution: %lli\n", runIntComp(intcode1, 1), runIntComp(intcode2, 2));

  free(intcode1);
  free(intcode2);

  return 0;
}
