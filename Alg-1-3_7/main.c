#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>




// find next to kill
size_t next_victim( size_t current, bool* array, unsigned int n, unsigned int k )
{
    size_t counter = 0;
    while (counter != k)
    {
        ++current;
        if (current == n)
        {
            current = 0;
        }
        if (array[current])
        {
            ++counter;
        }
    }
    return current;
}



int main(void)
{
    unsigned int n = 0;
    unsigned int k = 0;

    // input
    if (scanf("%i", &n) != 1)
    {
        return 1;
    }

    if (scanf("%i", &k) != 1)
    {
        return 1;
    }

    bool* array = (bool*)calloc(n, sizeof(*array));
    if (array == NULL)
    {
        return 1;
    }

    for (size_t i = 0; i < n; ++i)
    {
        array[i] = true;
    }

    // shooting loop
    size_t current = n-1;
    for (size_t i = 0; i < n - 1; ++i)
    {
        current = next_victim(current, array, n, k);
        array[current] = false;
    }

    // output
    for (size_t i = 0; i < n; ++i)
    {
        if (array[i])
        {
            printf("%i\n", i+1);
            break;
        }
    }

    free(array);
    return 0;
}

