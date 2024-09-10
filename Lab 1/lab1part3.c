#include <stdio.h>
#include <math.h>
#define M_PI 3.14159265358979323846

int main(void) {
//declare circumference, get input of circumference from user
  double inputCirc;
  printf("Circumference (km) of planet? ");
  scanf("%lf", &inputCirc);
//declare acceleration, get input of acceleration from user
  double inputAccel;
  printf("Acceleration due to gravity (m/s^2) on planet? ");
  scanf("%lf", &inputAccel);

//calculations and any required unit conversions are completed here
    double outputRadius = inputCirc * 1000 / (2 * M_PI);
    double r2 = outputRadius * outputRadius;
    double exp1 = pow(10.0, (-11.0));
    double gravconst = 6.6726 * exp1;
    double exp2 = pow(10.0, 21.0);
    double outputMass = inputAccel * r2 / (exp2 * gravconst);
    double escape = sqrtf(inputAccel * 2.0 * outputRadius);
    double outputEscapevel = escape / 1000.0;

//display radius, mass, and escape velocity of planet to user
  printf("\nCalculating the escape velocity...");
  printf("\nPlanet radius: %.1lf km", outputRadius / 1000);
  printf("\nPlanet mass: %.1lf x 10^21 kg", outputMass);
  printf("\nEscape velocity: %.1lf km/s", outputEscapevel);
}