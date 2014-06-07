/* Уваров Александр, 50 вариант, 3 группа
Задача 3. Декартово дерево
Дано число N < 106 и последовательность пар целых чисел из [-231..231] длиной N.
Построить декартово дерево из N узлов, характеризующихся парами чисел {Xi, Yi}.
Каждая пара чисел {Xi, Yi} определяет ключ Xi и приоритет Yi в декартовом дереве.
Добавление узла в декартово дерево выполняйте второй версией алгоритма, рассказанного на лекции:
При добавлении узла выполняйте спуск по ключу до узла P с меньшим приоритетом. Затем разбивайте
найденное поддерево. Получившиеся два дерева сделайте дочерними для нового узла. Новый узел
вставьте на место узла P.

Построить также наивное дерево поиска по ключам Xi методом из задачи 2.

3_2. Вычислить количество узлов в самом широком слое декартового дерева и количество узлов в самом широком слое наивного дерева поиска. Вывести их разницу.
in
10
5 11
18 8
25 7
50 12
30 30
15 15
20 10
22 5
40 20
45 9

10
38 19
37 5
47 15
35 0
12 3
0 42
31 37
21 45
30 26
41 6

out
1
1
*/

#include <iostream>
#include <stack>

using namespace std;



// Элемент декартова дерева
struct Node
{
    int Key;
    int Priority;
    Node* Left;
    Node* Right;

    Node( int k, int p ) : Key( k ), Priority( p ), Left( 0 ), Right( 0 ) {}
    ~Node()
    {
        delete Left;
        delete Right;
    }
};



// Декартово дерево
class Treap
{
public:
    Treap() : root( 0 ) {}
    ~Treap() { delete root; }
    void Add( int k, int p ); // Добавление элемента
    size_t GetWidestLayer(); // Получение количества узлов в самом широком слое

private:
    Node* root;

    // Разрезание дерева
    void Split( Node* currentNode, int key, Node*& left, Node*& right );
};



void Treap :: Add( int k, int p )
{
    Node* newNode = new Node( k, p );

    if ( root == 0 )
    {
        root = newNode;
        return;
    }

    // Спуск до ключа с меньшим приоритетом
    Node* currentNode = root;
    Node* currentNodeParent = 0;
    while ( true )
    {
        if ( newNode->Priority > currentNode->Priority )
        {
            break;
        }

        if ( newNode->Key < currentNode->Key )
        {
            // Смотрим налево
            if ( currentNode->Left != 0 )
            {
                currentNodeParent = currentNode;
                currentNode = currentNode->Left;
            }
            else
            {
                currentNode->Left = newNode;
                return;
            }
        }
        else
        {
            // Смотрим направо
            if ( currentNode->Right != 0 )
            {
                currentNodeParent = currentNode;
                currentNode = currentNode->Right;
            }
            else
            {
                currentNode->Right = newNode;
                return;
            }
        }
    }

    // Меняем указатель родителя
    if ( currentNodeParent != 0 )
    {
        if ( currentNodeParent->Left == currentNode )
        {
            currentNodeParent->Left = newNode;
        }
        else
        {
            currentNodeParent->Right = newNode;
        }
    }
    else
    {
        // currentNode - корень
        root = newNode;
    }

    Split( currentNode, newNode->Key, newNode->Left, newNode->Right );
}



size_t Treap :: GetWidestLayer()
{
    size_t maxWidth = 0;

    stack<Node*> nodesStack;
    nodesStack.push( root );

    while( !nodesStack.empty() )
    {
        if ( maxWidth < nodesStack.size() )
        {
            maxWidth = nodesStack.size();
        }

        // Формирование следующего слоя
        stack<Node*> newNodesStack;

        while( !nodesStack.empty() )
        {
            Node* currentNode = nodesStack.top();
            nodesStack.pop();
            if ( currentNode->Left != 0 )
            {
                newNodesStack.push( currentNode->Left );
            }
            if ( currentNode->Right != 0 )
            {
                newNodesStack.push( currentNode->Right );
            }
        }

        swap( nodesStack, newNodesStack );
    }

    return maxWidth;
}



void Treap :: Split( Node* currentNode, int key, Node*& left, Node*& right )
{
    if ( currentNode == 0 )
    {
        left = 0;
        right = 0;
    }
    else if ( currentNode->Key <= key )
    {
        Split( currentNode->Right, key, currentNode->Right, right );
        left = currentNode;
    }
    else
    {
        Split( currentNode->Left, key, left, currentNode->Left );
        right = currentNode;
    }
}



// Бинарное дерево
class BinaryTree
{
public:
    BinaryTree() : root( 0 ) {}
    ~BinaryTree() { delete root; }
    void Add( int nodeData ); // Добавление элемента (наивное)
    size_t GetWidestLayer(); // Получение количества узлов в самом широком слое

private:
    Node* root; // Корневой элемент

};



void BinaryTree :: Add( int Key )
{
    Node* newNode = new Node( Key, 0 );

    if ( root == 0 )
    {
        root = newNode;
        return;
    }

    Node* nextNode = root;
    while ( true )
    {
        if ( Key < nextNode->Key )
        {
            // Смотрим налево
            if ( nextNode->Left != 0 )
            {
                nextNode = nextNode->Left;
            }
            else
            {
                nextNode->Left = newNode;
                return;
            }
        }
        else
        {
            // Смотрим направо
            if ( nextNode->Right != 0 )
            {
                nextNode = nextNode->Right;
            }
            else
            {
                nextNode->Right = newNode;
                return;
            }
        }
    }
}


size_t BinaryTree :: GetWidestLayer()
{
    size_t maxWidth = 0;

    stack<Node*> nodesStack;
    nodesStack.push( root );

    while( !nodesStack.empty() )
    {
        if ( maxWidth < nodesStack.size() )
        {
            maxWidth = nodesStack.size();
        }

        stack<Node*> newNodesStack;

        // Формирование следующего слоя
        while( !nodesStack.empty() )
        {
            Node* currentNode = nodesStack.top();
            nodesStack.pop();
            if ( currentNode->Left != 0 )
            {
                newNodesStack.push( currentNode->Left );
            }
            if ( currentNode->Right != 0 )
            {
                newNodesStack.push( currentNode->Right );
            }
        }

        swap( nodesStack, newNodesStack );
    }

    return maxWidth;
}



int main()
{
    size_t elementsNumber = 0;
    cin >> elementsNumber;
    if ( elementsNumber == 0 )
    {
        return 1;
    }

    BinaryTree binaryTree;
    Treap treap;
    for ( size_t i = 0; i < elementsNumber; ++i )
    {
        int k = 0;
        int p = 0;
        cin >> k >> p;
        binaryTree.Add( k );
        treap.Add( k, p );
    }

    const int result = (int)treap.GetWidestLayer() - (int)binaryTree.GetWidestLayer();
    cout << result;
    return 0;
}

