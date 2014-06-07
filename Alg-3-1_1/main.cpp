/* Уваров Александр, 50 вариант, 3 группа
 * Задача 1. Хеш-таблица
Реализуйте структуру данных типа “множество строк” на основе динамической
хеш-таблицы с открытой адресацией. Хранимые строки состоят из строчных латинских
букв. Начальный размер таблицы должент быть равным 8-ми.
Структура данных должна поддерживать операции добавления строки в множество,
удаления строки из множества и проверки принадлежности данной строки множеству.

1_1. Для разрешения коллизий используйте квадратичное пробирование. i-ая проба
g(k, i)=g(k, i-1) + i (mod m). m - степень двойки.

Формат входных данных
Каждая строка входных данных задает одну операцию над множеством. Запись операции
состоит из типа операции и следующей за ним через пробел строки, над которой
проводится операция.
Тип операции  – один из трех символов:
    +  означает добавление данной строки в множество;
    -  означает удаление  строки из множества;
    ?  означает проверку принадлежности данной строки множеству.
При добавлении элемента в множество НЕ ГАРАНТИРУЕТСЯ, что он отсутствует в этом
множестве. При удалении элемента из множества НЕ ГАРАНТИРУЕТСЯ, что он присутствует
в этом множестве.
Формат выходных данных
Программа должна вывести для каждой операции одну из двух строк OK или FAIL, в
зависимости от того, встречается ли данное слово в нашем множестве.

stdin
+ hello
+ bye
? bye
+ bye
- bye
? bye
? hello

stdout
OK
OK
OK
FAIL
OK
FAIL
OK
*/

// Хэш-таблица методом открытой адресации
#include <iostream>
#include <string>
#include <vector>

using namespace std;



const int HashParameter = 29;
const size_t InitialTableSize = 8;
const double C1 = 0.5;
const double C2 = 0.5;



// Хэш-функция
int Hash( const string& s, int M )
{
    int result = 0;
    for ( size_t i = 0; i < s.length(); ++i )
    {
        result = ( result * HashParameter + s[i] ) % M;
    }

    return result;
}



// Элемент таблицы
template<class T>
struct CHashTableNode
{
    CHashTableNode() : Data( T() ), Deleted( false ) {}
    T Data;
    bool Deleted;
};



// Хэш-таблица
template<class T>
class CHashTable
{
public:
    CHashTable( size_t initialSize ) : table( initialSize, 0 ), keysCount( 0 ) {}
    ~CHashTable() { clean(); }
    bool Add( const T& key );
    bool Remove( const T& key );
    bool Find( const T& key ) const;

private:
    vector<CHashTableNode<T>*> table;
    size_t keysCount;

    void reHash();
    void clean();
};



// Добавление
template<class T> bool CHashTable<T> :: Add( const T& key )
{
    // Проверка, нужно ли перехэширование
    if ( keysCount == table.size() )
    {
        reHash();
    }

    size_t hash = Hash( key, table.size() );
    size_t firstDeleted = table.size();
    for ( size_t i = 0; i < table.size(); ++i )
    {
        hash = ( hash + i ) % table.size();

        if ( table[hash] == 0 )
        {
            // Нашли пустую клетку
            if ( firstDeleted == table.size() )
            {
                table[hash] = new CHashTableNode<T>;
                table[hash]->Data = key;
                table[hash]->Deleted = false;
            }
            else
            {
                table[firstDeleted]->Data = key;
                table[firstDeleted]->Deleted = false;
            }

            ++keysCount;
            return true;
        }
        else if ( table[hash]->Deleted )
        {
            // Нашли Deleted
            if ( firstDeleted == table.size() )
            {
                firstDeleted = hash;
            }
        }
        else if ( table[hash]->Data == key )
        {
            // Нашли совпадение
            return false;
        }
    }

    // Не нашли пустую клетку
    if ( firstDeleted != table.size() )
    {
        table[firstDeleted]->Data = key;
        table[firstDeleted]->Deleted = false;
        ++keysCount;
        return true;
    }

    return true;
}



// Удаление
template<class T> bool CHashTable<T> :: Remove( const T& key )
{
    size_t hash = Hash( key, table.size() );
    for ( size_t i = 0; i < table.size(); ++i )
    {
        hash = ( hash + i ) % table.size();

        if ( table[hash] == 0 )
        {
            return false;
        }
        else if ( table[hash]->Data == key )
        {
            // Нашли совпадение
            table[hash]->Data = "";
            table[hash]->Deleted = true;
            --keysCount;
            return true;
        }
    }

    return false;
}



// Поиск
template<class T> bool CHashTable<T> :: Find( const T& key ) const
{
    size_t hash = Hash( key, table.size() );
    for ( size_t i = 0; i < table.size(); ++i )
    {
        hash = ( hash + i ) % table.size();

        if ( table[hash] == 0 )
        {
            return false;
        }
        else if ( table[hash]->Data == key )
        {
            // Нашли совпадение
            return true;
        }
    }

    return false;
}



// Перехэширование
template<class T> void CHashTable<T> :: reHash()
{
    const size_t newSize = table.size() * 2;
    vector<CHashTableNode<T>*> newTable( newSize, 0 );

    for ( size_t i = 0; i < table.size(); ++i )
    {
        if ( table[i] == 0 || table[i]->Deleted )
        {
            continue;
        }

        size_t newHash = Hash( table[i]->Data, newSize );
        for ( size_t j = 0; j < table.size(); ++j )
        {
            newHash = ( newHash + j ) % newSize;

            if ( newTable[newHash] == 0 )
            {
                // Нашли пустую клетку
                newTable[newHash] = table[i];
                break;
            }
        }
    }

    swap( table, newTable );
}



// Очистка
template<class T> void CHashTable<T> :: clean()
{
    for ( size_t i = 0; i < table.size(); ++i )
    {
        if ( table[i] != 0 )
        {
            delete table[i];
        }
    }
}



int main()
{
    CHashTable<string> stringsTable( InitialTableSize );

    while ( true )
    {
        string s;
        cin >> s;
        if ( cin.eof() )
        {
            break;
        }

        if ( s == "+" )
        {
            cin >> s;
            cout << ( stringsTable.Add( s ) ? "OK" : "FAIL" ) << endl;
        }
        else if ( s == "-" )
        {
            cin >> s;
            cout << ( stringsTable.Remove( s ) ? "OK" : "FAIL" ) << endl;
        }
        else if ( s == "?" )
        {
            cin >> s;
            cout << ( stringsTable.Find( s ) ? "OK" : "FAIL" ) << endl;
        }
    }

    return 0;
}



