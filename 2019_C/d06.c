#include <stdio.h>
#include <stdlib.h>

#define LINE_COUNT 2500
#define YOU_PATH_SIZE 500

int main(int argc, char **argv) {
  if (argc != 2) {
    printf("Invalid number of arguments. Please enter the name of the input file as an argument.\n");
    return 1;
  }

  FILE *curfile = fopen(argv[1], "r");
  if(curfile == NULL) { printf("Unable to find file.\n"); return 2; }

  // 8 chars per line
  char *inarr = malloc(LINE_COUNT * 8 * sizeof(char));

  for(int i = 0; i < LINE_COUNT; i++) {
    fscanf(curfile, "%s", inarr + (i * 8));
  }

  // TODO: integrate part 1 and part 2 solutions together

  int sum = 0;
  int curlevel = 0;
  int levelsize;

  char *queuemem = malloc(LINE_COUNT * 3 * sizeof(char));
  char *queueb = queuemem;
  char *queuet = queuemem + 3;
    
  queueb[0] = 'C';
  queueb[1] = 'O';
  queueb[2] = 'M';

  while(queueb != queuet) {
    levelsize = (queuet - queueb) / 3;
    for(int i = 0; i < levelsize; i++) {
      sum += curlevel;
            
      for(int j = 0; j < LINE_COUNT; j++) {
        if((queueb[0] == inarr[j * 8]) && (queueb[1] == inarr[(j * 8) + 1]) && (queueb[2] == inarr[(j * 8) + 2])) {
          queuet[0] = inarr[(j * 8) + 4];
          queuet[1] = inarr[(j * 8) + 5];
          queuet[2] = inarr[(j * 8) + 6];

          queuet += 3;
        }
      }

      queueb += 3;
    }
    curlevel++;
  }

  printf("Part 1 solution: %i\n", sum);

  free(queuemem);

  char *loc = malloc(4 * sizeof(char));

  char *youpath = malloc(500 * 3 * sizeof(char));
  char *add = youpath;
  loc[0] = 'Y';
  loc[1] = 'O';
  loc[2] = 'U';

  while((loc[0] != 'C') || (loc[1] != 'O') || (loc[2] != 'M')) {
    for(int i = 0; i < LINE_COUNT; i ++) {
      if((loc[0] == inarr[(i * 8) + 4]) && (loc[1] == inarr[(i * 8) + 5]) && (loc[2] == inarr[(i * 8) + 6])) {
        loc[0] = inarr[i * 8];
        loc[1] = inarr[(i * 8) + 1];
        loc[2] = inarr[(i * 8) + 2];

        add[0] = loc[0];
        add[1] = loc[1];
        add[2] = loc[2];

        add += 3;
      }
    }
  }

  char *sanpath = malloc(YOU_PATH_SIZE * 3 * sizeof(char));
  add = sanpath;
  loc[0] = 'S';
  loc[1] = 'A';
  loc[2] = 'N';

  while((loc[0] != 'C') || (loc[1] != 'O') || (loc[2] != 'M')) {
    for(int i = 0; i < LINE_COUNT; i ++) {
      if((loc[0] == inarr[(i * 8) + 4]) && (loc[1] == inarr[(i * 8) + 5]) && (loc[2] == inarr[(i * 8) + 6])) {
        loc[0] = inarr[i * 8];
        loc[1] = inarr[(i * 8) + 1];
        loc[2] = inarr[(i * 8) + 2];

        add[0] = loc[0];
        add[1] = loc[1];
        add[2] = loc[2];

        add += 3;
      }
    }
  }

  for(int i = 0; i < YOU_PATH_SIZE; i++) {
    for(int j = 0; j < YOU_PATH_SIZE; j++) {
      if((youpath[(i * 3)] == sanpath[(j * 3)]) && (youpath[(i * 3) + 1] == sanpath[(j * 3) + 1]) && (youpath[(i * 3) + 2] == sanpath[(j * 3) + 2])) {
        printf("Part 2 solution: %i\n", i + j);
        return 0;
      }
    }
  }

  free(inarr);
}
