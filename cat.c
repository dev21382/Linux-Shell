#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {

  FILE *fptr;
  char c;

  if (argc == 1) // Invalid input
  {
    printf("Invalid input format, follow : cat [filename]");
  }

  else if (argc == 3 && strcmp(argv[1], ">") == 0) // In write mode here
  {
    fptr = fopen(argv[2], "w");
    scanf("%c", &c);
    while (c != '.') {
      fprintf(fptr, "%c", c);
      scanf("%c", &c);
    }
    fclose(fptr);
  }

  else if (argc == 3 && strcmp(argv[1], ">>") == 0) // In append mode here
  {
    fptr = fopen(argv[2], "a");
    scanf("%c", &c);
    while (c != '.') {
      fprintf(fptr, "%c", c);
      scanf("%c", &c);
    }
    fclose(fptr);
  }

  else if (argc == 2) // In read mode here
  {
    fptr = fopen(argv[1], "r");
    c = fgetc(fptr);
    while (c != EOF) {
      printf("%c", c);
      c = fgetc(fptr);
    }
    fclose(fptr);
  }

  return 0;
}
