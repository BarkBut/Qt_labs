#include "add_book_dialog.h"
#include "ui_add_book_dialog.h"

/// В этом файле содержится определение класса Окно_добавления_книги
/// тоже всё похоже на другие окна

Add_book_dialog::Add_book_dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Add_book_dialog)
{
    ui->setupUi(this);
}

Add_book_dialog::~Add_book_dialog()
{
    delete ui;
}

void Add_book_dialog::on_buttonBox_accepted()
{
    // распишу еще раз эту колбасу
    // Соедени(Это окно ака отправитель ака Add_book_dialog, Cooбщение,
    //         родитель-вызыватель, слот с инструкцией)
    connect(this, SIGNAL(on_accepted_book(QString,QString,int,int)),
            this->parent(),SLOT(book_accepted(QString, QString, int, int)));

    emit on_accepted_book(ui->le_title->text(),
                          ui->le_author->text(),
                          ui->sb_pages->value(),
                          ui->sb_shelf->value());
}
