#include <stdio.h>
#include <math.h>

int main () {
    // inputs
    int numberIntervals;
    double lowerBound, upperBound;
    double riemannSum = 0;
    double subintervalNumber = 1;

    while (numberIntervals >= 1) {
        riemannSum = 0;
        subintervalNumber = 1;
        
        printf("Please enter the number of rectangles (n): ");
        scanf("%d", &numberIntervals);
        
        if (numberIntervals < 1) {
        
            printf("Exiting.");
            return 0;
        
        } else {

        printf("Please enter the interval of integration (a b): ");
        scanf("%lf %lf", &lowerBound, &upperBound);

        // if you fail to meet the 2nd condition (lower bound < upper bound), the program should ask until this condition is met; thus, use a loop 
        while (lowerBound > upperBound) {
            printf("Invalid interval!");
            printf("\n\nPlease enter the interval of integration (a b): ");
            scanf("%lf %lf", &lowerBound, &upperBound);
        }

        do {
            double deltaX = (upperBound - lowerBound) / numberIntervals;
            double xKstar = lowerBound + (subintervalNumber - 0.5) * deltaX;
            double innerFunc = (double) -1 * pow(xKstar, 2);
            double subintervalArea = deltaX * exp(innerFunc);
            riemannSum += subintervalArea;
            subintervalNumber++;
        } while (subintervalNumber <= numberIntervals);

        printf("The integral of e^-x^2 on [%.5lf, %.5lf] with n = %d is: %.5lf\n\n", lowerBound, upperBound, numberIntervals, riemannSum);
        
        }
    
    }

        return 0;

    }