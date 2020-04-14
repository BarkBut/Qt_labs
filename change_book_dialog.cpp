#include "change_book_dialog.h"
#include "ui_change_book_dialog.h"

/// В этом файле содержится определение класса Окно_добавления_книги
/// тоже всё похоже на другие окна

Change_book_dialog::Change_book_dialog(QString title,
                                       QString author,
                                       int pages,
                                       QWidget *parent) :
    QDialog(parent),
    ui(new Ui::change_book_dialog)
{
    ui->setupUi(this);
    ui->le_author->setText(author);
    ui->le_title->setText(title);
    ui->spinBox->setValue(pages);
}

Change_book_dialog::~Change_book_dialog()
{
    delete ui;
}

void Change_book_dialog::on_buttonBox_accepted()
{
    connect(this, SIGNAL(on_accepted_book(QString, QString, int)),
            parent(), SLOT(book_accepted(QString, QString, int)));

    emit on_accepted_book(ui->le_title->text(),
                          ui->le_author->text(),
                          ui->spinBox->value());
}
