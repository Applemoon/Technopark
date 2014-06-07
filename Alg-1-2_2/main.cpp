// Copyright 2014 <Uvarov>

// 1_2

#include <cstdio>


// Check number if it's prime
bool checkPrime(int number) {
    for (int i = 2; i * i < number; ++i) {
        if (number % i == 0) {
            return false;
        }
    }
    return true;
}

// Find minimum multiplier of number
int findMinimumMultiplier(int number, int startPosition) {
    for (int i = startPosition; i * i <= number; ++i) {
        if (checkPrime(i)) {
            if (number % i == 0) {
                return i;
            }
        }
    }
    return number;
}

int main() {
    int number = 0;
    int lastMinimumMultiplier = 2;

    // Input
    int scanInput = scanf("%i", &number);
    if (scanInput != 1) {
        return 1;
    }

    // Main loop with output
    while (number != 1) {
        int minimumMultiplier = findMinimumMultiplier(
                    number, lastMinimumMultiplier);
        printf("%i", minimumMultiplier);
        number /= minimumMultiplier;
        if (number != 1) {
            printf(" ");
        }
        lastMinimumMultiplier = minimumMultiplier;
    }

    return 0;
}

