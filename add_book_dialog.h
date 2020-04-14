#ifndef ADD_BOOK_DIALOG_H
#define ADD_BOOK_DIALOG_H

#include <QDialog>

/// В этом файле находится объявление класса нового Окна,
/// необходимого для добавления новой книги
/// у этого окна помимо названия и автора есть поля для ввода количества страниц
/// и номера полки, на которую следует добавить новую книгу
/// Здесь всё очень похоже на другие файлы окошек

namespace Ui {
class Add_book_dialog;
}

class Add_book_dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Add_book_dialog(QWidget *parent = 0);

    ~Add_book_dialog();

signals:
    void on_accepted_book(QString title, QString author, int pages, int number);

private slots:
    void on_buttonBox_accepted();

private:
    Ui::Add_book_dialog *ui;
};

#endif // ADD_BOOK_DIALOG_H
