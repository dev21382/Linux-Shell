#include <fcntl.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

void generate_string_matrix(char *ptr) {
  char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
  for (int i = 0; i < 50; i++) {
    for (int j = 0; j < 7; j++) {
      size_t index = (double)rand() / RAND_MAX * (sizeof charset - 1);
      *((ptr + i * 10) + j) = charset[index];
    }
    if (i <= 9) {
      *((ptr + i * 10) + 7) = '0';
      *((ptr + i * 10) + 8) = (char)(i + 48);
    } else {
      *((ptr + i * 10) + 7) = (char)((i / 10) + 48);
      *((ptr + i * 10) + 8) = (char)((i % 10) + 48);
    }
    *((ptr + i * 10) + 9) = '\0';
  }
  return;
}

int main() {
  int res;
  char string_matrix[50][10];
  generate_string_matrix(&string_matrix);
  mkfifo("fifo1", 0666);
  char str1[1000];
  char *ptr1 = NULL;
  int index_next = 0;
  while (index_next < 50) {
    ptr1 = &string_matrix;
    res = open("fifo1", O_WRONLY);
    write(res, (ptr1 + index_next * 10), 10);
    write(res, (ptr1 + (index_next + 1) * 10), 10);
    write(res, (ptr1 + (index_next + 2) * 10), 10);
    write(res, (ptr1 + (index_next + 3) * 10), 10);
    write(res, (ptr1 + (index_next + 4) * 10), 10);
    close(res);
    res = open("fifo1", O_RDONLY);
    read(res, str1,strlen(str1));
    index_next = atoi(str1) + 1;
    printf("Sent by the receiver program: %s\n", str1);
    close(res);
  }
  unlink("fifo1");
  return 0;
}