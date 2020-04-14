#ifndef BOOK_DIALOG_H
#define BOOK_DIALOG_H

#include <QDialog>

/// В этом файле содержится объявление класса Воок диалог 
/// это самое простое окно для ввода данных о книге
/// оно содержит поля для ввода названия и автора и кнопки OK и CANCEL

namespace Ui {
class Book_Dialog;
}

class Book_Dialog : public QDialog  // наследуем наше окно от образцового окна Qt
{
    Q_OBJECT        // это появилось автоматически, я не знаю, кто это

public:
    explicit Book_Dialog(QWidget *parent = 0); // как всегда, конструктор принимает указатель на "родителя"
                                              // который его вызвал

    ~Book_Dialog();

private slots:
    void on_buttonBox_accepted(); // вписали книжку нажали ок

signals: // этот сигнал с введенными данными от нашего окна отправляется родителю-вызывателю -- MainWindowy
    void on_accepted_book(QString title, QString author); // и вручает ему титл и осора

private:
    Ui::Book_Dialog *ui;   // очередная Qt-автомагия
};

#endif // BOOK_DIALOG_H
