#include <iostream>
#include <algorithm>

using namespace std;

class BST
{
    int data;
    BST* left, * right;

public:
    BST();

    BST(int);

    BST* insert(BST*, int);
    BST* remove(BST*, int);

    void in_order(BST*);
    bool search(BST*, int);
    void pretty_print(const std::string&, const BST*, bool);
    int height(BST*);
    int node_count(BST*);
};

// Создание пустого дерева (без параметров)
BST::BST() : data(0), left(NULL), right(NULL)
{
}


// Создание дерева
BST::BST(int value)
{
    // Инициализация: значение в корне, указатели на ветви
    data = value;
    left = right = NULL;
}

// Вставка элемента в дерево
BST* BST::insert(BST* root, int value)
{
    // Если корень пуст, то ключ назначить корнем
    if (!root) return new BST(value);

    // Если ключ больше, чем значение на текущей позиции
    if (value > root->data)
    {
        // Вставить ключ в правую ветвь
        root->right = insert(root->right, value);
    }
    else
    {
        // Вставить ключ в левую ветвь
        root->left = insert(root->left, value);
    }
    return root;
}

// Функция обхода дерева в порядке возрастания
void BST::in_order(BST* root)
{

    if (!root) {
        return;
    }

    // <В квадратике с черточками> Рекурсивный вызов in_order
    in_order(root->left);
    // Печать ветвей до тех пор, пока node != NULL
    cout << root->data << endl;
    in_order(root->right);
}

// Поиск ключа в дереве
bool BST::search(BST* node, int key)
{
    // Если дерево пустое
    if (node == NULL)
        return false;

    // Если дерево содержит единственный искомый элемент
    if (node->data == key)
        return true;

    //<В квадратике с черточками> Рекурсивный поиск по левой ветви
    bool res1 = search(node->left, key);
    // Если в левой ветви элемент найден
    if (res1) return true;

    //<В квадратике с черточками> Рекурсивный поиск по правой ветви
    bool res2 = search(node->right, key);
    // Если в правой ветви элемент найден
    return res2;
}

// Печать дерева
void BST::pretty_print(const std::string& chain, const BST* node, bool isLeft)
{
    if (node != NULL)
    {
        // Печать префикса
        std::cout << chain;
        // Печать символа "связки"
        std::cout << (isLeft ? "├──" : "└──");

        // Печать значения
        std::cout << node->data << std::endl;

        // <В квадратике с черточками> Рекурсивный вызов для левой ветви
        pretty_print(chain + (isLeft ? "│   " : "    "), node->left, true);
        // <В квадратике с черточками> Рекурсивный вызов для правой ветви
        pretty_print(chain + (isLeft ? "│   " : "    "), node->right, false);
    }
}

// Нахождение высоты дерева
int BST::height(BST* node)
{
    // Если дерево неопределено
    if (!node) return -1;

    // <В квадратике с черточками> Рекурсивный вызов функции height для нахождения максимума между правой и левой ветвью
    return 1 + max(height(node->left), height(node->right));
}

// Нахождение кол-ва узлов дерева
int BST::node_count(BST* node)
{
    // Инициализация итератора = 1 (включает корень)
    int c = 1;
    // Если дерево пустое
    if (node == NULL)
        return 0;
    else
    {
        // <В квадратике с черточками> Рекурсивно посчитать все связки для правой и левой ветви
        // <В дефолтном квадратике> Записать в итератор
        c += node_count(node->left);
        c += node_count(node->right);
        return c;
    }
}

// Удаление элемента из дерева
BST* BST::remove(BST* root, int key)
{
    // Если дерево пустое
    if (root == NULL)
        return root;

    // Если ключ меньше элемента в текущей ноде
    if (key < root->data)
        // <В квадратике с черточками> Удаление элемента по левой ветви
        root->left = remove(root->left, key);

    // Если ключ больше элемента в текущей ноде
    else if (key > root->data)
        // <В квадратике с черточками> Удаление элемента по правой ветви
        root->right = remove(root->right, key);

    // В случае удаления
    else {
        // Если указатель по левой ветви пуст
        if (root->left == NULL) {
            // Переместить указатель на правую ветвь
            BST* temp = root->right;
            // Удалить элемент
            free(root);
            return temp;
        }
        // Если указатель по правой ветви пуст
        else if (root->right == NULL) {
            // Переместить указатель на левую ветвь
            BST* temp = root->left;
            // Удалить элемент
            free(root);
            return temp;
        }

        // Запомнить правую ветвь от корня
        BST* temp = root->right;

        // Пока правая ветвь и ее левая определена
        while (temp && temp->left != NULL)
            temp = temp->left;

        // Сдвиг элемента к актуальной ноде
        root->data = temp->data;

        // <В квадратике с черточками> Удаление запомненного элемента по правой ветви
        root->right = remove(root->right, temp->data);
    }

    return root;
}

int main()
{
    BST b, * root = NULL;
    int search_key = 4;

    root = b.insert(root, 8);
    b.insert(root, 5);
    b.insert(root, 2);
    b.insert(root, 6);
    b.insert(root, 10);
    b.insert(root, 9);
    b.insert(root, 11);

    cout << "Печать исходного дерева:" << endl;
    b.pretty_print("", root, false);

    cout << "\nВставка элемента " << search_key << ':' << endl;
    b.insert(root, search_key);
    b.pretty_print("", root, false);

    cout << "\nПоиск элемента " << search_key << ':' << endl;
    if (b.search(root, search_key))
        cout << "Элемент " << search_key << " найден в дереве." << endl;
    else
        cout << "Элемент " << search_key << " не найден в дереве." << endl;

    cout << "\nУдаление элемента " << search_key << endl;
    b.remove(root, 4);
    b.pretty_print("", root, false);

    cout << "\nВысота дерева: " << b.height(root) << endl;
    cout << "\nКоличество узлов дерева: " << b.node_count(root) << endl;

    cout << "\nОбход дерева (in_order): " << endl;
    b.in_order(root);

    return 0;
}

