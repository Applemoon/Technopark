/* Уваров Александр, 3 группа, 50 вариант

6_1. Скобочная последовательность.
Дан фрагмент последовательности скобок, состоящей из символов (){}[].
Требуется определить, возможно ли продолжить фрагмент в обе стороны, получив
корректную последовательность.
Формат входных данных. Строка, содержащая символы (){}[] и, возможно, перевод
строки.
Максимальная длина строки 10^6 символов.
Формат выходных данных. Если возможно - вывести минимальную корректную
последовательность, иначе - напечатать "IMPOSSIBLE".
*/

#include <iostream>
#include <cstring>

using std::cin;
using std::cout;



// Класс стека
class CStack
{
public:
    CStack() :  _strSize( 0 ), _bufferSize( 2 ) { _buffer = new char[2]; }
    ~CStack() { delete[] _buffer; }
    void PushBack( char c ); // Протолкнуть новый элемент
    char PopBack(); // Изъять последний элемент
    bool IsEmpty() { return _strSize == 0; } // Проверка на пустоту

private:
    char* _buffer; // Буфер
    unsigned int _strSize; // Длина строки
    unsigned int _bufferSize; // Размер буфера

    void Grow(); // Зарезервировать дополнительную память
};



void CStack::PushBack( char c )
{
    // Проверка на свободное место
    if ( _strSize == _bufferSize )
    {
        Grow();
    }

    _buffer[_strSize++] = c;
}



char CStack::PopBack()
{
    // Проверка на пустоту
    if ( _strSize != 0 )
    {
        return _buffer[--_strSize];
    }

    return 0;
}



void CStack::Grow()
{
    // Новая длина буфера
    const unsigned int newBufferSize = _bufferSize * 2;

    // Новый буфер
    char* newBuffer = new char[newBufferSize];
    for ( unsigned int i = 0; i < _strSize; ++i )
    {
        newBuffer[i] = _buffer[i];
    }

    delete[] _buffer;
    _buffer = newBuffer;
    _bufferSize = newBufferSize;
}



// Проверка, является ли скобка открывающей
bool IsOpening( char c )
{
    return ( c == '(' || c == '{' || c == '[' );
}



// Получение соответствующей скобки
char GetReverse( char c )
{
    if ( c == '(' )
        return ')';
    else if ( c == ')' )
        return '(';
    else if ( c == '{' )
        return '}';
    else if ( c == '}' )
        return '{';
    else if ( c == '[' )
        return ']';
    else if ( c == ']' )
        return '[';

    return 0;
}



int main()
{
    char string[1000000]; // Строка
    cin >> string;

    CStack stackBefore; // Открывающий стек
    CStack mainStack; // Вспомогательный (закрывающий) стек

    size_t strLen = strlen( string );
    for ( size_t i = 0; i < strLen; ++i )
    {
        if ( IsOpening( string[i] ) ) // Если скобка открывающая...
        {
            mainStack.PushBack( string[i] ); // ...сохраняем скобку
        }
        else // ...иначе (закрывающая) ищем соответствие в mainStack
        {
            char lastInMainStack = mainStack.PopBack();
            if ( lastInMainStack == 0 ) // Если mainStack пустой...
            {
                // ...добавляем соответствующую скобку в stackBefore
                stackBefore.PushBack( GetReverse( string[i] ) );
            }
            else // ...иначе проверяем на корректность
            {
                if ( string[i] != GetReverse( lastInMainStack ) )
                {
                    // Некорректная пара скобок
                    cout << "IMPOSSIBLE";
                    return 0;
                }
            }
        }
    }

    // Вывод
    // Начало
    while ( !stackBefore.IsEmpty() )
    {
        cout << stackBefore.PopBack();
    }

    // Введенная строка
    for ( size_t i = 0; i < strLen; ++i )
    {
        cout << string[i];
    }

    // Конец
    while ( !mainStack.IsEmpty() )
    {
        cout << GetReverse( mainStack.PopBack() );
    }

    return 0;
}

