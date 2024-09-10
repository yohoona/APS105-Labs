#include <stdio.h>

int main() {
// inputs    
    int presentHour, presentMinute;
    printf("Enter current time: ");
    scanf("%d" "%d", &presentHour, &presentMinute);

    double tripTime;
    printf("Enter trip time: ");
    scanf("%lf", &tripTime);

// convert triptime into hrs and mins     
    double tripHours = (int) tripTime;
    double tripMinutes = (tripTime - tripHours) * 60;

// calculate arrival time    
    double arrivalHour = presentHour + tripHours;
    double arrivalMinute = presentMinute + tripMinutes;
    if (arrivalMinute >= 60) {
        arrivalHour += 1;
        arrivalMinute -= 60;
    }

// output
    printf("\nCurrent time is %02d:%02d\n", presentHour, presentMinute);
    if (arrivalHour >= 24) {
        arrivalHour -= 24;
        printf("Arrival time is next day %02.0lf:%02.0lf", arrivalHour, arrivalMinute);
    } else {
        printf("Arrival time is same day %02.0lf:%02.0lf", arrivalHour, arrivalMinute);
    }

    return 0;

}