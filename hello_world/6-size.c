#include <stdio.h>

int main(void)

{
  char c = 'A';
  int i = 42;
  float f = 3.14f;
  double d = 3.14159;

  printf("Size of an int: %zu\n", sizeof(int));
  printf("Size of a char: %c\n", sizeof(char));
  printf("Size of a float: %f\n", sizeof(float));
  printf("Size of a long int: %d\n", sizeof(char));
}
