#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow> // Стандaртный класс главного окна приложения
#include <QFileDialog> // Диалог сохранения и чтения файла. Позволяет выбрать файлу

// Классы диалоговых окон, которые вызываются при взаимодействии с главным окном
#include "book_dialog.h"
#include "add_book_dialog.h"
#include "change_book_dialog.h"

// Наш книжный шкаф
#include "bookshelf.h"


/// В этом файле содержатся объявления методов и слотов класса Главное Окно

namespace Ui { // Пространство имен создалось автоматически
class MainWindow;
}

// Наследуем наше главное окно от стандартного главного окна. 
class MainWindow : public QMainWindow
{
    Q_OBJECT // я не знаю что это 

public:
    explicit MainWindow(QWidget *parent = 0); // конструктор
    ~MainWindow(); // и деструктор

    
/*
 * Слоты -- это специальные функции,
 * в которых написано, что делать,
 * когда пришел соответствующий сигнал
 * сигналы посылают графические объекты -- кнопки и окна, когда что-то случилось
 * например, пользователь тыкает ОК в окне по имени А
 * и кнопка ОК посылает сигнал 'ок_нажат' своему окну
 * а у окна А есть слот 'ок_нажат', в котором написано 
 * пошли сигнал 'ок_нажат_в_окне_А' программе
 * а у программы есть слот 'в_окне_А_нажали_ок', делать "это вот"...
 * как-то так :)
 * QT местами эту связь осуществляет самостоятельно
 */
    
private slots:
    /// Три слота ниже очень похожи, потому что в каждом из них у нас появляется окошко ввода,
    /// в которое юзер вбивает данные и тыкает ОК
    
    // в окошке, которое считывает название и автора, нажали ОК
    void book_accepted(QString title, QString author); 
    
    // в окошке, которое считывает название, автора, пагесы и номер полки нажали ОК
    void book_accepted(QString title, QString author, int pages, int number);
    
    // в окошке, которое считывает название, автора и пагесы нажали ОК
    void book_accepted(QString title, QString author, int pages);
    
    
    /// Дальше идут слоты нажатия кнопок главного окна
    
    void on_btn_find_book_clicked(); // нажата кнопка найти книгу 

    void on_btn_change_book_clicked(); // нажата кнопка редактировать книгу

    void on_btn_move_book_clicked(); // нажата кнопка переместить книгу

    void on_btn_remove_book_clicked(); // нажата кнопка удалить книгу

    void on_btn_add_book_clicked(); // нажата кнопка добавить книгу

    void on_btn_all_books_clicked(); // нажата кнопка показать все книги

    void on_btn_count_books_clicked(); // нажата кнопка показать общее количество книг в шкафу

    void on_btn_count_shelf_clicked(); // нажата кнопка показать количество полок

    void on_btn_books_on_shelf_clicked(); // нажата кнопка вывести книги на полке N

    void on_btn_save_clicked(); // нажата кнопка сохранить

    void on_btn_open_clicked(); // нажата кнопка открыть файл


private:
    Ui::MainWindow *ui; // Это объявление указателя на графический интерфейс главного окна,
                       // в котором содержатся все вышеописанные кнопки
    
    std::string title;
    std::string author;
    int pages;
    int number;
    Bookshelf bookshelf;

};

#endif // MAINWINDOW_H
