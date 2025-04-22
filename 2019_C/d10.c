#include <stdio.h>
#include <stdlib.h>

#define MAP_SIZE 36

int gcd(int a, int b) {
  if (a == 0) { return b; }
  if (b == 0) { return a; }
  if (a == b) { return a; }

  return (a > b) ? gcd(b, a % b) : gcd(a, b % a);
}

int checkAstView(int x, int y, char *map) {
  int sum = 0;

  for(int i = 0; i < MAP_SIZE; i++) {
    for(int j = 0; j < MAP_SIZE; j++) {
      if((i == x) && (j == y)) { continue; }
      if(map[i + (j * MAP_SIZE)] == '.') { continue; }

      int difx = i - x;
      int dify = j - y;

      int cd = gcd((difx > -1) ? difx : -difx, (dify > -1) ? dify : -dify);

      if (cd == 1) { sum++; continue; } // line does not pass over any spaces

      difx /= cd;
      dify /= cd;

      int step = 1;
      char col = 0; // bool flag

      while(step < cd) {
        if(map[(x + (difx * step)) + ((y + (dify * step)) * 36)] == '#') { col = 1; }

        step++;
      }
      if(col == 0) { sum++; }
    }
  }

  return sum;
}


int main(int argc, char **argv) {
  if (argc != 2) {
    printf("Invalid number of arguments. Please enter the name of the input file as an argument.\n");
    return 1;
  }

  FILE *curfile = fopen(argv[1], "r");
  if(curfile == NULL) { printf("Unable to find file.\n"); return 2; }

  char *instring = malloc(MAP_SIZE * MAP_SIZE * sizeof(char));

  for(int y = 0; y < MAP_SIZE; y++) {
    for(int x = 0; x < MAP_SIZE; x++) {
      instring[(y * MAP_SIZE) + x] = fgetc(curfile);
    }
    fgetc(curfile);
  }

  int bestview = 0;

  for(int y = 0; y < MAP_SIZE; y++) {
    for(int x = 0; x < MAP_SIZE; x++) {
      if(instring[(y * MAP_SIZE) + x] == '.') { continue; }

      int cur = checkAstView(x, y, instring);
      bestview = (cur > bestview) ? cur : bestview;
    }
  }

  printf("Part 1 solution: %i\n", bestview);
}
