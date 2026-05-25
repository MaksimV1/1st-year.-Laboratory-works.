#pragma once
#include <iostream>
#include <algorithm>
#include <iomanip>
using namespace std;

template<typename T>
class Tree {
private:
    struct Node {
        T data;
        Node* left;
        Node* right;
        int height;

        Node(const T& value) : data(value), left(nullptr), right(nullptr), height(1) {}
    };

    Node* root;

    // Получить высоту узла
    int getNodeHeight(Node* node) const {
        return node ? node->height : 0;
    }

    // Получить баланс узла
    int getBalance(Node* node) const {
        return node ? getNodeHeight(node->left) - getNodeHeight(node->right) : 0;
    }

    // Обновить высоту узла
    void updateHeight(Node* node) {
        if (node) {
            node->height = 1 + max(getNodeHeight(node->left), getNodeHeight(node->right));
        }
    }

    // Правый поворот
    Node* rotateRight(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;

        x->right = y;
        y->left = T2;

        updateHeight(y);
        updateHeight(x);

        return x;
    }

    // Левый поворот
    Node* rotateLeft(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;

        y->left = x;
        x->right = T2;

        updateHeight(x);
        updateHeight(y);

        return y;
    }

    // Вставка узла
    Node* insert(Node* node, const T& value) {
        // Обычная вставка BST
        if (!node) {
            return new Node(value);
        }

        if (value < node->data) {
            node->left = insert(node->left, value);
        }
        else if (value > node->data) {
            node->right = insert(node->right, value);
        }
        else {
            // Дубликаты не допускаются
            return node;
        }

        // Обновить высоту
        updateHeight(node);

        // Получить баланс
        int balance = getBalance(node);

        // Left Left Case
        if (balance > 1 && value < node->left->data) {
            return rotateRight(node);
        }

        // Right Right Case
        if (balance < -1 && value > node->right->data) {
            return rotateLeft(node);
        }

        // Left Right Case
        if (balance > 1 && value > node->left->data) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }

        // Right Left Case
        if (balance < -1 && value < node->right->data) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }

    // Найти узел с минимальным значением
    Node* findMin(Node* node) const {
        while (node && node->left) {
            node = node->left;
        }
        return node;
    }

    // Удаление узла
    Node* remove(Node* node, const T& value) {
        if (!node) {
            return node;
        }

        if (value < node->data) {
            node->left = remove(node->left, value);
        }
        else if (value > node->data) {
            node->right = remove(node->right, value);
        }
        else {
            if (!node->left || !node->right) {
                Node* temp = node->left ? node->left : node->right;

                if (!temp) {
                    temp = node;
                    node = nullptr;
                }
                else {
                    *node = *temp;
                }
                delete temp;
            }
            else {
                Node* temp = findMin(node->right);
                node->data = temp->data;
                node->right = remove(node->right, temp->data);
            }
        }

        if (!node) {
            return node;
        }

        updateHeight(node);

        int balance = getBalance(node);

        // Left Left Case
        if (balance > 1 && getBalance(node->left) >= 0) {
            return rotateRight(node);
        }

        // Left Right Case
        if (balance > 1 && getBalance(node->left) < 0) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }

        // Right Right Case
        if (balance < -1 && getBalance(node->right) <= 0) {
            return rotateLeft(node);
        }

        // Right Left Case
        if (balance < -1 && getBalance(node->right) > 0) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }

    // Поиск узла
    Node* search(Node* node, const T& value) const {
        if (!node || node->data == value) {
            return node;
        }

        if (value < node->data) {
            return search(node->left, value);
        }

        return search(node->right, value);
    }

    // Симметричный обход (in-order)
    void inOrder(Node* node) const {
        if (node) {
            inOrder(node->left);
            node->data.output();
            inOrder(node->right);
        }
    }

    // Прямой обход (pre-order)
    void preOrder(Node* node) const {
        if (node) {
            node->data.output();
            preOrder(node->left);
            preOrder(node->right);
        }
    }

    // Обратный обход (post-order)
    void postOrder(Node* node) const {
        if (node) {
            postOrder(node->left);
            postOrder(node->right);
            node->data.output();
        }
    }

    // Визуальное отображение дерева
    void printTree(Node* node, string indent, bool last) const {
        if (node) {
            cout << indent;
            if (last) {
                cout << "└── ";
                indent += "    ";
            }
            else {
                cout << "├── ";
                indent += "│   ";
            }

            cout << node->data.getTitle() << " (h:" << node->height << ")" << endl;

            if (node->left || node->right) {
                if (node->right) {
                    printTree(node->right, indent, !node->left);
                }
                if (node->left) {
                    printTree(node->left, indent, true);
                }
            }
        }
    }

    // Очистка дерева
    void clear(Node* node) {
        if (node) {
            clear(node->left);
            clear(node->right);
            delete node;
        }
    }

    // Копирование дерева
    Node* copyTree(Node* node) const {
        if (!node) {
            return nullptr;
        }

        Node* newNode = new Node(node->data);
        newNode->height = node->height;
        newNode->left = copyTree(node->left);
        newNode->right = copyTree(node->right);

        return newNode;
    }

    // Подсчет количества узлов
    int countNodes(Node* node) const {
        if (!node) {
            return 0;
        }
        return 1 + countNodes(node->left) + countNodes(node->right);
    }

public:
    Tree() : root(nullptr) {}

    Tree(const Tree& other) : root(copyTree(other.root)) {}

    Tree& operator=(const Tree& other) {
        if (this != &other) {
            clear(root);
            root = copyTree(other.root);
        }
        return *this;
    }

    ~Tree() {
        clear(root);
    }

    void insert(const T& value) {
        root = insert(root, value);
    }

    void remove(const T& value) {
        root = remove(root, value);
    }

    bool search(const T& value) const {
        return search(root, value) != nullptr;
    }

    bool isEmpty() const {
        return root == nullptr;
    }

    int getTreeHeight() const {
        return getNodeHeight(root);
    }

    int size() const {
        return countNodes(root);
    }

    // Различные способы обхода дерева
    void displayInOrder() const {
        cout << "In-order traversal:" << endl;
        inOrder(root);
        cout << endl;
    }

    void displayPreOrder() const {
        cout << "Pre-order traversal:" << endl;
        preOrder(root);
        cout << endl;
    }

    void displayPostOrder() const {
        cout << "Post-order traversal:" << endl;
        postOrder(root);
        cout << endl;
    }

    // Визуальное отображение структуры дерева
    void displayTree() const {
        if (isEmpty()) {
            cout << "Tree is empty" << endl;
            return;
        }

        cout << "Tree structure:" << endl;
        printTree(root, "", true);
        cout << endl;
    }

    // Статистика дерева
    void displayStats() const {
        cout << "Tree height: " << getTreeHeight() << endl;
        cout << "Number of nodes: " << size() << endl;
        cout << "Tree is " << (isEmpty() ? "empty" : "not empty") << endl;
    }
};