// Copyright 2014 <Uvarov>
// 3_2

#include <cstdio>



// Find triangle square by 3 verts
float findTriangleSquare(int x1, int y1, int x2, int y2, int x3, int y3) {
    float result = static_cast<float>((x1 - x3) * (y2 - y3) -
                                      (x2 - x3) * (y1 - y3)) / 2;
    if (result >= 0) {
        return result;
    } else {
        return -result;
    }
}



int main() {
    // First init
    int vertsNumber = 0;
    int *coords;

    int firstX = 0;
    int firstY = 0;
    int secondX = 0;
    int secondY = 0;
    int thirdX = 0;
    int thirdY = 0;

    float square = 0;

    // Input
    int scanfVertsNumber = scanf("%i", &vertsNumber);
    if (scanfVertsNumber != 1 || vertsNumber < 3) {
        return 1;
    }

    coords = new int[vertsNumber * 2];

    for (int i = 0; i < vertsNumber * 2; ++i) {
        int scanfCoordinate = scanf("%i", &coords[i]);
        if (scanfCoordinate != 1) {
            return 1;
        }
    }

    // Calculating
    firstX = coords[0];
    firstY = coords[1];
    thirdX = coords[2];
    thirdY = coords[3];

    for (int i = 0; i < vertsNumber - 2; ++i) {
        secondX = thirdX;
        secondY = thirdY;
        thirdX = coords[(i + 2) * 2];
        thirdY = coords[(i + 2) * 2 + 1];

        square += findTriangleSquare(
                    firstX, firstY, secondX, secondY, thirdX, thirdY);
    }

    // Output
    printf("%.1f", square);

    delete [] coords;
    return 0;
}

