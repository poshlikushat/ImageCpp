#include "Image.hpp"
#include <iostream>
#include <cmath>

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

void Image::Mirror(const MirrorType type) {
  if (empty()) return;

  const int rows = this->rows();
  const int cols = this->cols();
  const int channels = this->channels();

  switch (type) {
    case MirrorType::Vertical:
      for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols / 2; ++j) {
          for (int c = 0; c < channels; ++c) {
            const int idx1 = (i * cols + j) * channels + c;
            const int idx2 = (i * cols + (cols - 1 - j)) * channels + c;
            std::swap(imgData_->data[idx1], imgData_->data[idx2]);
          }
        }
      }
    break;
    case MirrorType::Horizontal:
      for (int i = 0; i < rows / 2; ++i) {
          for (int j = 0; j < cols; ++j) {
            for (int c = 0; c < channels; ++c) {
              const int idx1 = (i * cols + j) * channels + c;
              const int idx2 = ((rows - 1 - i) * cols + j) * channels + c;
              std::swap(imgData_->data[idx1], imgData_->data[idx2]);
            }
          }
        }
      break;
    default:
      break;
  }

}

bool Image::empty() const {
  return imgData_ == nullptr;
}

Image Image::values(const int rows, const int cols, const int channels, const unsigned char value) {
  if (empty()) throw std::out_of_range("Image is empty");
  Image img(rows, cols, channels);
  std::memset(img.data(), value, img.total());
  return img;
}

void Image::Rotate(const double angle) {
  if (empty()) return;

  int numRotations = 0;
  if (angle == 90 || angle == -270)
    numRotations = 1;
  else if (angle == 180 || angle == -180)
    numRotations = 2;
  else if (angle == -90 || angle == 270)
    numRotations = 3;
  else {
    throw std::cerr << "Unsupported angle. Only multiples of 90 are supported.\n";
    return;
  }

  Image result = *this;
  for (int i = 0; i < numRotations; ++i) {
    const int rows = result.rows();
    const int cols = result.cols();
    const int channels = result.channels();

    Image temp(cols, rows, channels);
    for (int r = 0; r < rows; ++r) {
      for (int c = 0; c < cols; ++c) {
        for (int ch = 0; ch < channels; ++ch) {
          //90 degree rotation
          temp.at((c * rows + (rows - 1 - r)) * channels + ch) =
              result.at((r * cols + c) * channels + ch);
        }
      }
    }
    result = temp;
  }
  *this = result;
}

void Image::copyTo(Image& image) const {
  if (empty()) return;





