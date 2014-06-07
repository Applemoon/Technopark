/* Уваров Александр, 50 вариант
 *
 * 1_3. Сортировка пузырьком.
 */

#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::vector;
using std::swap;



// Сортировка пузырьком
void bubbleSort( vector<int>& array );



int main()
{
    vector<int> array;
    int value = 0;
    while( true )
    {
        cin >> value; // Ввод
        if ( cin.eof() ) // Linux - Ctrl+D
        {
            break;
        }
        array.push_back( value );
    }

    bubbleSort( array );

    for ( size_t i = 0; i < array.size(); ++i )
    {
        cout << array[i] << " ";
    }

    return 0;
}



// Сортировка пузырьком
void bubbleSort( vector<int>& array )
{
    for ( size_t i = array.size(); i >= 1; --i )
    {
        unsigned int swapsCount = 0;
        for ( size_t j = 0; j < i-1; ++j )
        {
            if ( array[j] > array[j+1] )
            {
                swap( array[j], array[j+1] );
                ++swapsCount;
            }
        }
        if ( swapsCount == 0 )
        {
            return;
        }
    }
}
