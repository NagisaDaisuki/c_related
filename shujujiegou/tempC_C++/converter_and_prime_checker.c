#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

// Function to check if a number is prime
int is_prime(int n) {
    if (n <= 1) {
        return 0; // 1 and numbers less than 1 are not prime
    }
    if (n <= 3) {
        return 1; // 2 and 3 are prime
    }
    if (n % 2 == 0 || n % 3 == 0) {
        return 0; // Divisible by 2 or 3
    }
    // Check from 5 to sqrt(n)
    for (int i = 5; i * i <= n; i = i + 6) {
        if (n % i == 0 || n % (i + 2) == 0) {
            return 0;
        }
    }
    return 1;
}

// Function to convert binary string to hexadecimal string
void binaryToHex(const char *binary_string, char *hex_string) {
    long long decimal = strtoll(binary_string, NULL, 2);
    sprintf(hex_string, "%llX", decimal);
}

int main() {
    const char *binary_data = "1111011"; // Example binary data (123 in decimal)
    char hex_output[17]; // To store the hexadecimal output

    // Convert binary to hex
    binaryToHex(binary_data, hex_output);
    printf("Binary: %s\n", binary_data);
    printf("Hexadecimal: %s\n", hex_output);

    // Convert binary string to an integer for the prime check
    long long decimal_value = strtoll(binary_data, NULL, 2);
    printf("Decimal: %lld\n", decimal_value);

    // Check if the decimal value is a prime number
    if (is_prime((int)decimal_value)) {
        printf("%lld is a prime number.\n", decimal_value);
    } else {
        printf("%lld is not a prime number.\n", decimal_value);
    }
    
    printf("\n");

    const char *binary_data2 = "101101"; // Example binary data (45 in decimal)
    
    // Convert binary to hex
    binaryToHex(binary_data2, hex_output);
    printf("Binary: %s\n", binary_data2);
    printf("Hexadecimal: %s\n", hex_output);

    // Convert binary string to an integer for the prime check
    long long decimal_value2 = strtoll(binary_data2, NULL, 2);
    printf("Decimal: %lld\n", decimal_value2);

    // Check if the decimal value is a prime number
    if (is_prime((int)decimal_value2)) {
        printf("%lld is a prime number.\n", decimal_value2);
    } else {
        printf("%lld is not a prime number.\n", decimal_value2);
    }


    return 0;
}
