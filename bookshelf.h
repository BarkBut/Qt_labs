#ifndef LAB1_BOOKSHELF_H
#define LAB1_BOOKSHELF_H

#include "shelf.h"
#include <sstream>
#include <fstream>
#include <vector>

/// Здесь многое поменялось, добавилась работа с файлами
// todo сделать рабочей закладку

// Это заголовочный файл класса Книжныйшкаф. Тут будут комментарии только о новых штуках,
// подробнее см. классы Полка и Книга
// Большая часть методов здесь является обобщением методов класса Полка

class Bookshelf {
    std::vector<Shelf> shelves; // это поле -- vector 10 элементов типа Полка

public:
    explicit Bookshelf(unsigned int size);

    bool findBook(std::string title, std::string author); // проверяет, есть ли книга в шкафу
    unsigned int findShelf(std::string title, std::string author);// возвращает номер полки, на которой лежит книга

    /// Больше не выводит, а возвращает строку
    std::string writeAddress(std::string title, std::string author);

    void addBook(unsigned int shelf_number, PrintBook abook);

    void putBook(PrintBook afterbook, PrintBook putbook);

    /// Эти тоже теперь не выводят
    std::string writeAll();   //  выводит на экран ВСЁ. Весь шкаф...
    std::string writeNumber(); // выводит количество книг в шкафу
    std::string writeShelf(unsigned int number); // выводит на экран содержимое полки
    
    void removeBook(std::string title, std::string author); // можно удалить книгу по названию и автору
    void removeBook(unsigned int shelf_number, unsigned int place); // а можно по её адресу

    PrintBook &getBook(std::string title, std::string author);

    PrintBook &getBook(unsigned int place, unsigned int shelf_number);

    std::string getSize();  // возвращает количество полок в шкафу
    
    /// не используется
    //void writeSize();       // выводит его на экран
    
    /// Это работа с файлом
    void save(std::string filename);    // сохранение
    void load(std::string filename);    // чтение
    std::string split_by_comma(std::stringstream & line); // разделение строчки на название и автора по запятым

    ~Bookshelf(); // деструктор
};

#endif
