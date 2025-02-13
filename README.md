Задача 4. Изображение.
Реализовать класс Image для работы с изображениями c применением техники reference counting. Класс представляет собой многоканальный двумерный массив из unsigned char для хранения пикселей изображения.

Справочная информация

Цифровые изображения состоят из пикселей, а пиксели состоят из комбинаций основных цветов. Набор основных цветов называются каналами. Например, RGB изображения состоят из 3-х каналов: R (red), G (green), B (blue), а изображения в градациях серого являются одноканальными.

Методические указания: При написании кода особое внимание обращайте на обработку исключительных ситуаций и граничных случаев, в частности, на корректность аргументов методов. Продумывайте и документируйте обработку ошибок в ваших методах.

Дополнительно: попробуйте часть методов протестировать до их реализации.

//Image.hpp

enum class MirrorType {
Vertical,
Horizontal
}

class Image {

public:
Image();
Image(int rows, int cols, int channels);
Image(int rows, int cols, int channels, unsigned char* data);
Image(const Image& image);
virtual ~Image();

    Image& operator=(const Image& image);

    // Вернуть клон изборажения
    Image clone();
    //Скопировать изображение.
    void copyTo(Image& image);
    void create(int rows, int cols, int channels);
    bool empty();

    //декрементирует счетчик ссылок и в случае необходимости освобождает ресурсы (память).
    void release();

    Image col(int x);

    Image row(int y);

    const unsigned char* data() const;
    unsigned char* data();

    int rows();
    int cols();
    int total();
    int channels();

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
    //Т.е. количество объектов, которые ссылаются на данное изображение. Этот метод нужен для unit test'ов.
    size_t countRef();
};