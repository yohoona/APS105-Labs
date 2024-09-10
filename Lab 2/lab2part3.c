#include <stdio.h>
#include <math.h>

int main() {
    const double kconst = 8.9875 * pow(10, 9);

    double q1, q2;
    char unit1, unit2, unit3, unit4;
    printf("Enter the value of the two charges separated by a space: ");
    scanf("%lf%c%c" "%lf%c%c", &q1, &unit1, &unit2, &q2, &unit3, &unit4);

    if (unit1 == 'n' && unit2 == 'C') {
        q1 *= pow(10, -9);
    } else {
        q1 *= pow(10, -6);
    }

    if (unit3 == 'n' && unit4 == 'C') {
        q2 *= pow(10, -9);
    } else {
        q2 *= pow(10, -6);
    }

// input radius 
    double radius;
    printf("Enter distance between charges in metres: ");
    scanf("%lf", &radius);

// calculations
    double electroForce = kconst * fabs(q1 * q2) / pow(radius, 2.0);

// output
    if (electroForce < 0.000001) {
        electroForce *= pow(10, 9);
        printf("The force between charges is %.2lfnN (less than 1uN)", electroForce);

    } else if (electroForce < 0.001) {
        electroForce *= pow(10, 6);
        printf("The force between charges is %.2lfuN (less than 1mN)", electroForce);

    } else if (electroForce < 1) {
        electroForce *= pow(10, 3);
        printf("The force between charges is %.2lfmN (less than 1N)", electroForce);
    
    } else if (electroForce > 1) {
        printf("The force between charges is %.2lfN (1N or greater)", electroForce);
    }

    return 0;

}