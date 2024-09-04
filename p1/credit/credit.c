#include <math.h>
#include <stdio.h>

int count_digits(long long num);

int main(void) {
  int checksum = 0;
  long long visa;
  int firstDigit;
  int secondDigit;

  printf("Visa number: ");
  scanf_s("%lld", &visa);

  int digitCount = count_digits(visa);

  // calculate checksum

  for (int i = 0; i < digitCount; i++) {
    long long truncNum = visa / pow(10, i);
    int currDigit = truncNum % 10;

    if (i == digitCount - 1) {
      firstDigit = currDigit;
    } else if (i == digitCount - 2) {
      secondDigit = currDigit;
    }

    if (i % 2 != 0) {
      int currSum = currDigit * 2;

      if (currSum > 9) {
        checksum = checksum + currSum / 10 + currSum % 10;
      } else {
        checksum = checksum + currSum;
      }
    } else {
      checksum = checksum + currDigit;
    }
  }

  if (checksum % 10 == 0) {
    if (digitCount == 15 && firstDigit == 3 &&
        (secondDigit == 4 || secondDigit == 7)) {
      printf("AMEX\n");
    } else if (digitCount == 16 && firstDigit == 5 && secondDigit > 0 &&
               secondDigit < 6) {
      printf("MASTERCARD\n");
    } else if ((digitCount == 16 || digitCount == 13) && firstDigit == 4) {
      printf("VISA\n");
    } else {
      printf("INVALID\n");
    }
  } else {
    printf("INVALID\n");
  }
}

int count_digits(long long num) {
  int count = 0;
  while (num != 0) {
    num = num / 10;
    count++;
  }
  return count;
}
