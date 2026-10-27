#include <stdio.h>

int bitwise_addition(int a, int b) {
    while (b != 0) {
        int carry = a & b;
        a = a ^ b;
        b = carry << 1;
    }
    return a;
}

int bitwise_subtraction(int a, int b) {
    while (b != 0) {
        int borrow = (~a) & b;
        a = a ^ b;
       b = borrow << 1;
    }
    return a;
}

int bitwise_multiplication(int a, int b) {
    int result = 0;
    while (b != 0) {
        if (b & 1) {
            result = bitwise_addition(result, a);
        }
        a = a << 1;
        b = b >> 1;
    }

    return result;
}

int main() {
    int num1, num2, sum;

    printf("Enter two integers to add: ");
    scanf("%d %d", &num1, &num2);
    printf("%d + %d : %d\n", num1, num2, bitwise_addition(num1,num2));
    printf("%d - %d : %d\n", num1, num2, bitwise_subtraction(num1,num2));
    printf("%d x %d : %d\n", num1, num2, bitwise_multiplication(num1,num2));

    return 0;
}
