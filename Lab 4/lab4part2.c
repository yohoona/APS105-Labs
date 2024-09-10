#include <stdio.h>
#include <stdbool.h>

int absVal(int x);
int sevenCounter(int x);
bool isLucky(int x);

int main() {
    int j = 0;
    int num;
    int sevensInNum;
    printf("Input an integer: ");
    scanf("%d", &num);

    sevensInNum = sevenCounter(absVal(num));
    if (isLucky(sevensInNum) == true) {
        j++;
    }

    while (num != 0) {
        printf("Input an integer (0 to stop): ");
        scanf("%d", &num);
        sevensInNum = sevenCounter(absVal(num));
        if (isLucky(sevensInNum) == true) {
            j++;
        } 
    } printf("You entered %d lucky number(s)!", j);

    return 0;

}

int absVal(int x) {
    if (x > 0) {
        x = x;
    } else {
        x = 0 - x;
    }
    return x;
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