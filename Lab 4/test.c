#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

double randDouble() {
    return (double)rand() / ((double)RAND_MAX);
}

bool oui(double x, double y) {
    if (x + y < 0.7) {
        return true;
    } else {
        return false;
    }
}

int main() {

    int n;
    int i = 0;
    int yes = 0;

    printf("how many times? ", n);
    scanf(" %d", &n);
    
    while (i < n) {
        double x = randDouble();
        double y = randDouble();
        if (oui(x, y) == true) {
            yes++;
        }
        i++;
    }

    double ratio = (double)yes/(double)n;

    printf("yes count: %d\n", yes);
    printf("yes ratio: %lf", ratio);

    return 0;
}

/*int main() {
    
    int x = rand();
    printf("%d", x);

    return 0;
}*/