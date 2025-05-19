#include "phonebook.h"
#include <iostream>

using namespace std;

int main() {
    char** phoneBook; //создания массива для контактиков
    int capacity;     // емкость массива
    int size;         // кл контактов

    // создание и загрузка 
    initPhoneBook(&phoneBook, &capacity, &size);
    loadFromFile(&phoneBook, &capacity, &size);

    int choice;
    do {
        displayMenu(); // показ меню
        cin >> choice;
        switch (choice) {
        case 1:
            addContact(&phoneBook, &capacity, &size); // добавления контакта
            break;
        case 2:
            deleteContact(&phoneBook, &size); // удаления контакта
            break;
        case 3:
            searchContact(phoneBook, size); // поиск контакта
            break;
        case 4:
            editContact(&phoneBook, size); // редакция контака
            break;
        case 5:
            displayAll(phoneBook, size); // показ контактов
            break;
        case 6:
            cout << "Exiting...\n"; // выход
            break;
        default:
            cout << "Invalid choice! Try again.\n";
        }
    } while (choice != 6);

    // освобождение книжки
    freePhoneBook(&phoneBook, size);
    return 0;
}
