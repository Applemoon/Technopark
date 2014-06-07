/* Уваров Александр, 50 вариант

3_4. Закраска прямой 2. (сортировка слиянием)
На числовой прямой окрасили N отрезков. Известны координаты левого и правого
концов каждого отрезка (Li и Ri). Найти сумму длин частей числовой прямой,
окрашенных ровно в один слой.

In
3
1 4
2 5
7 8

out
3
*/

#include <iostream>
#include <vector>
#include <algorithm>

using std::cin;
using std::cout;
using std::vector;
using std::sort;



// Отрезок
struct Line
{
    int x1;
    int x2;

    Line( int ax1, int ax2 ) :
        x1( ax1 ), x2( ax2 ) {}

    bool operator<( const Line& p ) const
    {
        if ( x1 != p.x1 )
        {
            return x1 < p.x1;
        }
        else
        {
            return x2 < p.x2;
        }
    }

    bool operator>( const Line& p ) const
    {
        return ( p < *this );
    }
};



// Слияние двух векторов
vector<Line> merge( vector<Line> a, vector<Line> b )
{
    size_t i = 0;
    size_t j = 0;
    vector<Line> result;

    while ( i < a.size() && j < b.size() )
    {
        if ( a[i] < b[j] )
        {
            result.push_back( a.at( i++ ) );
        }
        else
        {
            result.push_back( b.at( j++ ) );
        }
    }

    if ( i == a.size() )
    {
        while ( j < b.size() )
        {
            result.push_back( b.at( j++ ) );
        }
    }
    else
    {
        while ( i < a.size() )
        {
            result.push_back( a.at( i++ ) );
        }
    }

    return result;
}



// Сортировка слиянием
vector<Line> sort( vector<Line> lines )
{
    size_t vecsCount = ( lines.size() + 1 ) / 2;

    vector< vector<Line> > resultLines;
    for ( size_t i = 0; i < vecsCount; ++i )
    {
        vector<Line> linesPair;

        // Разбиение на парные массивы и их упорядочивание
        if ( 2*i + 1 >= lines.size() ) // Исходный вектор нечетный
        {
            linesPair.push_back( lines[2*i] );
        }
        else
        {
            Line l1 = lines[2*i];
            Line l2 = lines[2*i + 1];
            if ( l1 < l2 )
            {
                linesPair.push_back( l1 );
                linesPair.push_back( l2 );
            }
            else
            {
                linesPair.push_back( l2 );
                linesPair.push_back( l1 );
            }
        }

        resultLines.push_back( linesPair );
    }

    // Слияние всех пар в 1 массив
    while ( vecsCount > 1 )
    {
        const size_t newVecsCount = ( vecsCount + 1 ) / 2;
        vector< vector<Line> > tempLines;

        for ( size_t i = 0; i < newVecsCount; ++i )
        {
            if ( i > resultLines.size() ) // Если число подмассивов нечетное
            {
                tempLines.push_back( resultLines[2*i] );
            }
            else
            {
                vector<Line> l1 = resultLines[2*i];
                vector<Line> l2 = resultLines[2*i + 1];
                tempLines.push_back( merge( l1, l2 ) );
            }
        }

        resultLines = tempLines;
        vecsCount = resultLines.size();
    }

    return resultLines[0];
}



// Нахождение длины отрезков, окрашенных 1 раз
size_t get1PaintedLength( vector<Line> lines, int leftBorder, int rightBorder )
{
    size_t length = 0; // Результат
    size_t firstLine = 0; // С какого отрезка проверяем
    size_t lastLine = 0; // До какого отрезка проверяем (не включая)
    for ( size_t i = 0; i < lines.size(); ++i )
    {
        if ( lines[i].x1 == leftBorder )
        {
            lastLine = i + 1;
        }
        else
        {
            break;
        }
    }

    // Идем по каждой координате
    for ( int x = leftBorder; x < rightBorder; ++x )
    {
        // Ищем все слои на данной координате
        size_t layers = 0;

        // Проходим по всем отрезкам
        size_t i = firstLine;
        while ( i <= lastLine )
        {
            if ( i == firstLine && x >= lines[firstLine].x2 && firstLine < lastLine - 1 )
            {
                // Сдвигаем начало проверки
                ++firstLine;
            }
            else
            {
                if ( i == lastLine && lastLine < lines.size() )
                {
                    if ( x >= lines[lastLine].x1 )
                    {
                        // Сдвигаем конец проверки
                        ++lastLine;
                    }
                }

                // Считаем количество слоев
                if ( i < lines.size() )
                {
                    if ( lines[i].x1 <= x && x < lines[i].x2 )
                    {
                        ++layers;
                    }
                }
            }

            ++i;
        }

        if ( layers == 1 )
        {
            ++length;
        }
    }

    return length;
}



int main()
{
    size_t linesNumber = 0; // Число отрезков
    cin >> linesNumber;
    if ( linesNumber == 0 )
    {
        return 1;
    }

    int leftBorder = 0; // Левая граница всех закрашенных участков
    int rightBorder = 0; // Правая граница всех закрашенных участков

    vector<Line> lines; // Массив отрезков
    int x1 = 0; // Переменные для ввода координат
    int x2 = 0;

    // Первый отрезок вводим отдельно, чтобы задать им границы
    cin >> x1 >> x2;
    if ( x1 > x2 )
    {
        return 2;
    }

    lines.push_back( Line( x1, x2 ) );
    leftBorder = x1;
    rightBorder = x2;

    // Ввод остальных отрезков
    for ( size_t i = 1; i < linesNumber; ++i )
    {
        cin >> x1 >> x2;
        if ( x1 > x2 )
        {
            return 2;
        }

        lines.push_back( Line( x1, x2 ) );

        // Смещение границ
        if ( leftBorder > x1 )
        {
            leftBorder = x1;
        }
        if ( rightBorder < x2 )
        {
            rightBorder = x2;
        }
    }

    // Сортировка
    lines = sort( lines );

    // Вывод
    cout << get1PaintedLength( lines, leftBorder, rightBorder );

    return 0;
}

