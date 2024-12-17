#include <stdio.h>
#include <stdlib.h>

void runIntComp(long long *memory);
long long getParameter(long long mode, long long pos, long long *memory, long long positional);

#define getFile(name) char *__file = name;
#define openFile FILE *curfile = fopen(__file, "r"); \
    if(curfile == NULL) { printf("File not found."); return; }
