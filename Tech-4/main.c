/* Уваров Александр, вариант 54
 * Создать структуру для хранения информации об обменных курсах иностранных
 * валют: наименовании банка, валютной паре, значении курса и комиссии банка.
 * Составить с ее использованием программу поиска оптимальной стратегии обмена
 * одной валюты на другую при условии, что возможность прямого обмена исходной
 * валюты на целевую отсутствует.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

// 5 a 2 1 2 10 b 3 1 4 10 c 3 2 1 10 d 4 2 2 10 e 4 3 4 10
// TODO вывести путь
// TODO разбить большую функцию на поменьше
// TODO обход от минимальной до максимальной заданныйх валют

size_t CurrencyTypesNumber = 10; // TODO 21;
// Валютная пара
struct CurrencyPair
{
    char bank[30];
    size_t baseCurrency; // Базовая валюта
    size_t counterCurrency; // Котируемая валюта
    double exchangeRate; // Курс
    double commission; // Комиссия в процентах
};



// Вычисление курса обмена с учетом комиссии
double getFinalExchangeRate( double counterExchangeRate, double newExchangeRate, double commission )
{
    return counterExchangeRate * newExchangeRate * 100 / ( 100 - commission );
}



// Поиск пути обмена
struct CurrencyPair* getCurrencyPairPath( struct CurrencyPair* currencyPairs,
                                          size_t currencyPairsNumber,
                                          size_t baseCurrency,
                                          size_t counterCurrency,
                                          size_t* pathSize,
                                          double* finalExchangeRate )
{
    // Массив, содержащий конечные курсы из текущей валюты к остальным
    double* exchangeRates = (double*)calloc( CurrencyTypesNumber, sizeof( *exchangeRates ) );
    if ( exchangeRates == 0 )
    {
        return 0;
    }

    for ( size_t i = 0; i < CurrencyTypesNumber; ++i )
    {
        exchangeRates[i] = 0;
    }
    exchangeRates[counterCurrency] = 1; // Курс исходной валюты к самой себе

    // Массив, содержащий последние отрезки пути обмена из текущей валюты к остальным
    struct CurrencyPair* pathToEveryCurrency = (struct CurrencyPair*)calloc(
                CurrencyTypesNumber-1, sizeof( *pathToEveryCurrency ) );
    if ( pathToEveryCurrency == 0 )
    {
        free( exchangeRates );
        return 0;
    }

    // Массив отмеченных посещенных узлов (валют)
    bool* visitedCurrencyTypes = (bool*)calloc(
                CurrencyTypesNumber, sizeof( *visitedCurrencyTypes ) );
    if ( visitedCurrencyTypes == 0 )
    {
        free( pathToEveryCurrency );
        free( exchangeRates );
        return 0;
    }

    // Задаем все валюты как непосещенные
    for ( size_t i = 0; i < CurrencyTypesNumber; ++i )
    {
        visitedCurrencyTypes[i] = false;
    }

    while ( 1 )
    {
        // Ищем непосещенный узел с наименьшим курсом
        bool unvisitedTypesExist = false; // Есть ли непосещенные узлы
        bool visited = false; // Отметка о посещении узла на этой итерации
        double minExchangeRate = 0; // Наименьший курс
        size_t minExchangeRateCurrency = 0; // Индекс найденной валюты

        for ( size_t i = 0; i < CurrencyTypesNumber; ++i )
        {
            // Обходим все непосещенные валюты
            if ( visitedCurrencyTypes[i] == false )
            {
                unvisitedTypesExist = true;

                if ( exchangeRates[i] != 0 && ( exchangeRates[i] < minExchangeRate || minExchangeRate == 0 ) )
                {
                    minExchangeRate = exchangeRates[i];
                    minExchangeRateCurrency = i;
                    visited = true;
                }
            }
        }

        if ( !unvisitedTypesExist || !visited )
        {
            break;
        }

        // Считаем соседние валюты. Для этого смотрим все возможности обмена текущей валюты
        for ( size_t i = 0; i < currencyPairsNumber; ++i )
        {
            if ( minExchangeRateCurrency == currencyPairs[i].counterCurrency ) // Котируемая валюта совпадает с искомой
            {
                // Старый и новый курсы базовой валюты
                const double oldExchangeRate = exchangeRates[currencyPairs[i].baseCurrency];
                const double newExchangeRate = getFinalExchangeRate( exchangeRates[minExchangeRateCurrency],
                                                                currencyPairs[i].exchangeRate,
                                                                currencyPairs[i].commission );
                if ( newExchangeRate < oldExchangeRate || oldExchangeRate == 0 )
                {
                    exchangeRates[currencyPairs[i].baseCurrency] = newExchangeRate;
                    pathToEveryCurrency[currencyPairs[i].baseCurrency] = currencyPairs[i];
                }
            }
        }

        // Отмечаем валюту как посещенную
        visitedCurrencyTypes[minExchangeRateCurrency] = true;
    }

    // Формирование пути
    *pathSize = 0;
    size_t currencyType = baseCurrency;
    while ( currencyType != counterCurrency ) // Идем от базовой валюты к котируемой
    {
        currencyType = pathToEveryCurrency[currencyType].counterCurrency;
        ++(*pathSize);
    }

    struct CurrencyPair* path = (struct CurrencyPair*)calloc( *pathSize, sizeof( *path ) );
    if ( path == 0 )
    {
        free( pathToEveryCurrency );
        free( exchangeRates );
        free( visitedCurrencyTypes );
        return 0;
    }

    size_t k = *pathSize - 1;
    currencyType = baseCurrency;

    while ( currencyType != counterCurrency ) // Идем от базовой валюты к котируемой
    {
        path[k--] = pathToEveryCurrency[currencyType];
        currencyType = pathToEveryCurrency[currencyType].counterCurrency;
    }

    free( pathToEveryCurrency );
    free( exchangeRates );
    free( visitedCurrencyTypes );

    *finalExchangeRate = exchangeRates[baseCurrency];
    return path;
}



int main()
{
    // 0. Вывод подсказки
    printf( "1 - RUB\n2 - EUR\n3 - USD\n4 - CHF\n5 - GBP\n6 - JPY\n7 - AUD\n8 - CAD\n9 - NZD\n10 - DKK\n11 - NOK\n" );
    printf( "12 - SEK\n13 - CCK\n14 - SKK\n15 - SGD\n16 - HUF\n17 - PLN\n18 - HKD\n19 - LVL\n20 - MXN\n21 - ZAR\n" );

    printf( "------------------------------\n\n" );

    // 1. Ввод валютных пар
    size_t currencyPairNumber = 0;
    printf( "Write currency pairs number\n" );
    if ( scanf( "%i", &currencyPairNumber ) != 1 )
    {
        printf( "Input error\n" );
        return 1;
    }

    struct CurrencyPair* currencyPairs = (struct CurrencyPair*)calloc( currencyPairNumber,
                                                                       sizeof( *currencyPairs ) );
    if ( currencyPairs == 0 )
    {
        return 2;
    }

    for ( size_t i = 0; i < currencyPairNumber; ++i )
    {
        printf( "\n------------------------------\n" );

        // 1.1 Ввод названия банка
        printf( "Write bank name (without spaces)\n" );
        if ( scanf( "%29s", currencyPairs[i].bank ) != 1  )
        {
            printf( "Input error\n" );
            free( currencyPairs );
            return 3;
        }

        // 1.2 Ввод базовой валюты банка
        printf( "Write base currency code for this bank (0 - %i)\n", CurrencyTypesNumber - 1 );
        if ( scanf( "%i", &(currencyPairs[i].baseCurrency) ) != 1 ||
             currencyPairs[i].baseCurrency >= CurrencyTypesNumber )
        {
            printf( "Input error\n" );
            free( currencyPairs );
            return 4;
        }

        // 1.3 Ввод котируемой валюты банка
        printf( "Write counter currency code for this bank (0 - %i)\n", CurrencyTypesNumber - 1 );
        if ( scanf( "%zd", &(currencyPairs[i].counterCurrency) ) != 1 ||
             currencyPairs[i].counterCurrency >= CurrencyTypesNumber )
        {
            printf( "Input error\n" );
            free( currencyPairs );
            return 5;
        }
        else if ( currencyPairs[i].counterCurrency == currencyPairs[i].baseCurrency )
        {
            printf( "Base and counter currencies can't be equal\n" );
            free( currencyPairs );
            return 6;
        }

        // 1.4 Ввод курса обмена
        printf( "Write bank exchange rate\n" );
        if ( scanf( "%lf", &currencyPairs[i].exchangeRate ) != 1 ||
             currencyPairs[i].exchangeRate <= 0 )
        {
            printf( "Input error\n" );
            free( currencyPairs );
            return 7;
        }

        // 1.5 Ввод комиссии банка
        printf( "Write bank commission as a percentage (0%% - 100%%)\n" );
        if ( scanf( "%lf", &currencyPairs[i].commission ) != 1 ||
             currencyPairs[i].commission < 0 || currencyPairs[i].commission > 100 )
        {
            printf( "Input error\n" );
            free( currencyPairs );
            return 8;
        }
    }

    // 2. Ввод базовой и котируемой валют
    printf( "\n------------------------------\n" );
    // 2.1 Ввод базовой валюты
    printf( "Write base currency code (0 - %i)\n", CurrencyTypesNumber - 1 );
    size_t baseCurrency; // Базовая валюта
    if ( scanf( "%zd", &baseCurrency ) != 1 || baseCurrency >= CurrencyTypesNumber )
    {
        printf( "Input error\n" );
        free( currencyPairs );
        return 9;
    }

    // 2.1 Ввод котируемой валюты
    printf( "Write current currency code (0 - %i)\n", CurrencyTypesNumber - 1 );
    size_t counterCurrency; // Котируемая валюта
    if ( scanf( "%zd", &counterCurrency ) != 1 || counterCurrency >= CurrencyTypesNumber )
    {
        printf( "Input error\n" );
        free( currencyPairs );
        return 10;
    }

    // 3. Поиск пути
    size_t pathSize = 0;
    double finalExchangeRate = 0;
    struct CurrencyPair *currencyPairsPath =
            getCurrencyPairPath( currencyPairs, currencyPairNumber,
                                 baseCurrency, counterCurrency, &pathSize, &finalExchangeRate);
    if ( currencyPairsPath == 0 )
    {
        printf( "Error\n" );
        free( currencyPairs );
        return 11;
    }

    // 4. Вывод пути
    printf( "\n------------------------------\n" );
    for ( size_t i = 0; i < pathSize; ++i )
    {
        printf( "%i. %s\n", i+1, currencyPairsPath[i].bank );
        printf( "Exchange rate - %lf\n", currencyPairsPath[i].exchangeRate );
        printf( "Commission - %lf%%\n", currencyPairsPath[i].commission );
        printf( "%i -> %i\n\n", currencyPairsPath[i].counterCurrency,
                            currencyPairsPath[i].baseCurrency );
    }
    printf( "Final exchange rate - %lf\n", finalExchangeRate );

    free( currencyPairs );
    free( currencyPairsPath );
    return 0;
}

