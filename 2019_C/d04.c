#include <stdio.h>
#include <stdlib.h>

char validate_int_part1(int val) {
  char *val_s = malloc(10 * sizeof(char));
  sprintf(val_s, "%d", val);

  char reqs = 0;

  for(int i = 1; i < 6; i++) {
    if(val_s[i - 1] == val_s[i]) {
      reqs = reqs | 1;
    }
    else if(val_s[i - 1] > val_s[i]) {
      reqs = reqs | 2;
    }
  }

  if(reqs == 1) {
    return 1;
  }
  return 0;
}


char validate_int_part2(int val) {
  char *val_s = malloc(10 * sizeof(char));
  sprintf(val_s, "%d", val);

  char reqs = 0;

  for(int i = 1; i < 6; i++) {
    if(val_s[i - 1] > val_s[i]) {
      reqs = reqs | 2;
    }
  }

  for(int i = 1; i < 6; i++) {
    if(val_s[i - 1] == val_s[i]) {
      if(val_s[i + 1] == val_s[i]) {
        while(val_s[i - 1] == val_s[i]) { i++; }
      }
      else {
        reqs = reqs | 1;
      }
    }
  }
    
  if(reqs == 1) {
    return 1;
  }
  return 0;
}


int main(int argc, char **argv) {
  if(argc != 3) {
    printf("Invalid number of arguments. Please enter the starting and ending numbers as arguments.\n");
    return 1;
  }

  int min = atoi(argv[1]);
  int max = atoi(argv[2]);

  int part1_count = 0;
  int part2_count = 0;
  
  for(int i = min; i <= max; i++) {
    part1_count += validate_int_part1(i);
    part2_count += validate_int_part2(i);
  }

  printf("Part 1 solution: %i\nPart 2 solution: %i\n", part1_count, part2_count);
}
