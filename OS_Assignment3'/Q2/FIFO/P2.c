#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
  int fd1;
  mkfifo("fifo1", 0666);
  char str1[1000] = {0};
  char *str2 = malloc(1000);
  for (int i = 0; i < 50; i++) {
    fd1 = open("fifo1", O_RDONLY);
    read(fd1, str1, 1000);
    printf("Sent to the sender : %d\t", i);
    printf("%s\n", str1);
    close(fd1);
    int len = strlen(str1);
    int index1 = ((((int)str1[7]) - 48) * 10) + (((int)str1[8]) - 48);
    if (i % 5 == 4) {
      fd1 = open("fifo1", O_WRONLY);
      sprintf(str2, "%d", index1);
      write(fd1, str2, strlen(str2) + 1);
      close(fd1);
    }
    i++;
  }
  unlink("fifo1");
  return 0;
}

