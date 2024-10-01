#include <iostream>
#include <queue>
#include <stack>

using namespace std;

// Структура для представления узла двоичного дерева
struct Node {
    int data;          // Данные, хранящиеся в узле
    Node* left;       // Указатель на левое поддерево
    Node* right;      // Указатель на правое поддерево

    // Конструктор узла
    Node(int value) : data(value), left(nullptr), right(nullptr) {}
};

class BT {
private:
    Node* root; // Корень двоичного дерева

public:
    // Конструктор
    BT() : root(nullptr) {}

    // Деструктор
    ~BT() {
        clear(root); // Освобождение памяти при удалении дерева
    }

    // Рекурсивный метод для очистки дерева
    void clear(Node* node) {
        if (node) {
            clear(node->left);  // Очистка левого поддерева
            clear(node->right); // Очистка правого поддерева
            delete node;        // Удаление текущего узла
        }
    }

    // Метод для вставки значения
    void insert(int val) {
        root = insert(root, val); // Вставка значения в дерево
    }

    // Внутренний метод для рекурсивной вставки
    Node* insert(Node* node, int val) {
        if (node == nullptr) {
            return new Node(val); // Создание нового узла, если место найдено
        }

        // Рекурсивный поиск места для вставки
        if (val < node->data) {
            node->left = insert(node->left, val);
        } else if (val > node->data) {
            node->right = insert(node->right, val);
        } else {
            cout << "Такое значение в дереве уже существует" << endl; // Если значение уже есть
        }

        return node; // Возврат текущего узла
    }

    // Метод для поиска значения
    Node* search(int val) {
        return search(root, val); // Поиск значения в дереве
    }

    // Внутренний метод для рекурсивного поиска
    Node* search(Node* node, int val) {
        if (node == nullptr) {
            return nullptr; // Если узел не найден
        }

        // Сравнение значения с данными узла
        if (node->data == val) {
            return node; // Если узел найден
        } else if (val < node->data) {
            return search(node->left, val); // Поиск в левом поддереве
        } else {
            return search(node->right, val); // Поиск в правом поддереве
        }
    }

    // Метод для удаления узла
    void removeNode(int val) {
        root = removeNode(root, val); // Удаление узла из дерева
    }

    // Внутренний метод для рекурсивного удаления
    Node* removeNode(Node* node, int val) {
        if (node == nullptr) {
            return nullptr; // Если узел не найден
        }

        // Рекурсивный поиск узла для удаления
        if (val < node->data) {
            node->left = removeNode(node->left, val);
        } else if (val > node->data) {
            node->right = removeNode(node->right, val);
        } else {
            // Найден узел для удаления
            if (node->left == nullptr) {
                Node* temp = node->right; // Сохранение правого поддерева
                delete node;               // Удаление узла
                return temp;               // Возврат правого поддерева
            } else if (node->right == nullptr) {
                Node* temp = node->left;  // Сохранение левого поддерева
                delete node;               // Удаление узла
                return temp;               // Возврат левого поддерева
            }

            // Узел с двумя потомками
            Node* minNode = node->right; // Поиск минимального узла в правом поддереве
            while (minNode->left != nullptr) {
                minNode = minNode->left; // Находим самый левый узел
            }

            node->data = minNode->data; // Замена данных узла
            node->right = removeNode(node->right, minNode->data); // Удаление минимального узла
        }

        return node; // Возврат текущего узла
    }

    // Метод обхода в ширину
    void bfs() {
        bfs(root); // Запуск обхода в ширину
    }

    // Внутренний метод обхода в ширину
    void bfs(Node* node) {
        if (node == nullptr) {
            return; // Если дерево пустое
        }

        queue<Node*> q; // Создание очереди для обхода
        q.push(node);   // Добавление корня в очередь

        while (!q.empty()) {
            Node* current = q.front(); // Получение текущего узла
            q.pop();                   // Удаление узла из очереди
            cout << current->data << " "; // Вывод данных узла

            // Добавление дочерних узлов в очередь
            if (current->left != nullptr) {
                q.push(current->left);
            }
            if (current->right != nullptr) {
                q.push(current->right);
            }
        }
    }

    // Метод обхода в глубину
    void dfs() {
        dfs(root); // Запуск обхода в глубину
    }

    // Внутренний метод обхода в глубину
    void dfs(Node* node) {
        if (node == nullptr) {
            return; // Если дерево пустое
        }

        stack<Node*> st; // Создание стека для обхода
        st.push(node);   // Добавление корня в стек

        while (!st.empty()) {
            Node* curr = st.top(); // Получение текущего узла
            st.pop();              // Удаление узла из стека
            cout << curr->data << endl; // Вывод данных узла

            // Добавление дочерних узлов в стек
            if (curr->right != nullptr) {
                st.push(curr->right);
            }
            if (curr->left != nullptr) {
                st.push(curr->left);
            }
        }
    }
};

// Пример использования класса BT
int main() {
    BT tree; // Создание экземпляра двоичного дерева

    // Вставка значений в дерево
    tree.insert(5);
    tree.insert(3);
    tree.insert(7);
    tree.insert(2);
    tree.insert(4);
    tree.insert(6);
    tree.insert(8);

    // Обход в ширину
    cout << "Обход в ширину (BFS): ";
    tree.bfs();
    cout << endl;

    // Обход в глубину
    cout << "Обход в глубину (DFS): ";
    tree.dfs();
    cout << endl;

    // Пример удаления узла
    tree.removeNode(3);
    cout << "После удаления узла со значением 3 (BFS): ";
    tree.bfs(); // Повторный обход после удаления
    cout << endl;

    return 0; // Завершение программы
}
