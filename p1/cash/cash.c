#include <stdio.h>

void cash(int coin, int *change, int *count);

int main(void) {
  int change;
  int count = 0;

  // not worrying about error checking user input
  printf("Change owed: ");
  scanf_s("%d", &change);

  // array is next week
  cash(25, &change, &count);
  cash(10, &change, &count);
  cash(5, &change, &count);
  cash(1, &change, &count);

  printf("%d", count);
}

void cash(int coin, int *change, int *count) {
  if (*change >= coin) {
    *count = *count + *change / coin;
    *change = *change % coin;
  }
}
