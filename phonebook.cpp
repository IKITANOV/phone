#include "phonebook.h"
#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

// создания масива для контактов
void initPhoneBook(char*** phoneBook, int* capacity, int* size) {
    *capacity = 10; // место в масиве
    *size = 0;      // контактов в телефоной книге в старте кода
    *phoneBook = new char* [*capacity];
    for (int i = 0; i < *capacity; i++) {
        (*phoneBook)[i] = new char[3][100]; // вывод ифнормации
    }
}

// освобождение памяти
void freePhoneBook(char*** phoneBook, int size) {
    for (int i = 0; i < size; i++) {
        delete[] (*phoneBook)[i]; // освобождение под масива
    }
    delete[] *phoneBook; // освобождения масива
}

// добавления контакта
void addContact(char*** phoneBook, int* capacity, int* size) {
    if (*size >= *capacity) {
        // увелечения масива при проблемах с местом
        int newCapacity = *capacity * 2;
        char** temp = new char* [newCapacity];
        for (int i = 0; i < newCapacity; i++) {
            temp[i] = new char[3][100];
            if (i < *size) {
                for (int j = 0; j < 3; j++) {
                    strcpy(temp[i][j], (*phoneBook)[i][j]);
                }
            }
        }
        freePhoneBook(phoneBook, *size);
        *phoneBook = temp;
        *capacity = newCapacity;
    }

    string name, phone, email;
    cout << "Enter name: ";
    cin.ignore();
    getline(cin, name);
    cout << "Enter phone: ";
    getline(cin, phone);
    cout << "Enter email: ";
    getline(cin, email);

    // копирование в массив
    strncpy((*phoneBook)[*size][0], name.c_str(), 99);
    (*phoneBook)[*size][0][99] = '\0';
    strncpy((*phoneBook)[*size][1], phone.c_str(), 99);
    (*phoneBook)[*size][1][99] = '\0';
    strncpy((*phoneBook)[*size][2], email.c_str(), 99);
    (*phoneBook)[*size][2][99] = '\0';
    (*size)++;
    cout << "Contact added successfully!\n";
    saveToFile(*phoneBook, *size);
}

// удаления контакта
void deleteContact(char*** phoneBook, int* size) {
    string name;
    cout << "Enter name to delete: ";
    cin.ignore();
    getline(cin, name);

    for (int i = 0; i < *size; i++) {
        if (name == (*phoneBook)[i][0]) {
            // сдвиг контактов псоле делита
            for (int j = i; j < *size - 1; j++) {
                for (int k = 0; k < 3; k++) {
                    strcpy((*phoneBook)[j][k], (*phoneBook)[j + 1][k]);
                }
            }
            (*size)--;
            cout << "Contact deleted successfully!\n";
            saveToFile(*phoneBook, *size);
            return;
        }
    }
    cout << "Contact not found!\n";
}

// поисках немо(контактов)
void searchContact(char** phoneBook, int size) {
    string query;
    cout << "Enter name or phone to search: ";
    cin.ignore();
    getline(cin, query);
    bool found = false;

    for (int i = 0; i < size; i++) {
        if (string(phoneBook[i][0]).find(query) != string::npos ||
            string(phoneBook[i][1]).find(query) != string::npos) {
            cout << "Name: " << phoneBook[i][0] << "\nPhone: " << phoneBook[i][1]
                 << "\nEmail: " << phoneBook[i][2] << "\n\n";
            found = true;
        }
    }
    if (!found) cout << "No contacts found!\n";
}

// редактирование контакта
void editContact(char*** phoneBook, int size) {
    string name;
    cout << "Enter name of contact to edit: ";
    cin.ignore();
    getline(cin, name);

    for (int i = 0; i < size; i++) {
        if (name == (*phoneBook)[i][0]) {
            string phone, email;
            cout << "Enter new phone: ";
            getline(cin, phone);
            cout << "Enter new email: ";
            getline(cin, email);
            strncpy((*phoneBook)[i][1], phone.c_str(), 99);
            (*phoneBook)[i][1][99] = '\0';
            strncpy((*phoneBook)[i][2], email.c_str(), 99);
            (*phoneBook)[i][2][99] = '\0';
            cout << "Contact updated successfully!\n";
            saveToFile(*phoneBook, size);
            return;
        }
    }
    cout << "Contact not found!\n";
}
// вывод контактов
void displayAll(char** phoneBook, int size) {
    if (size == 0) {
        cout << "Phonebook is empty!\n";
        return;
    }
    cout << "All contacts:\n";
    for (int i = 0; i < size; i++) {
        cout << "Name: " << phoneBook[i][0] << "\nPhone: " << phoneBook[i][1]
             << "\nEmail: " << phoneBook[i][2] << "\n\n";
    }
}

// сейв в файл
void saveToFile(char** phoneBook, int size) {
    ofstream outFile("phonebook.txt");
    if (!outFile) {
        cout << "Error opening file for writing!\n";
        return;
    }
    for (int i = 0; i < size; i++) {
        outFile << phoneBook[i][0] << ";" << phoneBook[i][1] << ";" << phoneBook[i][2] << "\n";
    }
    outFile.close();
    cout << "Contacts saved to file.\n";
}

// из файла загрузка
void loadFromFile(char*** phoneBook, int* capacity, int* size) {
    ifstream inFile("phonebook.txt");
    if (!inFile) {
        cout << "No existing phonebook file found. Starting fresh.\n";
        return;
    }

    string line;
    *size = 0;
    *capacity = 10;
    *phoneBook = new char* [*capacity];
    for (int i = 0; i < *capacity; i++) {
        (*phoneBook)[i] = new char[3][100];
    }

    while (getline(inFile, line)) {
        if (*size >= *capacity) {
            int newCapacity = *capacity * 2;
            char** temp = new char* [newCapacity];
            for (int i = 0; i < newCapacity; i++) {
                temp[i] = new char[3][100];
                if (i < *size) {
                    for (int j = 0; j < 3; j++) {
                        strcpy(temp[i][j], (*phoneBook)[i][j]);
                    }
                }
            }
            freePhoneBook(phoneBook, *size);
            *phoneBook = temp;
            *capacity = newCapacity;
        }

        size_t pos1 = line.find(';');
        size_t pos2 = line.find(';', pos1 + 1);
        if (pos1 != string::npos && pos2 != string::npos) {
            strncpy((*phoneBook)[*size][0], line.substr(0, pos1).c_str(), 99);
            (*phoneBook)[*size][0][99] = '\0';
            strncpy((*phoneBook)[*size][1], line.substr(pos1 + 1, pos2 - pos1 - 1).c_str(), 99);
            (*phoneBook)[*size][1][99] = '\0';
            strncpy((*phoneBook)[*size][2], line.substr(pos2 + 1).c_str(), 99);
            (*phoneBook)[*size][2][99] = '\0';
            (*size)++;
        }
    }
    inFile.close();
    cout << "Contacts loaded from file.\n";
}

// менюшка
void displayMenu() {
    cout << "\nPhonebook Menu:\n";
    cout << "1. Add contact\n";
    cout << "2. Delete contact\n";
    cout << "3. Search contact\n";
    cout << "4. Edit contact\n";
    cout << "5. Display all contacts\n";
    cout << "6. Exit\n";
    cout << "Enter choice: ";
}
