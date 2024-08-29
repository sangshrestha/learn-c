#include <stdio.h>

int main(void) {
  int size;

  printf("Enter height: ");
  int res = scanf_s("%d", &size);

  while (res != 1 || size < 1) {
    // consume the existing inputs in buffer
    char buffer[20];
    fgets(buffer, sizeof(buffer), stdin);

    printf("Enter height: ");
    res = scanf_s("%d", &size);
  }

  for (int row = 0; row < size; row++) {
    // print blocks before the gap
    for (int col = 0; col < size; col++) {
      if (col >= size - row - 1) {
        printf("#");
      } else {
        printf(" ");
      }
    }

    // print gaps
    for (int i = 0; i < 2; i++) {
      printf("  ");
    }

    // print blocks after the gap
    for (int col = 0; col <= row; col++) {
      printf("#");
    }
    printf("\n");
  }
}
