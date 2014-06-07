#include <iostream>

using namespace std;

void filterPrimes( bool* isPrime, int maxN )
{
    for ( int i = 0; i * i <= maxN; ++i )
    {
        if ( isPrime[i] )
        {
            for ( int j = i * i; j <= maxN; j += i )
            {
                isPrime[j] = false;
            }
        }
    }
}

int main()
{
    std::cout << "!!!";
    int maxN = 0;
    std::cin >> maxN;

    bool* isPrime = new bool[maxN + 1];
    for ( int i = 0; i <= maxN; ++i )
    {
        isPrime[i] = true;
    }

    filterPrimes( isPrime, maxN );
    for ( int i = 2; i <= maxN; ++i )
    {
        if ( isPrime[i] )
        {
            std::cout << i << " ";
        }
    }

    delete [] isPrime;
    return 0;
}

