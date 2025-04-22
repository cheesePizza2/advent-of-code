#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INTCOMP_SIZE 200

void runIntComp(long long *memory) {
  for(long long i = 0; ; ) {
    long long opcode = memory[i];

    switch(opcode) {
    case 1:
      memory[memory[i + 3]] = memory[memory[i + 1]] + memory[memory[i + 2]];
      i += 4;
      break;
    case 2:
      memory[memory[i + 3]] = memory[memory[i + 1]] * memory[memory[i + 2]];
      i += 4;
      break;
    case 99:
      return;
    default:
      printf("Error occurred: got instruction %lli at %lli\n", memory[i], i);
      return;
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

  long long *intcode = malloc(INTCOMP_SIZE * sizeof(long long));
  long long *backup = malloc(INTCOMP_SIZE * sizeof(long long));

  char *instring = malloc(INTCOMP_SIZE * sizeof(char));
  char *token = malloc(5 * sizeof(char));

  fscanf(curfile, "%s", instring);

  int i = 0;
  while (token = strsep(&instring, ",")) {
    intcode[i] = atoll(token);
    backup[i] = intcode[i];
    i++;
  }

  free(instring);
  free(token);

  // calc part 1 solution
  intcode[1] = 12;
  intcode[2] = 2;

  runIntComp(intcode);

  printf("Part 1 solution: %lli\n", intcode[0]);

  // calc part 2 solution

  long long noun = 0;
  long long verb = 0;
  
  while(1) {
    for(int i = 0; i < INTCOMP_SIZE; i++) {
      intcode[i] = backup[i];
    }
    
    intcode[1] = noun;
    intcode[2] = verb;

    runIntComp(intcode);

    // i think this number is common to everyone?
    if(intcode[0] == 19690720) {
      printf("Part 2 solution: %lli\n", (100 * noun) + verb);

      free(intcode);
      free(backup);
      return 0;
    }

    if(verb == 99) {
      noun++;
      verb = 0;
    }
    else {
      verb++;
    }
  }
}
