#include "Image.hpp"
#include <iostream>

void printImage(const Image& img) {
    for (int i = 0; i < img.rows(); i++) {
        for (int j = 0; j < img.cols(); j++) {
            int idx = (i * img.cols() + j) * img.channels();
            unsigned char r = img.data()[idx];
            std::cout << (r > 0 ? "⬜" : "⬛");
        }
        std::cout << '\n';
    }
}

int main() {
    constexpr int height = 5;
    constexpr int width = 5;
    constexpr int channels = 3;
    Image img = Image::zeros(height, width, channels);

    // Заполняем левую половину белым
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width / 2; j++) {
            const int idx = (i * width + j) * channels;
            img.data()[0] = 0;
            img.data()[idx]     = 255; // R
            img.data()[idx + 1] = 255; // G
            img.data()[idx + 2] = 255; // B
        }
    }

    std::cout << "Original Image:\n";
    printImage(img);

    img.Mirror(MirrorType::Vertical);

    std::cout << "Mirrored Image:\n";
    printImage(img);

    return 0;
}
