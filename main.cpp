#include "Image.hpp"
#include <iostream>

void printImage(const Image& img) {
    for (int i = 0; i < img.rows(); ++i) {
        for (int j = 0; j < img.cols(); ++j) {
            const int idx = (i * img.cols() + j) * img.channels();
            const unsigned char r = img.data()[idx];
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
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width / 2; ++j) {
            const int idx = (i * width + j) * channels;
            img.data()[0] = 0;
            img.data()[idx]     = 255;
            img.data()[idx + 1] = 255;
            img.data()[idx + 2] = 255;
        }
    }

    std::cout << "Original Image:\n";
    printImage(img);

    // img.Mirror(MirrorType::Vertical);
    img.Rotate(-90);

    std::cout << "Mirrored Image:\n";
    printImage(img);

    return 0;
}
