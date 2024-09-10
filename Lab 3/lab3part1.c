#include <stdio.h>

int main(void) {
    char userNum, userSign;
    int sum = 0;
    printf("Enter sequence of numbers to add: ");

    do {
        scanf(" %c %c", &userSign, &userNum);
        if (userSign == '-' && userNum >= '0' && userNum <= '9') {
            sum -= userNum - '0';
            printf("Sum is updated to %d\n", sum);
        } else if (userSign == '+' && userNum >= '0' && userNum <= '9') {
            sum += userNum - '0';
            printf("Sum is updated to %d\n", sum);
        }
    } while (sum > 0);
    printf("Sum fell below zero.\n");
    return 0;
}