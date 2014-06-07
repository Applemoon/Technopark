/* Уваров Александр, 50 вариант, 3 группа
Задача 2. Порядок обхода
Дано число N < 106 и последовательность целых чисел из [-231..231] длиной N.
Требуется построить бинарное дерево, заданное наивным порядком вставки.
Т.е., при добавлении очередного числа K в дерево с корнем root, если root→Key ≤ K,
то узел K добавляется в правое поддерево root; иначе в левое поддерево root.

2_3. Выведите элементы в порядке post-order (снизу вверх).
in
3
2 1 3
3
1 2 3
3
3 1 2

out
1 3 2
3 2 1
2 1 3
*/

#include <iostream>

using namespace std;



// Узел двоичного дерева
struct BinaryTreeNode
{
    int Data;
    BinaryTreeNode* Left;
    BinaryTreeNode* Right;

    BinaryTreeNode( int d, ) : Data( d ), Left( 0 ), Right( 0 ) {}
    ~BinaryTreeNode()
    {
        delete Left;
        delete Right;
    }
};



// Бинарное дерево
class BinaryTree
{
public:
    BinaryTree() : root( 0 ) {}
    ~BinaryTree() { delete root; }
    void Add( int nodeData ); // Добавление элемента (наивное)
    void TraverseDFS() // Обход в глубину
    { TraverseDFS( root ); }

private:
    BinaryTreeNode* root; // Корневой элемент

    void Visit( BinaryTreeNode* node ) // Вывод элемента
    { cout << node->Data << " "; }
    void TraverseDFS( BinaryTreeNode *node );
};



void BinaryTree :: Add( int data )
{
    BinaryTreeNode* newNode = new BinaryTreeNode( data );

    if ( root == 0 )
    {
        root = newNode;
        return;
    }

    BinaryTreeNode* nextNode = root;
    while ( true )
    {
        if ( data < nextNode->Data )
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
    };


}



void BinaryTree :: TraverseDFS( BinaryTreeNode *node )
{
    if ( node == 0 )
    {
        return;
    }

    TraverseDFS( node->Left );
    TraverseDFS( node->Right );
    Visit( node );
}



int main()
{
    size_t elementsNumber = 0;
    cin >> elementsNumber;
    if ( elementsNumber == 0 )
    {
        return 1;
    }

    BinaryTree tree;
    for ( size_t i = 0; i < elementsNumber; ++i )
    {
        int data = 0;
        cin >> data;
        tree.Add( data );
    }

    tree.TraverseDFS();

    return 0;
}

