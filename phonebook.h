#ifndef PHONEBOOK_H
#define PHONEBOOK_H

// Структура для хранения контакта
struct Contact {
    char name[100];   // Имя контакта
    char phone[100];  // Телефон контакта
    char email[100];  // Електронка контакта
};

// Прототипы функций
void initPhoneBook(char*** phoneBook, int* capacity, int* size); // Инициализация массива
void addContact(char*** phoneBook, int* capacity, int* size);    // Добавить контакт
void deleteContact(char*** phoneBook, int* size);               // Удалить контакт
void searchContact(char** phoneBook, int size);                 // Поиск контакта
void editContact(char*** phoneBook, int size);                  // Редактировать контакт
void displayAll(char** phoneBook, int size);                    // Вывести все контакты
void saveToFile(char** phoneBook, int size);                    // Сохранить в файл
void loadFromFile(char*** phoneBook, int* capacity, int* size); // Загрузить из файла
void freePhoneBook(char*** phoneBook, int size);                // Освободить память
void displayMenu();                                            // Показать меню

#endif
