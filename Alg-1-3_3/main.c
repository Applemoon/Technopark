#include <stdio.h>
#include <stdlib.h>



// allocate memory for array
int* array_input(size_t size)
{
    int* array = (int*)calloc(size, sizeof(*array));

    if (array != NULL)
    {
        for (size_t i = 0; i < size; ++i)
        {
            int scanf_count = scanf("%i", &array[i]);
            if (scanf_count != 1)
            {
                return NULL;
            }
        }
    }
    else
    {
        free(array);
    }

    return array;
}



int main(void)
{
    unsigned int n = 0;
    unsigned int m = 0;

    // input
    int scanf_count = scanf("%i", &n);
    if (scanf_count != 1)
    {
        return 1;
    }
    int* ar_n = array_input((size_t)n);
    if (ar_n == NULL)
    {
        return 1;
    }

    scanf_count = scanf("%i", &m);
    if (scanf_count != 1)
    {
        return 1;
    }
    int* ar_m = array_input((size_t)m);
    if (ar_m == NULL)
    {
        return 1;
    }

    size_t n_count = 0;
    size_t m_count = 0;

    int result = 0;

    // main loop
    while (n_count < n || m_count < m)
    {
        if (ar_n[n_count] == ar_m[m_count])
        {
            ++result;
            ++n_count;
            ++m_count;
        }
        else if (ar_n[n_count] < ar_m[m_count])
        {
            ++n_count;
        }
        else
        {
            ++m_count;
        }
    }

    // output
    printf("%i\n", result);

    free(ar_n);
    free(ar_m);

    return 0;
}

