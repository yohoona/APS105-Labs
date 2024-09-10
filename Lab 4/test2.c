#include <stdio.h>

int main() {
    int i = 0;
    int x;
    printf("enter integer: ");
    scanf("%d", &x);

    while (x > 0) {
        if (x%10 == 7) {
            i++;
        } x /= 10;
    }

    printf("this number has %d seven(s)", i);

    return 0;
}