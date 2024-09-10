#include <stdio.h>
#include <math.h>

int main() {
    double pi = 3.14159265;

//inputs
    double inputA;
    printf("Enter the length of side A: ");
    scanf("%lf", &inputA);

    double inputB;
    printf("Enter the length of side B: ");
    scanf("%lf", &inputB);

    double inputAlpha;
    printf("Enter the measure of angle alpha in degrees: ");
    scanf("%lf", &inputAlpha);

//deg/rad conversion
    double deg2rad = pi / 180;
    double rad2deg = 180 / pi;

//calculations
    double outputBeta = asin(inputB * sin(inputAlpha * deg2rad) / inputA) * rad2deg;
    double outputGamma = 180.0 - (inputAlpha + outputBeta);
    double outputC = sin(outputGamma * deg2rad) * inputA / sin(inputAlpha * deg2rad);

//output
    printf("\nResults: ");
    printf("\nSide A: %.2lf", inputA);
    printf("\nSide B: %.2lf", inputB);
    printf("\nSide C: %.2lf", outputC);
    printf("\nAngle Alpha: %.2lf degrees", inputAlpha);
    printf("\nAngle Beta: %.2lf degrees", outputBeta);
    printf("\nAngle Gamma: %.2lf degrees", outputGamma);
        
    return 0;

}
