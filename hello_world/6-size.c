#include <stdio.h>

int main(void)

{
  char c = 'A';
  int i = '42';
  float f = 3.14f;
  double d = 3.14159;

  printf("Size of a char: %c byte(s)\n", sizeof(char));
  printf("Size of an int: %zu byte(s)\n", sizeof(int));
  printf("Size of a long int: %d byte(s)\n", sizeof(char));
  printf("Size of a long long int: %d byte(s)\n", sizeof(char));
  printf("Size of a float: %f byte(s)\n", sizeof(float));
  return (0);
}
