#ifndef IMAGE_H
#define IMAGE_H

enum class MirrorType {
  Vertical,
  Horizontal
};


class Image {
  public:
    Image();
    Image(int rows, int cols, int channels);
    Image(const Image& image);
    virtual ~Image();

    Image& operator=(const Image& image);

    //Вернуть клон изображения
    Image clone() const; //Не меняет ориг
    //Скопировать изображение
    void copyTo(Image& image) const;
    void create(int rows, int cols, int channels);
    bool empty() const; //Только проверяет состояние

    //декрементирует счетчик ссылок и в случае необходимости свобождает ресурсы (память).
    void release();

    Image col(int x) const;

    Image row(int y) const;

    const unsigned char* data() const;  //Возвращает часть пикселя без модификации
    unsigned char* data();

    int rows() const;
    int cols() const;
    int total() const;
    int channels() const;

    //Вернуть ЧАСТЬ пикселя
    unsigned char& at(int index);
    const unsigned char& at(int index) const;

    Image zeros(int rows, int cols, int channels);
    Image values(int rows, int cols, int channels, unsigned char value);

    //Отразить изображение по вертикали или по горизонтали
    void Mirror(MirrorType type);

    //Повернуть на угол кратный 90
    void Rotate(double angle);

    //Возвращает текущее количество ссылок на изображение.
    //Т.е. количество объектов, которые ссылаются на данное изображение Этот метод нужен для untiy test'ов.
    size_t countRef() const;
};



#endif //IMAGE_H
