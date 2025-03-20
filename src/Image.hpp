#ifndef IMAGE_H
#define IMAGE_H
// ReSharper disable once CppUnusedIncludeDirective
#include <iostream>

enum class MirrorType {
  Vertical,
  Horizontal
};


class Image final {
  struct ImageData {
    unsigned char *data;
    int rows;
    int cols;
    int channels;
    size_t countRef;
    bool ownsData;
  };

  ImageData *imgData_;

public:
  Image();

  Image(int rows, int cols, int channels);

  Image(int rows, int cols, int channels, unsigned char *data);

  Image(const Image &image);

  ~Image();

  Image &operator=(const Image &image);

  //Вернуть клон изображения
  [[nodiscard]] Image clone() const; //Не меняет ориг
  //Скопировать изображение
  void copyTo(Image &image) const;

  void create(int rows, int cols, int channels);

  [[nodiscard]] bool empty() const; //Только проверяет состояние

  //декрементирует счетчик ссылок и в случае необходимости освобождает ресурсы (память).
  void release();

  [[nodiscard]] Image col(int x) const;

  [[nodiscard]] Image row(int y) const;

  [[nodiscard]] const unsigned char *data() const; //Возвращает часть пикселя без модификации
  unsigned char *data();

  [[nodiscard]] int rows() const;

  [[nodiscard]] int cols() const;

  [[nodiscard]] int total() const;

  [[nodiscard]] int channels() const;

  //Вернуть ЧАСТЬ пикселя
  unsigned char &at(int index); // Что делает?
  [[nodiscard]] const unsigned char &at(int index) const; // Что делает?

  static Image zeros(int rows, int cols, int channels);

  Image values(int rows, int cols, int channels, unsigned char value) const;

  //Отразить изображение по вертикали или по горизонтали
  void Mirror(MirrorType type); // Нужно сделать

  //Повернуть на угол кратный 90
  void Rotate(double angle); // Нужно сделать

  //Возвращает текущее количество ссылок на изображение.
  //Т.е. количество объектов, которые ссылаются на данное изображение Этот метод нужен для untiy __Tests__'ов.
  [[nodiscard]] size_t countRef() const;
};


#endif //IMAGE_H
