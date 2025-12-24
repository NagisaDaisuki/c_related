#include <stdio.h>
#include <float.h>
#include "calc.h"

int main() {
    printf("Testing Addition Overflow:\n");
    add(DBL_MAX, DBL_MAX);

    printf("\nTesting Subtraction Overflow:\n");
    sub(-DBL_MAX, DBL_MAX);

    printf("\nTesting Multiplication Overflow:\n");
    mul(DBL_MAX, 2.0);

    printf("\nTesting Division Overflow:\n");
    div_op(DBL_MAX, 0.5);

    printf("\nTesting Division by Zero:\n");
    div_op(10.0, 0.0);

    printf("\nTesting Normal Operations:\n");
    printf("1 + 1 = %f\n", add(1.0, 1.0));

    return 0;
}
