#ifndef CHANGE_BOOK_DIALOG_H
#define CHANGE_BOOK_DIALOG_H

#include <QDialog>


/// В этом файле находится объявление класса нового Окна,
/// необходимого для редактирования книги
/// у этого окна помимо названия и автора есть поля для ввода количества страниц
/// Здесь всё очень похоже на другие файлы окошек

namespace Ui {
class change_book_dialog;
}

class Change_book_dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Change_book_dialog(QString title,  // передаем в конструктор старые значения этих полей
                                QString author, // чтобы юзер видел, что он собирается поменять
                                int pages,
                                QWidget *parent = 0);
    ~Change_book_dialog();

signals:
    void on_accepted_book(QString title, QString author, int pages);

private slots:
    void on_buttonBox_accepted();

private:
    Ui::change_book_dialog *ui;
};

#endif // CHANGE_BOOK_DIALOG_H
