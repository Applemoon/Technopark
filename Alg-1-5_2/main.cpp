/*
 *Уваров Александр, 50 вариант, 3 группа
 */

#include <iostream>
#include <assert.h>

using std::cin;
using std::cout;



class TDeque
{
public:
    TDeque() : _buffer ( new int[2] ),
               _bufferSize( 2 ),
               _realSize( 0 ),
               _head( _buffer ),
               _tail( _buffer ) {}
    ~TDeque() { delete[] _buffer; }

    void PushFront( int element ); // положить в начало
    int PopFront(); // изъять первый элемент

    void PushBack( int element ); // положить в конец
    int PopBack(); // изъять последний элемент

private:
    int* _buffer; // динамический буфер дека
    unsigned int _bufferSize; // физический размер буфера
    unsigned int _realSize; // количество элементов в буфере
    int* _head; // начало массива в буфере
    int* _tail; // конец массива в буфере (адрес после массива)

    void Grow(); // увеличить размер буфера
};



void TDeque::PushFront( int element )
{
    // проверка, достаточен ли размер
    if ( _realSize == _bufferSize )
    {
        Grow();
    }

    // изменение начала массива
    if ( _head != _buffer )
    {
        --_head;
    }
    else
    {
        _head = _buffer + _bufferSize - 1;
        if ( _tail == _buffer )
        {
            _tail = _buffer + _bufferSize;
        }
    }

    // добавление элементаx
    _head[0] = element;
    ++_realSize;
}



int TDeque::PopFront()
{
    // проверка на пустоту
    if ( _realSize == 0 )
    {
        return -1;
    }

    const int result = _head[0];

    // изменение начала массива
    if ( _head != _buffer + _bufferSize - 1 )
    {
        ++_head;
    }
    else
    {
        _head = _buffer;
    }

    --_realSize;
    return result;
}



void TDeque::PushBack( int element )
{
    // проверка, достаточен ли размер
    if ( _realSize == _bufferSize )
    {
        Grow();
    }

    // изменение конца массива
    if ( _tail != _buffer + _bufferSize )
    {
        _tail[0] = element;
        ++_tail;
    }
    else
    {
        _buffer[0] = element;
        _tail = _buffer + 1;
    }
    ++_realSize;
}



int TDeque::PopBack()
{
    // проверка на пустоту
    if ( _realSize == 0 )
    {
        return -1;
    }

    int result = -1;

    // изменение конца буфера
    if ( _tail != _buffer + 1 )
    {
        --_tail;
        result = _tail[0];
    }
    else
    {
        _tail = _buffer + _bufferSize;
        result = _buffer[0];
    }

    --_realSize;
    return result;
}



void TDeque::Grow()
{
    // размер нового буфера
    const unsigned int newBufferSize = _bufferSize * 2;

    // новый буфер
    int* newBuffer = new int[newBufferSize];

    // начало заполнения нового буфера
    const unsigned int startPosition = _realSize / 2;

    // инициализация нового буфера
    unsigned int k = 0; // итератор для нового буфера

    // пустая начальная часть
    while ( k < startPosition )
    {
        newBuffer[k++] = 0;
    }

    // копирование старого буфера
    if ( _head < _tail )
    {
        for ( unsigned int i = 0; i < _realSize; ++i )
        {
            newBuffer[k++] = _head[i];
        }
    }
    else
    {
        // длина массива от головы до конца буфера
        const unsigned int firstPart = _realSize - ( _head - _buffer );

        // первая часть массива
        for ( unsigned int i = 0; i < firstPart; ++i )
        {
            newBuffer[k++] = *(_head + i);
        }

        // вторая часть массива
        for ( unsigned int i = 0; i < _realSize - firstPart; ++i )
        {
            newBuffer[k++] = _buffer[i];
        }
    }

    // пустая конечная часть
    while ( k < newBufferSize )
    {
        newBuffer[k++] = 0;
    }

    delete[] _buffer;
    _buffer = newBuffer;
    _bufferSize = newBufferSize;
    _head = _buffer + startPosition;
    _tail = _head + _realSize;
}



int main()
{
    TDeque deque;
    unsigned int commandsNumber = 0; // количество команд

    // ввод количества команд
    cin >> commandsNumber;
    if ( commandsNumber <= 0 ) return 1;

    bool ok = true;
    for ( unsigned int i = 0; i < commandsNumber; ++i )
    {
        int command = 0; // команда
        int number = 0; // новое или ожидаемое значение
        int real_number = 0; // получаемое значение
        cin >> command >> number;

        switch ( command )
        {
        case 1: // push front
            deque.PushFront( number );
            break;

        case 2: // pop front
            real_number = deque.PopFront();
            if ( number != real_number )
            {
                ok = false;
            }
            break;

        case 3: // push back
            deque.PushBack( number );
            break;

        case 4: // pop back
            real_number = deque.PopBack();
            if ( number != real_number )
            {
                ok = false;
            }
            break;

        default:
            assert( false );
            break;
        }

        if ( !ok )
        {
            cout << "NO";
            break;
        }
    }

    if ( ok )
    {
        cout << "YES";
    }

    return 0;
}
