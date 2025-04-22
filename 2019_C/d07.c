#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INTCOMP_SIZE 200

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

long long runAmplifier(long long *memory, long long input, long long setting) {
  int input_count = 0;
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
      switch(input_count) {
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

      input_count++;
      i += 2;
      break;
    case 4:
      return getValue(par1, i + 1, memory);
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
    default:
      printf("Error occurred: got instruction %lli at %lli\n", memory[i], i);
      return 0;
    }
  }
}

int checkPhase(long long *originalcode, int *phase) {
  int buffer = 0;
  long long *intcode = malloc(INTCOMP_SIZE * sizeof(long long));
  for(int i = 0; i < 5; i++) {
    for(int i = 0; i < INTCOMP_SIZE; i++) {
      intcode[i] = originalcode[i];
    }
    
    buffer = runAmplifier(intcode, buffer, phase[i]);
  }
  return buffer;
}

int main(int argc, char **argv) {
  if (argc != 2) {
    printf("Invalid number of arguments. Please enter the name of the input file as an argument.\n");
    return 1;
  }

  FILE *curfile = fopen(argv[1], "r");
  if(curfile == NULL) { printf("Unable to find file.\n"); return 2; }

  long long *intcode = malloc(INTCOMP_SIZE * sizeof(long long));

  char *instring = malloc(INTCOMP_SIZE * 8 * sizeof(char));
  char *token = malloc(8 * sizeof(char));

  fscanf(curfile, "%s", instring);

  int i = 0;
  while (token = strsep(&instring, ",")) {
    intcode[i++] = atoll(token);
  }

  free(instring);
  free(token);

  int maxsol = 0;
  // TODO: inefficient, needs optimization
  for(int a = 0; a < 5; a++) {
    for(int b = 0; b < 5; b++) {
      if(b == a) { continue; }
      
      for(int c = 0; c < 5; c++) {
        if((c == a) || (c == b)) { continue; }
        
        for(int d = 0; d < 5; d++) {
          if((d == a) || (d == b) || (d == c)) { continue; }

          int e = 10 - a - b - c - d;

          int phase[5] = {a, b, c, d, e};
          int temp = checkPhase(intcode, phase);

          maxsol = (temp > maxsol) ? temp : maxsol;
        }
      }
    }
  }

  printf("Part 1 solution: %i\n", maxsol);

  // TODO: part 2 solution
  
  free(intcode);
}
