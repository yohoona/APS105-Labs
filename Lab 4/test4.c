#include <stdio.h>
#include <stdbool.h>

int sevenCounter(int x);
bool isLucky(int x);

int main() {
    int j = 0;
    int num;
    printf("enter an integer: ");
    scanf("%d", &num);

    num = sevenCounter(num);
    if (isLucky(num) == true) {
        j++;
    }

    while (num != 0) {
        printf("enter an integer (0 to stop): ");
        scanf("%d", &num);
        num = sevenCounter(num);
        if (isLucky(num) == true) {
            j++;
        } 
    } printf("you entered %d lucky numbers", j);

    return 0;

}

int sevenCounter(int x) {
    int i = 0;
    while (x > 0) {
        if (x%10 == 7) {
            i++;
        } x /= 10;
    }
    return i;
}

bool isLucky(int x) {
    if (x != 3) {
        return false;
    } else {
        return true;
    }
}
