/*Уваров Александр, 3 группа
 *
 * 54. Составить программу разрезания трехмерной матрицы по заданной строке.
 * Алгоритм преобразования оформить в виде функции, получающей на вход указатель
 * на трехмерную матрицу и ее размеры по каждому измерению. На выход функция
 * должна возвращать указатель на массив результирующих структур (четверной
 * указатель).
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>



// Выделение памяти под трехмерную матрицу
int*** allocate3DMatrix( size_t rows, size_t cols, size_t layers );

// Ввод трехмерной матрицы
bool input3DMatrix( int*** matrix, size_t rows, size_t cols, size_t layers );

// Освобождение памяти из-под трехмерной матрицы
void free3DMatrix( int*** matrix, size_t curLayer, size_t curRow, size_t rows );

// Получение разрезанной матрицы
int**** cut3DMatrix( int*** matrix, size_t rows, size_t cols, size_t layers,
                     size_t cuttingRow );

// Вывод трехмерной матрицы
void print3DMatrix( int*** matrix, size_t rows, size_t cols, size_t layers );



int main(void)
{
    // Секущая строка
    size_t cuttingRow = 0;
    if ( scanf( "%zd", &cuttingRow ) != 1 )
    {
        return 1;
    }

    size_t rows = 0; // Строки
    size_t cols = 0; // Столбцы
    size_t layers = 0; // Слои
    if ( scanf( "%zd%zd%zd", &rows, &cols, &layers ) != 3 ||
         rows == 0 || cols == 0 || layers == 0 ||
         cuttingRow <= 0 || cuttingRow > rows )
    {
        return 2;
    }

    // Матрица
    int*** matrix = allocate3DMatrix( rows, cols, layers );
    if ( matrix == 0 )
    {
        return 3;
    }
    if ( !input3DMatrix( matrix, rows, cols, layers ) )
    {
        free3DMatrix( matrix, layers, rows, rows );
        return 4;
    }

    // Разрезанная матрица
    int**** cuttedMatrix = cut3DMatrix( matrix, rows, cols, layers, cuttingRow );
    if ( cuttedMatrix == 0 )
    {
        free3DMatrix( matrix, layers, rows, rows );
        return 5;
    }

    print3DMatrix( cuttedMatrix[0], cuttingRow - 1, cols, layers );
    print3DMatrix( cuttedMatrix[1], rows - cuttingRow, cols, layers );

    free3DMatrix( matrix, layers, rows, rows );
    free3DMatrix( cuttedMatrix[0], layers, cuttingRow - 1, cuttingRow - 1 );
    free3DMatrix( cuttedMatrix[1], layers, rows - cuttingRow, rows - cuttingRow );
    free( cuttedMatrix );
    return 0;
}



int*** allocate3DMatrix( size_t rows, size_t cols, size_t layers )
{
    // Результат
    int*** resultMatrix = (int***)calloc( layers, sizeof( *resultMatrix ) );
    if ( resultMatrix == 0 )
    {
        return 0;
    }

    // Цикл по слоям
    for ( size_t layer = 0; layer < layers; ++layer )
    {
        // Выделение слоя
        resultMatrix[layer] = (int**)calloc( rows, sizeof( **resultMatrix ) );
        if ( resultMatrix[layer] == 0 )
        {
            for ( size_t l = layer; l >= 1; --l )
            {
                free( resultMatrix[l-1] );
            }
            free( resultMatrix );
            return 0;
        }

        // Цикл по строкам
        for ( size_t row = 0; row < rows; ++row )
        {
            // Выделение строки
            resultMatrix[layer][row] =
                    (int*)calloc( cols, sizeof( ***resultMatrix ) );
            if ( resultMatrix[layer][row] == 0 )
            {
                free3DMatrix( resultMatrix, layer, row, rows );
                return 0;
            }
        }
    }

    return resultMatrix;
}



bool input3DMatrix( int*** matrix, size_t rows, size_t cols, size_t layers )
{
    for ( size_t layer = 0; layer < layers; ++layer )
    {
        for ( size_t row = 0; row < rows; ++row )
        {
            for ( size_t col = 0; col < cols; ++col )
            {
                if ( scanf( "%i", &matrix[layer][row][col] ) != 1 )
                {
                    free3DMatrix( matrix, layers, rows, rows);
                    return false;
                }
            }
        }
    }

    return true;
}



void free3DMatrix(int*** matrix, size_t curLayer, size_t curRow , size_t rows)
{
    // Очистка недовыделенной строки
    if ( curRow < rows )
    {
        for ( size_t row = curRow; row >= 1; --row )
        {
            free( matrix[curLayer][row-1] );
        }

        // Очистка недовыделенного слоя
        free( matrix[curLayer] );
    }

    // Очистка полностью выделенных слоев
    for ( size_t layer = curLayer; layer >= 1; --layer )
    {
        for ( size_t row = rows; row >= 1; --row )
        {
            free( matrix[layer-1][row-1] );
        }

        free( matrix[layer-1] );
    }

    free( matrix );
}



int**** cut3DMatrix( int*** matrix, size_t rows, size_t cols, size_t layers,
                     size_t cuttingRow )
{
    // Указатель на 2 матрицы, равные частям исходной
    int**** resultMatrix = (int****)calloc( 2, sizeof( *resultMatrix ) );
    if ( resultMatrix == 0 )
    {
        return 0;
    }

    // Первая часть
    resultMatrix[0] = allocate3DMatrix( cuttingRow - 1, cols, layers );
    if ( resultMatrix[0] == 0 )
    {
        return 0;
    }

    // Вторая часть
    resultMatrix[1] = allocate3DMatrix( rows - cuttingRow, cols, layers );
    if ( resultMatrix[1] == 0 )
    {
        free3DMatrix( resultMatrix[0], layers, cuttingRow - 1, cuttingRow - 1 );
        return 0;
    }

    // Заполнение первой части
    for ( size_t layer = 0; layer < layers; ++layer )
    {
        for ( size_t row = 0; row < cuttingRow - 1; ++row )
        {
            for ( size_t col = 0; col < cols; ++col )
            {
                resultMatrix[0][layer][row][col] = matrix[layer][row][col];
            }
        }
    }

    // Заполнение второй части
    for ( size_t layer = 0; layer < layers; ++layer )
    {
        for ( size_t row = cuttingRow; row < rows; ++row )
        {
            for ( size_t col = 0; col < cols; ++col )
            {
                resultMatrix[1][layer][row - cuttingRow][col] =
                        matrix[layer][row][col];
            }
        }
    }

    return resultMatrix;
}



void print3DMatrix( int*** matrix, size_t rows, size_t cols, size_t layers )
{
    for ( size_t layer = 0; layer < layers; ++layer )
    {
        for ( size_t row = 0; row < rows; ++row )
        {
            for ( size_t col = 0; col < cols; ++col )
            {
                printf( "%i ", matrix[layer][row][col] );
            }
            printf( "\n" );
        }
        printf( "\n" );
    }
}
