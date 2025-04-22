#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define GRID_SIZE 25000

int main(int argc, char **argv) {
  if (argc != 2){
    printf("Invalid number of arguments. Please enter the name of the input file as an argument.\n");
    return 1;
  }

  FILE *curfile = fopen(argv[1], "r");
  if(curfile == NULL) { printf("Unable to find file.\n"); return 2; }

  char *infirstring = malloc(2000 * sizeof(char));
  char *insecstring = malloc(2000 * sizeof(char));

  fscanf(curfile, "%s", infirstring);
  fscanf(curfile, "%s", insecstring);

  char *token = malloc(5 * sizeof(char));

  unsigned long *grid = malloc(GRID_SIZE * GRID_SIZE * sizeof(unsigned long));

  int curx = (GRID_SIZE / 2) - 1;
  int cury = (GRID_SIZE / 2) - 1;

  unsigned long step = 0;

  while (token = strsep(&infirstring, ",")) {
    int val = atoi(token+1);

    for(int i = 0; i < val; i++) {
      step++;
      switch(token[0]) {
      case 'R':
        curx++;
        break;
      case 'L':
        curx--;
        break;
      case 'U':
        cury++;
        break;
      case 'D':
        cury--;
        break;
      }
      if(grid[(GRID_SIZE * curx) + cury] == 0) {
        grid[(GRID_SIZE * curx) + cury] = step;
      }
    }
  }

  free(infirstring);
  curx = (GRID_SIZE / 2) - 1;
  cury = (GRID_SIZE / 2) - 1;
  step = 0;

  unsigned int cur_min_inter = ~0;
  unsigned long cur_min_steps = ~0;

  while (token = strsep(&insecstring, ",")) {
    int val = atoi(token+1);

    for(int i = 0; i < val; i++) {
      step++;
      switch(token[0]) {
      case 'R':
        curx++;
        break;
      case 'L':
        curx--;
        break;
      case 'U':
        cury++;
        break;
      case 'D':
        cury--;
        break;
      }

      if(grid[(GRID_SIZE * curx) + cury]) {
        int distance = abs(curx - ((GRID_SIZE / 2) - 1)) + abs(cury - ((GRID_SIZE / 2) - 1));
        cur_min_inter = (distance < cur_min_inter) ? distance : cur_min_inter;

        int steps = step + grid[(GRID_SIZE * curx) + cury];
        cur_min_steps = (steps < cur_min_steps) ? steps : cur_min_steps;
      }
    }
  }

  printf("Part 1 solution: %i\nPart 2 solution: %li\n", cur_min_inter, cur_min_steps);
    
  free(token);
  free(insecstring);
  free(grid);

  return 0;
}
