#include <stdio.h>

int main(void) {
  char name[20];

  printf("What's your name? ");
  scanf_s("%s", name);
  printf("Hello, %s\n", name);
}
