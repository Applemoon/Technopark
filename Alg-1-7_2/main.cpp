/*Уваров Александр, 3 группа, 50 вариант

7_2. Быстрое сложение.
Для сложения чисел используется старый компьютер. Время, затрачиваемое на
нахождение суммы двух чисел равно их сумме.
Таким образом для нахождения суммы чисел 1,2,3 может потребоваться разное время,
в зачисимости от порядка вычислений.
((1+2)+3) -> 1+2 + 3+3 = 9
((1+3)+2) -> 1+3 + 4+2 = 10
((2+3)+1) -> 2+3 + 5+1 = 11
Требуется написать программу, которая определяет минимальное время, достаточное
для вычисления суммы заданного набора чисел.
Формат входных данных. Вначале вводится n - количество чисел. Затем вводится n
строк - значения чисел (значение каждого числа не превосходит 10^9, сумма всех
чисел не превосходит 2*10^9).
Формат выходных данных. Натуральное число - минимальное время.
*/

#include <iostream>

using std::cin;
using std::cout;
using std::swap;



// Восстановление свойств кучи
void Heapify( int* numbers, unsigned int n, unsigned int k )
{
    const unsigned int left = 2 * k + 1;
    const unsigned int right = 2 * k + 2;

    // Поиск большего сына, если такой есть
    unsigned int largest = k;
    if ( left < n && numbers[left] > numbers[k] )
    {
        largest = left;
    }
    if ( right < n && numbers[right] > numbers[largest] )
    {
        largest = right;
    }

    // Если больший сын есть, проталкиваем корень в него
    if ( largest != k )
    {
        swap( numbers[k], numbers[largest] );
        Heapify( numbers, n, largest );
    }
}



// Определение минимального времего, достаточного для вычисления суммы
// заданного набора чисел
unsigned int MinTime( int* numbers, unsigned int n )
{
    int sum = 0; // Сумма

    // TODO непонятно

    return sum;
}



int main()
{
    unsigned int n = 0; // Количество чисел
    cin >> n;

    int* numbers = new int[n]; // Массив чисел
    for ( unsigned int i = 0; i < n; ++i )
    {
        cin >> numbers[i];
    }

    // Построение кучи из неупорядоченного массива
    for ( int i = n/2 - 1; i >= 0; --i )
    {
        Heapify( numbers, n, i );
    }

    cout << MinTime( numbers, n ); // Результат
    return 0;
}

