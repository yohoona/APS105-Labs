#include <stdio.h>
#include <math.h>

int main() {
    // inputs
    int numberIntervals;
    double lowerBound, upperBound;
    printf("Please enter the number of rectangles (n): ");
    scanf("%d", &numberIntervals);

    // since the program exits if the first condition (n<1) fails, no need to use a loop
    if (numberIntervals < 1) {
        printf("Exiting.");
    } else {
        printf("Please enter the interval of integration (a b): ");
        scanf("%lf %lf", &lowerBound, &upperBound);

        // if you fail to meet the 2nd condition (lower bound < upper bound), the program should ask until this condition is met; thus, use a loop 
        while (lowerBound > upperBound) {
            printf("\nInvalid Interval!");
            printf("\nPlease enter the interval of integration (a b): ");
            scanf("%lf %lf", &lowerBound, &upperBound);
        }
    // calculations
        // 1. initialize total area = 0, subinterval number = 1
        // 2. divide interval of integration into n subintervals (deltaX)
        // 3. find xk* = x0 + k(deltaX)
        // 4. find height at xk* for subinterval
        // 5. find area of rectangle
        // 6. repeat steps 3-5 until 
        // sum it to total area
        double riemannSum = 0;
        double subintervalNumber = 1;

        do {
            double deltaX = (upperBound - lowerBound) / numberIntervals;
            double xKstar = lowerBound + (subintervalNumber - 0.5) * deltaX;
            double innerFunc = (double)-1 * pow(xKstar, 2);
            double subintervalArea = deltaX * exp(innerFunc);
            riemannSum += subintervalArea;
            subintervalNumber++;
        } while (subintervalNumber < numberIntervals);

        printf("The integral of e^-x^2 on [%.5lf, %.5lf] with n = %d is:  %.5lf", lowerBound, upperBound, numberIntervals, riemannSum);
      
    } 

    return 0;
}
