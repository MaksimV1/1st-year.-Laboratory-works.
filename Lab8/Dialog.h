#pragma once
#include "Magazin.h"
#include "Tree.h"
#include <vector>

class Dialog : public Tree<Magazin> {
private:
    vector<Magazin> magazines; // Для хранения журналов в порядке добавления

    void addItem() {
        Magazin mag;
        cout << "Enter magazine information:" << endl;
        mag.input();

        // Добавляем в дерево
        this->insert(mag);
        // Добавляем в вектор для индексации
        magazines.push_back(mag);

        cout << "Magazine added successfully." << endl;
    }

    void removeItem() {
        if (magazines.empty()) {
            cout << "No magazines to remove." << endl;
            return;
        }

        cout << "Available magazines:" << endl;
        for (size_t i = 0; i < magazines.size(); ++i) {
            cout << i + 1 << ". " << magazines[i].getTitle() << endl;
        }

        cout << "Enter magazine number to remove (1-" << magazines.size() << "): ";
        int index;
        cin >> index;
        cin.ignore();

        if (index < 1 || index > static_cast<int>(magazines.size())) {
            cout << "Invalid magazine number." << endl;
            return;
        }

        Magazin magToRemove = magazines[index - 1];

        // Удаляем из дерева
        this->remove(magToRemove);
        // Удаляем из вектора
        magazines.erase(magazines.begin() + index - 1);

        cout << "Magazine '" << magToRemove.getTitle() << "' removed successfully." << endl;
    }

    void showAll() {
        if (this->isEmpty()) {
            cout << "No magazines in the collection." << endl;
            return;
        }

        cout << "\n=== All Magazines (sorted by title) ===" << endl;
        this->displayInOrder();

        cout << "\n=== Tree Structure ===" << endl;
        this->displayTree();

        this->displayStats();
    }

    void showTitles() {
        if (magazines.empty()) {
            cout << "No magazines in the collection." << endl;
            return;
        }

        cout << "\n=== Magazine Titles ===" << endl;
        for (size_t i = 0; i < magazines.size(); ++i) {
            cout << i + 1 << ". " << magazines[i].getTitle() << endl;
        }
        cout << "Total: " << magazines.size() << " magazines" << endl;
    }

    void clearCollection() {
        magazines.clear();
    }

public:
    Dialog() : Tree<Magazin>() {}

    void printMenu() {
        cout << "\n=== Magazine Collection Management ===" << endl;
        cout << "Available commands:" << endl;
        cout << "m <n> - Create collection with <n> magazines" << endl;
        cout << "+     - Add one magazine to the collection" << endl;
        cout << "-     - Remove one magazine from the collection" << endl;
        cout << "s     - Show all magazines information" << endl;
        cout << "z     - Show all magazine titles" << endl;
        cout << "c     - Clear the collection" << endl;
        cout << "h     - Show this menu" << endl;
        cout << "q     - Quit the program" << endl;
        cout << "=======================================" << endl;
    }

    void handleCommands() {
        cout << "Welcome to the Magazine Collection Management System" << endl;
        printMenu();

        char cmd;
        do {
            cout << "\nEnter command: ";
            cin >> cmd;

            switch (cmd) {
            case 'm': {
                int count;
                cin >> count;
                cin.ignore();

                if (count <= 0) {
                    cout << "Number must be positive." << endl;
                    break;
                }

                cout << "Creating collection with " << count << " magazines..." << endl;
                clearCollection(); // Очищаем существующую коллекцию

                for (int i = 0; i < count; ++i) {
                    cout << "\n--- Magazine " << i + 1 << " of " << count << " ---" << endl;
                    addItem();
                }

                cout << "\nCollection created successfully with " << count << " magazines." << endl;
                break;
            }

            case '+':
                cin.ignore();
                addItem();
                break;

            case '-':
                cin.ignore();
                removeItem();
                break;

            case 's':
                cin.ignore();
                showAll();
                break;

            case 'z':
                cin.ignore();
                showTitles();
                break;

            case 'c':
                cin.ignore();
                clearCollection();
                cout << "Collection cleared." << endl;
                break;

            case 'h':
                cin.ignore();
                printMenu();
                break;

            case 'q':
                cin.ignore();
                cout << "Exiting program. Thank you for using Magazine Collection Management!" << endl;
                break;

            default:
                cin.ignore();
                cout << "Unknown command '" << cmd << "'. Type 'h' for help." << endl;
            }

        } while (cmd != 'q');
    }

    // Дополнительные методы для демонстрации возможностей дерева
    void searchMagazine() {
        if (magazines.empty()) {
            cout << "No magazines in the collection." << endl;
            return;
        }

        cout << "Enter magazine title to search: ";
        string title;
        getline(cin, title);

        Magazin searchMag(title, "", 0, "");
        bool found = this->search(searchMag);

        cout << "Magazine '" << title << "' " << (found ? "found" : "not found")
            << " in the collection." << endl;
    }

    void showTreeTraversals() {
        if (this->isEmpty()) {
            cout << "No magazines in the collection." << endl;
            return;
        }

        cout << "\n=== Different Tree Traversals ===" << endl;

        cout << "\n1. In-order (sorted by title):" << endl;
        this->displayInOrder();

        cout << "\n2. Pre-order:" << endl;
        this->displayPreOrder();

        cout << "\n3. Post-order:" << endl;
        this->displayPostOrder();
    }
};

