#include "mainwindow.h"
#include "ui_mainwindow.h"

/// В этом файле содержится определение методов и слотов Главного Окна

/*
 * Дальше идёт конструктор, создающий наше главное окно
 * он принимает указатель на тот объект, который его вызвал
 * в Qt иерархия вызовов называется родителями
 * тот, кто вызвал окно_А -- родитель (parent) окна А
 *
 * Ещё наше главное окно наследуется от QMainWindow
 * это фича QT -- все графические объекты здесь наследуются от других графических объектов,
 * являющихся образцами из библиотеки Qt
 *
 * Наследование от Q-объектов и связь вызвавшего родителя с "ребенком" -- разные и не связанные вещи!
 * что совсем не интуитивно и я уже попадалась на этом :(
 */

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    bookshelf(Bookshelf(10))
{
    ui->setupUi(this);
}


MainWindow::~MainWindow() // деструктор -- удаляет весь графический интерфейс
{
    delete ui;
}


/// Определение слотов, принимающих информацию о книге

void MainWindow::book_accepted(QString title, QString author){ 
    this->title = title.toStdString();      // конвертируем кутешные строки в человеческие 
    this->author = author.toStdString();   // ведь наш старый код работает с обычными строками
}

void MainWindow::book_accepted(QString title, QString author, int pages, int number){
    this->title = title.toStdString();
    this->author = author.toStdString();
    this->pages = pages;
    this->number = number;
}

void MainWindow::book_accepted(QString title, QString author, int pages){
    this->title = title.toStdString();
    this->author = author.toStdString();
    this->pages = pages;
}


/// Определение слотов, отвечающих за нажатые кнопки

void MainWindow::on_btn_find_book_clicked() // найти книгу
{
   Book_Dialog book_dlg(this);  // открываем самое простое окошко ввода книги -- "введите название и автора" 
   book_dlg.setModal(true);    // делаем его главным -- пока юзер не закроет его, 
                              // все остальные окна принимать ничего не будут
   
   if(book_dlg.exec() == QDialog::Accepted){    // если в окне нажали ок
       try {                                   // старая добрая обработка исключений, которые никто не отменял
           // а дальше мы спокойно пишем title и author
          // потому что окно, считавшее их, нам их вручило
       PrintBook pb = bookshelf.getBook(title, author); // и вытаскиваем нужную книгу из шкафа
       ui->te_output->setText(pb.writeBook().c_str());  // а теперь выводим её на экран, типа нашли
       // при этом конвертируем её из си++ строк в си строки, чтобы setText работал правильно
       // и для красоты выведем ещё и адрес
       ui->te_output->append(bookshelf.writeAddress(title, author).c_str()); // апед дописывает на экран адрес
       } catch (std::domain_error e){
           ui->te_output->clear();
           ui->te_output->setText(e.what()); // если что-то пошло не так, выводим сообщение о том, что именно
       }
   }
}


void MainWindow::on_btn_change_book_clicked() // редактировать книгу 
{
    Book_Dialog book_dlg(this); // снова вызываем самое простое окошко ввода книги -- титл и осор
    book_dlg.setModal(true);   // делаем его главным
    if(book_dlg.exec() == QDialog::Accepted){   // если нажали ок, т е ввели данные о книге
        try {
            PrintBook & chbook = bookshelf.getBook(title, author);  // вынимаем нужную книгу из шкафа
            // при этом мы получаем ее по ссылке, т е получаем не копию объекта, а сам объект, и меняем его
            
            // а тут опа и вызывается еще одно окно
            // точнее это конструктор конечно
            // и окно теперь посложнее, ведь можно менять не только название и автора, но и колво страниц
            // у этого окошка свое имя и отдельные файлы с подробным описанием
            // а ещё оно создается сразу заполненное информацией о книге, которую юзер хочет поменять
            // для наглядности
            Change_book_dialog chg_dlg(QString(chbook.getTitle().c_str()), 
                                       QString(chbook.getAuthor().c_str()),
                                       chbook.getPages(),
                                       this);// а еще с указателем на родительское окно, те на наше MainWindow,
                                            // из которого мы вызвали наш chg_dlg
                                           // как и прочие окна собсна
            chg_dlg.setModal(true); // делаем свежее окошко главным
            if(chg_dlg.exec() == QDialog::Accepted){  // опять нажатие ока
                chbook.setTitle(title); // записываем
                chbook.setAuthor(author); // обновленные
                chbook.setPages(pages);  // данные о книге
                ui->te_output->setText(chbook.writeBook().c_str());
            } // показываем обновленную книгу :)

        } catch (std::domain_error e){
            ui->te_output->clear();
            ui->te_output->setText(e.what()); 
        }

    }
}


