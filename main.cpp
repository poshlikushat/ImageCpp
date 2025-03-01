#include <iostream>
#include "Image.hpp"

int main() {
    // Define flag dimensions.
    const int rows = 13;
    const int cols = 25;

    // Create an image with 1 channel.
    Image flag = Image::zeros(rows, cols, 1);

    // Fill the whole flag with '-' for stripes.
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            flag.at(i * cols + j) = '-';
        }
    }

    // Draw the union (blue area with stars) on the top-left.
    // For this simple implementation we use 7 rows and 10 columns.
    const int union_rows = 7;
    const int union_cols = 10;
    for (int i = 0; i < union_rows; i++) {
        for (int j = 0; j < union_cols; j++) {
            // Apply a star pattern at alternating positions
            if ((i + j) % 2 == 0) {
                flag.at(i * cols + j) = '*';
            }
        }
    }

    // Output the flag in the console.
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            std::cout << flag.at(i * cols + j);
        }
        std::cout << std::endl;
    }

    return 0;
}