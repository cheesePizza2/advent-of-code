#include <stdio.h>
#include <stdlib.h>

int part1calc(int x) {
  return (x / 3) - 2;
}

// POSSIBLE IMPROVEMENT: tail call recursion
int part2calc(int x) {
  int curfuel = (x / 3) - 2;

  if(curfuel > 0) {
    return curfuel + part2calc(curfuel);
  }
  
  return 0;
}


int main(int argc, char **argv) {
  if (argc != 2){
    printf("Invalid number of arguments. Please enter the name of the input file as an argument.\n");
    return 1;
  }

  FILE *curfile = fopen(argv[1], "r");
  if(curfile == NULL) { printf("Unable to find file.\n"); return 2; }

  char curstring[50];
  int part1 = 0;
  int part2 = 0;

  while(fscanf(curfile, "%s\n", curstring) != EOF) {
    int curint = atoi(curstring);
    part1 += part1calc(curint);
    part2 += part2calc(curint);
  }

  printf("Part 1 solution: %i\nPart 2 solution: %i\n", part1, part2);

  return 0;
}
