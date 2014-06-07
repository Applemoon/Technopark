// Copyright 2014 <Uvarov>

// 1_2

#include <cstdio>


// Check if rectange c x d can lay into rectange a x b
bool checkLayIn(int a, int b, int c, int d) {
    return (a >= c && b >= d) || (a >= d && b >= c);
}

int main() {
    // First init
    int a = 0;
    int b = 0;
    int c = 0;
    int d = 0;

    // Input
    int input_count = scanf("%i%i%i%i", &a, &b, &c, &d);
    if (input_count != 4) {
        return 1;
    }

    // Output
    checkLayIn(a, b, c, d) ? printf("YES") : printf("NO");

    return 0;
}

