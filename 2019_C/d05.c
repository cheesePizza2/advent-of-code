#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INTCOMP_SIZE 3000

long long getValue(long long mode, long long pos, long long *memory) {
  switch(mode) {
  case 0:
    return memory[memory[pos]];
  case 1:
    return memory[pos];
  default:
    printf("Error occurred: got parameter %lli at %lli\n", mode, pos);
    return 0;
  }
}

long long runIntComp(long long *memory, long long input) {
  long long last_output = 0;
  for(long long i = 0; ; ) {
    long long intval = memory[i];
    long long opcode = intval % 100;

    long long par1 = (intval % 1000) / 100;
    long long par2 = (intval % 10000) / 1000;
    long long par3 = (intval % 100000) / 10000;

    switch(opcode) {
    case 1:
      memory[memory[i + 3]] = getValue(par1, i + 1, memory) + getValue(par2, i + 2, memory);
      i += 4;
      break;
    case 2:
      memory[memory[i + 3]] = getValue(par1, i + 1, memory) * getValue(par2, i + 2, memory);
      i += 4;
      break;
    case 3:
      // only 1 input value, so lets handle it inside the program
      memory[memory[i + 1]] = input;
      i += 2;
      break;
    case 4:
      last_output = memory[memory[i + 1]];
      i += 2;
      break;
    case 5:
      if(getValue(par1, i + 1, memory)) {
        i = getValue(par2, i + 2, memory);
      } else {
        i += 3;
      }
      break;
    case 6:
      if(getValue(par1, i + 1, memory) == 0) {
        i = getValue(par2, i + 2, memory);
      } else {
        i += 3;
      }
      break;
    case 7:
      if(getValue(par1, i + 1, memory) < getValue(par2, i + 2, memory)) {
        memory[memory[i + 3]] = 1;
      } else {
        memory[memory[i + 3]] = 0;
      }
      i += 4;
      break;
    case 8:
      if(getValue(par1, i + 1, memory) == getValue(par2, i + 2, memory)) {
        memory[memory[i + 3]] = 1;
      } else {
        memory[memory[i + 3]] = 0;
      }
      i += 4;
      break;
    case 99:
      return last_output;
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

  long long *part1code = malloc(INTCOMP_SIZE * sizeof(long long));
  long long *part2code = malloc(INTCOMP_SIZE * sizeof(long long));

  char *instring = malloc(INTCOMP_SIZE * sizeof(char));
  char *token = malloc(8 * sizeof(char));

  fscanf(curfile, "%s", instring);

  int i = 0;
  while (token = strsep(&instring, ",")) {
    part1code[i] = atoll(token);
    part2code[i] = part1code[i];
    i++;
  }

  free(instring);
  free(token);

  printf("Part 1 solution: %lli\nPart 2 Solution: %lli\n", runIntComp(part1code, 1), runIntComp(part2code, 5));

  free(part1code);
  free(part2code);
}
