#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

double randDouble();
bool inBounds(double x, double y);

int main() {
    int i = 0;
    int inside = 0;
    int n;

    printf("Number of monte carlo iterations: ");
    scanf(" %d", &n);

    while (i < n) {
        double x = randDouble();
        double y = randDouble();
        if (inBounds(x, y) == true) {
            inside++;
        }
        i++;
    }

    double pi = 4 * (double)inside / n;
    printf("Pi: %lf", pi); 

    return 0;
}

double randDouble() {
    return (double)rand() / RAND_MAX;
}

bool inBounds(double x, double y) {
    if (((x * x) + (y * y)) <= 1) {
        return true;
    } else {
        return false;
    }
}