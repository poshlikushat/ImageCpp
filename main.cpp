#include <iostream>
#include "Image.hpp"

void createAnImage()
{
    Image image;
    image.create(480, 640, 3);

    std::cout << "Rows: " << image.rows() << std::endl;
    std::cout << "Cols: " << image.cols() << std::endl;
    std::cout << "Channels: " << image.channels() << std::endl;
}

void copyAnImage() {
    Image image;
    image.create(1, 640, 3);
    std::cout << "countRef: " << image.countRef() << std::endl;
    std::cout << "Cols: " << image.cols() << std::endl;
    std::cout << "Rows: " << image.rows() << std::endl;
    std::cout << "Total: " << image.total() << std::endl;
    std::cout << "Data: " << static_cast<int>(*image.data()) << std::endl;
    const Image image2 = image.clone();
    std::cout << "countRef: " << image.countRef() << std::endl;
    std::cout << "Cols: " << image.cols() << std::endl;
    std::cout << "Rows: " << image.rows() << std::endl;
    std::cout << "Total: " << image.total() << std::endl;
    image.release();
    std::cout << "countRef: " << image.countRef() << std::endl;
    std::cout << "Cols: " << image.cols() << std::endl;
    std::cout << "Rows: " << image.rows() << std::endl;
    std::cout << "Total: " << image.total() << std::endl;
    image.release();
    std::cout << "countRef: " << image.countRef() << std::endl;
    std::cout << "Cols: " << image.cols() << std::endl;
    std::cout << "Rows: " << image.rows() << std::endl;
    std::cout << "Total: " << image.total() << std::endl;
}

void testZero() {
    Image img = Image::zeros(3, 3, 3);

    for (int i = 0; i < img.total(); ++i) {
        std::cout << static_cast<int>(img.at(i)) << " ";
    }
    std::cout << std::endl;
}

int main() {

}
