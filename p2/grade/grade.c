#include <math.h>
#include <stdio.h>
#include <string.h>

int calculate_grade(float l, float s);
int is_horizontal_space(char c);
int is_letter(char c);
int is_endmark(char c);

int main(void) {
  char text[2048];
  const int INPUT_SIZE = sizeof(text);

  printf("Text: ");
  fgets(text, INPUT_SIZE, stdin);
  text[strcspn(text, "\n")] = 0; // replace the newline character if it exists

  int wordCount = 0;
  int letterCount = 0;
  int sentenceCount = 0;

  for (int i = 0; i < strlen(text); i++) {
    char currChar = text[i];
    if (is_letter(currChar)) {
      letterCount++;

      if (i == 0 || is_horizontal_space(text[i - 1])) {
        wordCount++;
      }
    } else if (is_endmark(currChar)) {
      if (i > 0 && !is_endmark(text[i - 1])) {
        sentenceCount++;
      }
    }

    // printf("'%c':%i; wc: %i; lc: %i; sc: %i\n", currChar, currChar,
    // wordCount, letterCount, sentenceCount);
  }

  // printf("Words: %i; Letters: %i; Sentences: %i\n", wordCount, letterCount,
  // sentenceCount);

  float lettersPer100Words = (letterCount / (float)wordCount) * 100;
  float sentencesPer100Words = (sentenceCount / (float)wordCount) * 100;

  // printf("Letters/100: %f; Sentences/100: %f\n", lettersPer100Words,
  // sentencesPer100Words);

  printf("Grade %i\n",
         calculate_grade(lettersPer100Words, sentencesPer100Words));
}

int calculate_grade(float l, float s) {
  int index = round(0.0588 * l - 0.296 * s - 15.8);

  if (index < 0) {
    return 0;
  }

  return index;
}

int is_horizontal_space(char c) {
  if (c == 9 || c == 32) {
    return 1;
  } else {
    return 0;
  }
}

int is_letter(char c) {
  if ((65 <= c && c <= 90) || (97 <= c && c <= 122) || (48 <= c && c <= 57)) {
    return 1;
  } else {
    return 0;
  }
}

int is_endmark(char c) {
  if (c == 33 || c == 46 || c == 63) {
    return 1;
  } else {
    return 0;
  }
}
