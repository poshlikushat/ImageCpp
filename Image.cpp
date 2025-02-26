#include "Image.hpp"

void Image::create(const int rows, const int cols, const int channels) {
  imgData_ = new ImageData;
  imgData_->rows = rows;
  imgData_->cols = cols;
  imgData_->channels = channels;
  imgData_->countRef = 1;
  imgData_->total = (rows + cols) * channels;
  imgData_->data = new unsigned char[imgData_->total];
  }

Image::Image() : imgData_(nullptr) {}  // Создаем пустое изображение

Image::Image(const int rows, const int cols, const int channels) : imgData_(nullptr) {
  if (rows <= 0 || cols <= 0 || channels <= 0) {
    throw std::invalid_argument("Invalid image size");
  }
  create(rows, cols, channels);
}

Image::Image(const int rows, const int cols, const int channels, unsigned char* data): imgData_(nullptr) {
  if (rows <= 0 || cols <= 0 || channels <= 0) {
    throw std::invalid_argument("Invalid image size");
  }
  create(rows, cols, channels);
  imgData_->total = rows * cols * channels;
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
      delete[] imgData_;

    imgData_ = image.imgData_;
    if (imgData_)
      ++(imgData_->countRef);
  }
  return *this;
}

Image::~Image() {
  if (imgData_) {
    if (--(imgData_->countRef) == 0) {
      delete[] imgData_->data;
      delete imgData_;
    }
  }
}

void Image::release() const {
  if (imgData_) {
    if (--(imgData_->countRef) == 0) {
      delete[] imgData_;
      imgData_->rows = 0;  // Если это не указать, то значение будет 2043. Почему?
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
  return imgData_ ? imgData_->total : 0;
}

// unsigned char &Image::at(int index) {
//   if (index < 0)
//     throw std::out_of_range("Invalid index");
//   return data[index];
// }

// const unsigned char* Image::data() const {
//   return imgData_ ? imgData_->data : nullptr;
// }

Image Image::clone() const {
  Image copy = *this;
  copy.imgData_ = new ImageData;
  copy.imgData_->rows = imgData_->rows;
  copy.imgData_->cols = imgData_->cols;
  copy.imgData_->channels = imgData_->channels;
  copy.imgData_->data = new unsigned char[copy.imgData_->total];
  return copy;
}

size_t Image::countRef() const {
  return imgData_ ? imgData_->countRef : 0;
}

