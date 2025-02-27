#include "Image.hpp"
#include <iostream>

void Image::create(const int rows, const int cols, const int channels) {
  if (rows <= 0 || cols <= 0 || channels <= 0) {
    throw std::invalid_argument("Invalid image size");
  }
  imgData_ = new ImageData;
  imgData_->rows = rows;
  imgData_->cols = cols;
  imgData_->channels = channels;
  imgData_->countRef = 1;
  imgData_->data = new unsigned char[rows*cols*channels]();

  }

Image::Image() : imgData_(nullptr) {}  // Создаем пустое изображение

Image::Image(const int rows, const int cols, const int channels) : Image() {
  create(rows, cols, channels);
}

Image::Image(const int rows, const int cols, const int channels, unsigned char* data): Image() {
  create(rows, cols, channels);
  imgData_->data = data;
}

Image::Image(const Image& image) : imgData_(image.imgData_) {
  if (imgData_) {
    ++(imgData_->countRef);
  }
}

Image& Image::operator=(const Image& image) {
  if (this != &image) {
    if (imgData_ && --(imgData_->countRef) == 0)
      delete imgData_;
    imgData_ = image.imgData_;
    if (imgData_)
      ++(imgData_->countRef);
  }
  return *this;
}

Image::~Image() {
  release();
}

void Image::release() {
  if (imgData_) {
    if (--(imgData_->countRef) == 0) {
      delete[] imgData_->data;
      delete imgData_;
      imgData_ = nullptr;
    }
  }
}


int Image::rows() const {
  return imgData_ ? imgData_->rows : 0;
}

int Image::cols() const {
  return imgData_ ? imgData_->cols : 0;
}

int Image::channels() const {
  return imgData_ ? imgData_->channels : 0;
}

int Image::total() const {
  return imgData_ ? imgData_->rows * imgData_->cols * imgData_->channels : 0;
}

unsigned char &Image::at(const int index) {
  if (!imgData_ || index >= (imgData_->rows * imgData_->cols * imgData_->channels)) {
    throw std::out_of_range("Invalid index");
  }
  return imgData_->data[index];
}

const unsigned char &Image::at(const int index) const {
  if (!imgData_ || index >= (imgData_->rows * imgData_->cols * imgData_->channels)) {
    throw std::out_of_range("Invalid index");
  }
  return imgData_->data[index];
}


Image Image::clone() const {
  Image copy = *this;
  return copy;
}

size_t Image::countRef() const {
  return imgData_ ? imgData_->countRef : 0;
}

unsigned char* Image::data() {
  return imgData_ ? imgData_->data : nullptr;
}

const unsigned char* Image::data() const {
  return imgData_ ? imgData_->data : nullptr;
}


Image Image::zeros(const int rows, const int cols, const int channels) {
  Image img(rows, cols, channels);
  std::memset(img.data(), 0, img.total());
  return img;
}

