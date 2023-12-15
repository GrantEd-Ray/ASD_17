#include <iostream>
#include <string>
#include <windows.h>
using namespace std;

struct Node {
    int value;
    Node* left;
    Node* right;

    Node(int val) : value(val), left(nullptr), right(nullptr) {}
};

Node* constructTree(string s, int& index) {
    if (s.empty() || s[index] == ')') {
        index++;
        return nullptr;
    }

    int num = 0;
    while (index < s.length() && s[index] != '(' && s[index] != ')') {
        num = num * 10 + (s[index] - '0');
        index++;
    }

    Node* node = new Node(num);

    if (index < s.length() && s[index] == '(') {
        index++;
        node->left = constructTree(s, index);

        if (index < s.length() && s[index] == ',') {
            index++;
            node->right = constructTree(s, index);
        }
    }
    index++;
    return node;
}

Node* insert(Node* root, int value) {
    if (!root) {
        return new Node(value);
    }

    if (value < root->value) {
        root->left = insert(root->left, value);
    } else if (value > root->value) {
        root->right = insert(root->right, value);
    }

    return root;
}

Node* findMinValueNode(Node* node) {
    Node* current = node;

    while (current && current->left != nullptr) {
        current = current->left;
    }

    return current;
}

Node* deleteNode(Node* root, int value) {
    if (!root) {
        return root;
    }

    if (value < root->value) {
        root->left = deleteNode(root->left, value);
    } else if (value > root->value) {
        root->right = deleteNode(root->right, value);
    } else {
        if (root->left == nullptr) {
            Node* temp = root->right;
            delete root;
            return temp;
        } else if (root->right == nullptr) {
            Node* temp = root->left;
            delete root;
            return temp;
        }

        Node* temp = findMinValueNode(root->right);
        root->value = temp->value;
        root->right = deleteNode(root->right, temp->value);
    }

    return root;
}

bool search(Node* root, int value) {
    if (!root) {
        return false;
    }

    if (root->value == value) {
        return true;
    } else if (value < root->value) {
        return search(root->left, value);
    } else {
        return search(root->right, value);
    }
}

void printInorder(Node* root) {
    if (root) {
        printInorder(root->left);
        cout << root->value << " ";
        printInorder(root->right);
    }
}

int main() {
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);

    string inputString = "8(3(1,6(4,7)),10(,14(13,)))";
    int index = 0;
    Node* root = constructTree(inputString, index);

    char choice;
    int value;

    do {
        cout << "Меню:\n";
        cout << "1. Добавить узел\n";
        cout << "2. Удалить узел\n";
        cout << "3. Поиск узла\n";
        cout << "4. Вывести БДП\n";
        cout << "5. Выйти из программы\n";
        cout << "Выберите операцию (1-5): ";
        cin >> choice;

        switch (choice) {
            case '1':
                cout << "Введите значение для добавления: ";
                cin >> value;
                root = insert(root, value);
                break;
            case '2':
                cout << "Введите значение для удаления: ";
                cin >> value;
                root = deleteNode(root, value);
                break;
            case '3':
                cout << "Введите значение для поиска: ";
                cin >> value;
                if (search(root, value)) {
                    cout << "Узел найден\n";
                } else {
                    cout << "Узел не найден\n";
                }
                break;
            case '4':
                cout << "БДП в виде линейно-скобочной записи: ";
                printInorder(root);
                cout << endl;
                break;
            case '5':
                cout << "Программа завершена\n";
                break;
            default:
                cout << "Неверный ввод. Пожалуйста, выберите операцию от 1 до 5\n";
                break;
        }
    } while (choice != '5');

    return 0;
}