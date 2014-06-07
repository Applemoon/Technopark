/* Уваров Александр, 50 вариант
 *
 * 2_2. Ломаная 1 (пирамидальная сортировка)
Задано N точек на плоскости. Указать (N-1)-звенную несамопересекающуюся
незамкнутую ломаную, проходящую через все эти точки.
Указание: стройте ломаную в порядке возрастания x-координаты. Если имеются две
точки с одинаковой x-координатой, то расположите раньше ту точку, у которой
y-координата меньше.

in
4
0 0
1 1
1 0
0 1

out
0 0
0 1
1 0
1 1
*/

#include <iostream>

using std::cin;
using std::cout;
using std::swap;



// Точка
struct Point
{
    int x;
    int y;

    Point( int ax = 0, int ay = 0 ) : x( ax ), y( ay ) {}

    bool operator<( const Point& p ) const
    {
        if ( x != p.x )
        {
            return x < p.x;
        }
        else
        {
            return y < p.y;
        }
    }

    bool operator>( const Point& p ) const
    {
        return ( p < *this );
    }

    void Print() const
    {
        cout << x << " " << y << "\n";
    }
};



// Обратная куча
class Heap
{
public:
    Heap( size_t arraySize ) : _buffer( new Point[arraySize] ), _size( 0 ) {}
    ~Heap() { delete[] _buffer; }
    Point PopMin(); // Извлечь минимальный элемент
    void Add( Point p ); // Добавить элемент
    bool HasSingleElement() const { return _size == 1; } // В массиве 1 элемент

private:
    Point* _buffer; // Буффер
    size_t _size; // Количество элементов

    void Heapify( size_t k ); // Восстановление свойств обратной кучи
};



Point Heap::PopMin() // Извлечь минимальный элемент
{
    if ( _size == 0 )
    {
        return 0;
    }

    Point result = _buffer[0];

    // Кладем последний элемент в корень и восстанавливаем свойства кучи
    _buffer[0] = _buffer[--_size];
    Heapify( 0 );
    return result;
}



void Heap::Add( Point p ) // Добавить элемент
{
    // Для данной задачи проверка на переполнение буфера не требуется
    // Добавление элемента в конец
    _buffer[_size++] = p;

    // Восстановление кучи
    size_t currentPos = _size - 1; // Текущая позиция
    while ( currentPos != 0 )
    {
        const size_t parentPos = (currentPos - 1) / 2; // Позиция родителя
        if ( _buffer[currentPos] > _buffer[parentPos] )
        {
            return;
        }
        swap( _buffer[currentPos], _buffer[parentPos] );
        currentPos = parentPos;
    }
}



void Heap::Heapify( size_t k ) // Восстановление свойств обратной кучи
{
    if ( _size <= 1 )
    {
        return;
    }

    const size_t left = 2 * k + 1;
    const size_t right = 2 * k + 2;

    // Поиск меньшего сына, если такой есть
    size_t smaller = k;
    if ( left < _size )
    {
        if ( _buffer[left] < _buffer[k] )
        {
            smaller = left;
        }
    }
    if ( right < _size )
    {
        if (_buffer[right] < _buffer[smaller] )
        {
            smaller = right;
        }
    }

    // Если меньший сын есть, проталкиваем корень в него
    if ( smaller != k )
    {
        swap( _buffer[k], _buffer[smaller] );
        Heapify( smaller );
    }
}



int main()
{
    size_t pointsNumber = 0; // Количество вершин
    cin >> pointsNumber;
    if ( pointsNumber == 0 )
    {
        return 1;
    }

    Heap array( pointsNumber ); // Массив вершин размером pointsNumber
    for ( size_t i = 0; i < pointsNumber; ++i )
    {
        int x = 0;
        int y = 0;
        cin >> x >> y;
        array.Add( Point( x, y ) );
    }

    // Вывод массива
    for ( size_t i = 0; i < pointsNumber; ++i )
    {
        array.PopMin().Print();
    }

    return 0;
}

