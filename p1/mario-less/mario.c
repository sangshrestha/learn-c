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

  for (int height = size; height > 0; height--) {
    // print blocks on the current line
    for (int col = 1; col <= size; col++) {
      if (col >= height) {
        printf("#");
      } else {
        printf(" ");
      }
    }
    printf("\n");
  }
}
