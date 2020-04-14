#include "book_dialog.h"
#include "ui_book_dialog.h"

Book_Dialog::Book_Dialog(QWidget *parent) : // конструктор, такой же, как у MainWindowa
    QDialog(parent),
    ui(new Ui::Book_Dialog)
{
    ui->setupUi(this);
}

Book_Dialog::~Book_Dialog() // деструктор
{
    delete ui;
}

void Book_Dialog::on_buttonBox_accepted()   // книгу вписали ок нажали
{
    // эта длиннющая функция соединяет наше окошко с главным окном
    // Соедени(отправитель т е Book_dialog, сообщение(нажали ок вписали две строки),
    //         получатель сигнала родитель т е MainWindow, и наконец слот MainWindowa где написано че делать);
    connect(this, SIGNAL(on_accepted_book(QString, QString)),
            this->parent(),SLOT(book_accepted(QString, QString)));

    // а эта функция отправляет наш сигнал по настроенному выше "каналу связи"
    emit on_accepted_book(ui->le_title->text(), ui->le_author->text());
}
