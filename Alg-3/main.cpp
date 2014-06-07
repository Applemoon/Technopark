// Хэш-таблица методом цепочек
#include <iostream>
#include <string>
#include <vector>

using namespace std;



int HashParameter = 29;
size_t InitialTableSize = 8;



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



// Элемент цепочки
template<class T>
struct CHashTableNode
{
    T Data;
    CHashTableNode<T>* Next;
};



// Хэш-таблица
template<class T>
class CHashTable
{
public:
    CHashTable( size_t initialSize );
    ~CHashTable() { clean(); }
    bool Add( const T& key ); // Добавление
    bool Remove( const T& key ); // Удаление
    bool Find( const T& key ) const; // Поиск

private:
    vector<CHashTableNode<T>*> table;
    size_t keysCount;

    void reHash(); // Перехэширование
    void clean(); // Очистка
};



template<class T> CHashTable<T> :: CHashTable( size_t initialSize ) :
    table( initialSize, 0 ), keysCount( 0 )
{
}



template<class T> bool CHashTable<T> :: Add( const T& key )
{
    // Проверка, нужно ли перехэширование
    if ( keysCount == table.size() )
    {
        reHash();
    }

    const int hash = Hash( key, table.size() );

    // Поиск элемента
    for ( CHashTableNode<T>* current = table[hash]; current != 0; current = current->Next )
    {
        if ( current->Data == key )
        {
            return false;
        }
    }

    CHashTableNode<T>* newNode = new CHashTableNode<T>;
    newNode->Data = key;
    newNode->Next = table[hash];
    table[hash] = newNode;

    ++keysCount;
    return true;
}



template<class T> bool CHashTable<T> :: Remove( const T& key )
{
    const int hash = Hash( key, table.size() );

    // Элементов нет
    if ( table[hash] == 0 )
    {
        return false;
    }

    // Если элемент нашелся первым
    if ( table[hash]->Data == key )
    {
        CHashTableNode<T>* toDelete = table[hash];
        table[hash] = toDelete->Next;
        delete toDelete;
        --keysCount;
        return true;
    }

    CHashTableNode<T>* prev = table[hash];
    for ( CHashTableNode<T>* current = table[hash]->Next; current != 0;
          current = current->Next )
    {
        if ( current->Data == key )
        {
            prev->Next = current->Next;
            delete current;
            --keysCount;
            return true;
        }
        prev = current;
    }

    return false;
}



template<class T> bool CHashTable<T> :: Find( const T& key ) const
{
    const int hash = Hash( key, table.size() );

    for ( CHashTableNode<T>* current = table[hash]; current != 0; current = current->Next )
    {
        if ( current->Data == key )
        {
            return true;
        }
    }

    return false;
}



template<class T> void CHashTable<T> :: reHash()
{
    const size_t newSize = table.size() * 2;
    vector<CHashTableNode<T>*> newTable( newSize, 0 );

    for ( size_t i = 0; i < table.size(); ++i )
    {
        for ( CHashTableNode<T>* current = table[i]; current != 0;
              current = current->Next )
        {
            const int newHash = Hash( current->Data, newSize );
            CHashTableNode<T>* newNode = new CHashTableNode<T>;
            newNode->Data = current->Data;
            newNode->Next = newTable[newHash];
            newTable[newHash] = newNode;
        }
    }

    clean();
    swap( table, newTable );
}



template<class T> void CHashTable<T> :: clean()
{
    for ( size_t i = 0; i < table.size(); ++i )
    {
        for ( CHashTableNode<T>* current = table[i]; current != 0; )
        {
            CHashTableNode<T>* toDelete = current;
            current = current->Next;
            delete toDelete;
        }

        table[i] = 0;
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

