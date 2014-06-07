#include <stdio.h>
#include <stdlib.h>



// Очистка выделенной памяти
void free_matrix(int **matrix, size_t last_row)
{
    for (size_t i = last_row; i >= 1; --i)
    {
        free(matrix[i-1]);
    }
    free(matrix);
}



// Выделение памяти под матрицу
int** alloc_for_matrix(size_t rows, size_t cols)
{
    int** result_matrix = NULL;
    result_matrix = (int**)calloc(rows, sizeof(*result_matrix));

    if (result_matrix != NULL)
    {
        for (size_t row = 0; row < rows; ++row)
        {
            result_matrix[row] = (int*)calloc(cols, sizeof(**result_matrix));

            // Проверка
            if (result_matrix[row] == NULL && row != 0)
            {
                free_matrix(result_matrix, row - 1);
                return NULL;
            }
        }
    }

    return result_matrix;
}



// Получение указателя на матрицу, содержащую матрицу элементов диагонали
// и матрицу остальных элементов
int*** get_final_matrix(int** matrix, unsigned int rows, unsigned int cols)
{
    int*** result_matrix = NULL;
    result_matrix = (int***)calloc(2, sizeof(*result_matrix));

    if (result_matrix != NULL)
    {
        // Выделение памяти под первую матрицу
        result_matrix[0] = alloc_for_matrix(rows, cols);
        if (result_matrix[0] == NULL)
        {
            free(result_matrix);
            return NULL;
        }

        // Выделение памяти под вторую матрицу
        result_matrix[1] = alloc_for_matrix(rows, cols);
        if (result_matrix[1] == NULL)
        {
            free_matrix(result_matrix[0], rows);
            free(result_matrix);
            return NULL;
        }

        // Заполнение матриц
        for (size_t row = 0; row < rows; ++row)
        {
            for (size_t col = 0; col < cols; ++col)
            {
                // Если элемент лежит на диагонали
                if (row == col || row == cols - 1 - col)
                {
                    result_matrix[0][row][col] = matrix[row][col];
                }
                else
                {
                    result_matrix[1][row][col] = matrix[row][col];
                }
            }
        }
    }
    else
    {
        printf("Can't allocate memory for matrix\n");
        free(result_matrix);
    }

    return result_matrix;
}



int main(void)
{
    // Задание размеров матрицы
    unsigned int rows = 0;
    unsigned int cols = 0;

    int scanf_count = scanf("%i%i", &rows, &cols);

    if (scanf_count != 2 || rows != cols || rows == 0 || cols == 0)
    {
        printf("Wrong matrix size input\n");
        return 1;
    }

    // Выделение памяти под матрицу
    int** matrix = alloc_for_matrix(rows, cols);
    if (matrix == NULL)
    {
        printf("Can't allocate memory for matrix\n");
        return 1;
    }

    // Ввод матрицы
    for (size_t row = 0; row < rows; ++row)
    {
        for (size_t col = 0; col < cols; ++col)
        {
            scanf_count = scanf("%d", &matrix[row][col]);
            if (scanf_count != 1)
            {
                printf("Wrong matrix input\n");
                return 1;
            }
        }
    }

    // Получение конечной матрицы
    int*** final_matrix = get_final_matrix(matrix, rows, cols);
    if (final_matrix == NULL)
    {
        printf("Can't get final matrix");
        free_matrix(matrix, (size_t)rows);
        return 1;
    }

    // Вывод
    for (size_t row = 0; row < rows; ++row)
    {
        for (size_t col = 0; col < cols; ++col)
        {
            printf("%i ", final_matrix[0][row][col]);
        }
        printf("\n");
    }

    printf("\n");

    for (size_t row = 0; row < rows; ++row)
    {
        for (size_t col = 0; col < cols; ++col)
        {
            printf("%i ", final_matrix[1][row][col]);
        }
        printf("\n");
    }

    // Очистка
    free_matrix(final_matrix[0], (size_t)rows);
    free_matrix(final_matrix[1], (size_t)rows);
    free(final_matrix);
    free_matrix(matrix, (size_t)rows);

    return 0;
}
