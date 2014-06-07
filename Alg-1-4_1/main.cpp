/*Дан отсортированный массив целых чисел A[0..n-1] и массив целых чисел B[0..m-1].
 *Для каждого элемента массива B[i] найдите минимальный индекс минимального
 *элемента массива, равного или превосходящего b: A[k] >= B[i]. Если такого
 *элемента нет, выведите n. Время работы поиска каждого элемента B[i]: O(log(k)).
 *
 *Уваров, 50 вариант, 3 группа
 */

#include <iostream>

using std::cin;
using std::cout;



// Выделение памяти под массив и его ввод
int* array_input( unsigned int size )
{
    // Выделение памяти
    int* array = new int[size];
    if ( array == 0 )
    {
        return 0;
    }

    // Ввод
    for ( unsigned int i = 0; i < size; ++i )
    {
        cin >> array[i];
    }

    return array;
}



// Поиск в массиве array в диапазоне (a,b] элемента, большего или равного element
int check( int element, int* array, int a, int b )
{
    unsigned int length = b - a;
    while ( length > 1 )
    {
        // С каждым шагом делим диапазон пополам до длины 1
        if( element > array[a + length / 2] )
        {
            a += length / 2;
        }
        else
        {
            b -= length / 2;
        }
        length = b - a;
    }

    // Если элемент не найден, возвращаем -1
    return array[b] >= element ? b : -1;
}



// Поиск первого элемента массива array, который больше или равен element
int index_of_greater_or_equal( int element, int* array, unsigned int size )
{
    // Границы диапазона поиска
    int prev_index = -1;
    unsigned int index = 0;

    bool found = false; // Элемент найден
    int pos = -1; // Позиция элемента
    bool end_of_array = false; // Дошли до конца массива

    do
    {
        index = ( prev_index + 1 ) * 2;
        if ( index < size )
        {
            pos = check( element, array, prev_index, index );
            prev_index = index;
        }
        else // От prev_index до конца массива
        {
            pos = check( element, array, prev_index, size - 1 );
            end_of_array = true;
        }
        found = ( pos != -1 );
    } while ( !found && !end_of_array );

    return pos != -1 ? pos : size;
}



int main()
{
    // Инициализация
    unsigned int n = 0; // Длина первого массива
    unsigned int m = 0; // Длина второго массива

    // Ввод
    cin >> n >> m;
    if ( n <= 0 || m <= 0 )
    {
        return 1;
    }

    int* A = array_input( n );
    int* B = array_input( m );

    // Расчеты и вывод
    for ( unsigned int i = 0; i < m; ++i )
    {
        cout << index_of_greater_or_equal( B[i], A, n ) << " ";
    }

    // Завершение
    delete A ;
    delete B ;
    return 0;
}
