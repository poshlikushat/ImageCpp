#include <gtest/gtest.h>
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

// Тест зеркального отражения
TEST(ImageTest, MirrorHorizontal) {
    constexpr int height = 5;
    constexpr int width = 5;
    constexpr int channels = 3;
    Image img = Image::zeros(height, width, channels);

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width / 2; ++j) {
            const int idx = (i * width + j) * channels;
            img.data()[idx]     = 255;
            img.data()[idx + 1] = 255;
            img.data()[idx + 2] = 255;
        }
    }
    printImage(img);
    img.Mirror(MirrorType::Horizontal);
    printImage(img);
    SUCCEED();
}

TEST(ImageTest, MirrorTypeVertical) {
    constexpr int height = 5;
    constexpr int width = 5;
    constexpr int channels = 3;
    Image img = Image::zeros(height, width, channels);

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width / 2; ++j) {
            const int idx = (i * width + j) * channels;
            img.data()[idx]     = 255;
            img.data()[idx + 1] = 255;
            img.data()[idx + 2] = 255;
        }
    }
    printImage(img);
    img.Mirror(MirrorType::Vertical);
    printImage(img);
    SUCCEED();
}

// Тест поворота на -90 градусов
TEST(ImageTest, RotateNegative90) {
    constexpr int height = 5;
    constexpr int width = 5;
    constexpr int channels = 3;
    Image img = Image::zeros(height, width, channels);

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width / 2; ++j) {
            const int idx = (i * width + j) * channels;
            img.data()[idx]     = 255;
            img.data()[idx + 1] = 255;
            img.data()[idx + 2] = 255;
        }
    }
    printImage(img);
    img.Rotate(-90);
    printImage(img);
    SUCCEED();
}

// Тест конструктора по умолчанию
TEST(ImageTest, DefaultConstructor) {
    Image img;
    EXPECT_TRUE(img.empty());
}

// Тест конструктора с размерами
TEST(ImageTest, SizeConstructor) {
    Image img(10, 20, 3);
    EXPECT_EQ(img.rows(), 10);
    EXPECT_EQ(img.cols(), 20);
    EXPECT_EQ(img.channels(), 3);
}

// Тест конструктора с некорректными размерами
TEST(ImageTest, InvalidSizeConstructor) {
    EXPECT_THROW(Image(-10, 20, 3), std::invalid_argument);
    EXPECT_THROW(Image(10, -20, 3), std::invalid_argument);
    EXPECT_THROW(Image(10, 20, -3), std::invalid_argument);
}

// Тест конструктора с переданными данными
TEST(ImageTest, DataConstructor) {
    unsigned char data[60] = {0};
    Image img(2, 10, 3, data);
    EXPECT_EQ(img.data(), data);
}

// Тест копирования изображения
TEST(ImageTest, CopyConstructor) {
    Image img1(5, 5, 3);
    Image img2 = img1;
    EXPECT_EQ(img1.countRef(), 2);
    EXPECT_EQ(img2.countRef(), 2);
}

// Тест присваивания изображения
TEST(ImageTest, AssignmentOperator) {
    Image img1(5, 5, 3);
    Image img2;
    img2 = img1;
    EXPECT_EQ(img1.countRef(), 2);
    EXPECT_EQ(img2.countRef(), 2);
}

// Тест доступа к пикселям
TEST(ImageTest, PixelAccess) {
    Image img(2, 2, 1);
    img.at(0) = 255;
    EXPECT_EQ(img.at(0), 255);
    EXPECT_THROW(img.at(10), std::out_of_range);
}

// Тест создания изображения через zeros
TEST(ImageTest, Zeros) {
    Image img = Image::zeros(3, 3, 1);
    for (int i = 0; i < img.total(); ++i) {
        EXPECT_EQ(img.at(i), 0);
    }
}

// Тест освобождения памяти
TEST(ImageTest, ReleaseMemory) {
    Image img(3, 3, 1);
    img.release();
    EXPECT_TRUE(img.empty());
}
