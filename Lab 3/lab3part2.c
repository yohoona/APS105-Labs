#include <stdio.h>
#include <math.h>
#define M_PI 3.14159265358979323846

int main() {
    double robotHeight = 2; // meters
    double ballSpeed = 20; // meters/second
    double gravConst = 9.81; // metres/second^2
    double deg2rad = M_PI / 180;
    double alpha = 0;
    double xSpeed, ySpeed;
    double distFromRim = 1;
    double travelTime, deltaY;

    double travelDist; // metres
    do {
        printf("Please enter the horizontal distance from the wall between 3 and 30 m: ");
        scanf("%lf", &travelDist);    
    } while (travelDist > 30 || travelDist < 3);

    double rimHeight; // metres
    do {
        printf("Please enter the target height between 3 and 6 m: ");
        scanf("%lf", &rimHeight);
    } while (rimHeight > 6 || rimHeight < 3);


    while (distFromRim > 0.3) {
        xSpeed = cos(deg2rad * alpha) * ballSpeed;
        ySpeed = sin(deg2rad * alpha) * ballSpeed;
        travelTime = travelDist / xSpeed;
        deltaY = robotHeight + (ySpeed * travelTime) - (0.5 * gravConst * pow(travelTime, 2.0));
        distFromRim = fabs(deltaY - rimHeight); //metres
        alpha++;
    }
    printf("The angle should be %.2lf", alpha - 1);
    
    return 0;
}