#include "main.h"
#include <stdio.h>


/**
 * print_sign - prints +, 0 or -
 * @n: The number has to either be positive,
 * negative or zero
 * Return: 1 if n is positive, 0 if n is zero, -1 if n is negative
 */
int print_sign(int n) {
  if (n > 0) {
    putchar('+');
    return (1);
  } else if (n < 0) {
    putchar('-');
    return (-1);
  } else {
    putchar('0');
    return (0);
  }
}