void MainWindow::on_btn_move_book_clicked() // переместить книгу
{
    Book_Dialog mobook_dlg(this); // классическое окно название+автор, но название у него означает
    mobook_dlg.setModal(true);   // move book, т е перемещаемая книга
    try {
        if(mobook_dlg.exec() == QDialog::Accepted){
            PrintBook mobook = bookshelf.getBook(title, author); 
            Book_Dialog afbook_dlg(this); // теперь нам нужно еще одно окно, считать книгу,
            afbook_dlg.setModal(true); //  после которой надо положить move book
            if(afbook_dlg.exec() == QDialog::Accepted){
                PrintBook & afbook = bookshelf.getBook(title, author);
                // удаляем книгу со старого места
                bookshelf.removeBook(mobook.getTitle(), mobook.getAuthor());
                bookshelf.putBook(afbook, mobook); // добавляем на новое
            }
        }
    } catch (std::domain_error e){
        ui->te_output->clear();
        ui->te_output->setText(e.what());
    }
}


void MainWindow::on_btn_remove_book_clicked() // удалить книгу
{                                            // этот слот похож на предыдущие, но простой
    Book_Dialog book_dlg(this);
    book_dlg.setModal(true);
    try {
        if(book_dlg.exec() == QDialog::Accepted){
            bookshelf.removeBook(title, author);
        }
    } catch (std::domain_error e){
        ui->te_output->clear();
        ui->te_output->setText(e.what());
    }
}


void MainWindow::on_btn_add_book_clicked() // добавить книгу
{
    Add_book_dialog add_book_dlg(this);
    add_book_dlg.setModal(true);
    if(add_book_dlg.exec() == QDialog::Accepted){
        this->bookshelf.addBook(this->number,
                                PrintBook(this->title,
                                          this->author,
                                          this->pages));
    }
}


void MainWindow::on_btn_all_books_clicked() // показать все книги
{
    ui->te_output->clear();
    ui->te_output->setText(QString(bookshelf.writeAll().c_str()));
}


void MainWindow::on_btn_count_books_clicked() // количество книг в шкафу
{
    ui->te_output->clear();
    ui->te_output->setText(QString(bookshelf.writeNumber().c_str()));
}


void MainWindow::on_btn_count_shelf_clicked() // размер шкафа
{
    ui->te_output->clear();
    ui->te_output->setText(QString(bookshelf.getSize().c_str()));
}


void MainWindow::on_btn_books_on_shelf_clicked() // показать содержимое полки
{
    unsigned int number = ui->sb_shelf_number->value();
    ui->te_output->clear();
    ui->te_output->setText(QString(bookshelf.writeShelf(number).c_str()));

}


///////////////////////////////////////// Работа с файлами ////////////////////////////////////////////////

/*
 * Ниже используется диалоговое окно, которое я не писала
 * оно подключено из специальной либы QFileDialog и само знает, как ему работать
 * это окно умеет соединять файловую систему компьютера, юзерский интерфейс и этот код
 * в отличие от меня :)
 */

void MainWindow::on_btn_save_clicked() // сохранить в файл
{
    QString file_name = QFileDialog::getSaveFileName(this,"Сохранить в файл");
    bookshelf.save(file_name.toStdString());
}

void MainWindow::on_btn_open_clicked() // открыть файл
{
    QString file_name = QFileDialog::getOpenFileName(this, "Загрузить из файла"); //
    bookshelf.load(file_name.toStdString());
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////
