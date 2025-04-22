#include <stdio.h>
#include <stdlib.h>

#define PIXEL_WIDTH 25
#define PIXEL_HEIGHT 6
#define LAYER_COUNT 100

int main(int argc, char **argv) {
  if (argc != 2) {
    printf("Invalid number of arguments. Please enter the name of the input file as an argument.\n");
    return 1;
  }

  FILE *curfile = fopen(argv[1], "r");
  if(curfile == NULL) { printf("Unable to find file.\n"); return 2; }

  char *instring = malloc((PIXEL_WIDTH * PIXEL_HEIGHT * LAYER_COUNT + 1) * sizeof(char));

  fscanf(curfile, "%s\n", instring);

  unsigned int leastzeros = -1;
  unsigned int leastlayer = -1;

  for(int i = 0; i < LAYER_COUNT; i++) {
    int curzeros = 0;
    for(int j = 0; j < (PIXEL_WIDTH * PIXEL_HEIGHT); j++) {
      if(instring[(i * (PIXEL_WIDTH * PIXEL_HEIGHT)) + j] == '0') { curzeros++; }
    }

    if(curzeros < leastzeros) {
      leastzeros = curzeros;
      leastlayer = i;
    }
  }
    
  int onedigs = 0;
  int twodigs = 0;

  for(int i = 0; i < (PIXEL_WIDTH * PIXEL_HEIGHT); i++) {
    if(instring[(leastlayer * PIXEL_WIDTH * PIXEL_HEIGHT) + i] == '1') { onedigs++; }
    else if(instring[(leastlayer * PIXEL_WIDTH * PIXEL_HEIGHT) + i] == '2') { twodigs++; }
  }

  printf("Part 1 solution: %i\n", onedigs * twodigs);
  printf("Part 2 image follows:\n");

  for(int i = 0; i < PIXEL_HEIGHT; i++) {
    for(int j = 0; j < PIXEL_WIDTH; j++) {
      int layer = 0;
      while(instring[(layer * PIXEL_WIDTH * PIXEL_HEIGHT) + (i * PIXEL_WIDTH) + j] == '2') { layer++; }
      if(instring[(layer * PIXEL_WIDTH * PIXEL_HEIGHT) + (i * PIXEL_WIDTH) + j] == '0') {
        printf(" ");
      } else {
        printf("#");
      }
    }
    printf("\n");
  }
}
