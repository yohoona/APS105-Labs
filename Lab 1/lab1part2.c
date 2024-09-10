#include <stdio.h>

int main(void) {
  double fahrenheit, celsius;
  printf("Enter the thermostat temperature: ");
  scanf("%lf", &fahrenheit);
  celsius = (fahrenheit - 32) * 5 / 9;
  printf("The temperature in Celsius is: %0.1lf", celsius);

  double standard = 22.0 * 9 / 5 + 32;
  double delta = fahrenheit - standard;

  printf("\n\nYou are %.1lf degrees Fahrenheit away from a nice 22 degrees Celsius.", delta);

  return 0;
}