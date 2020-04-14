#include "bookshelf.h"

/// Многое поменялось, в основном так же, как и в других файлах, вывод в консоль заменён на передачу строки
/// Ведь теперь выводом занимается графический интерфейс
/// Ещё добавлена работа с файлами

/* Этот файл посвящен капусте.
 * многие методы здесь -- просто обобщение методов класса полка
 * с более высоким уровнем абстракции
 * т е методы шкафа просто находят нужную полку и говорят ей делать свои аналогичные методы самой
 */

/////////////////// Новые технологии ухты, у нас появилось работа с файлами!/////////////////////////////////
/* Ниже будут использоваться потоки stringstream, ifstream и ofstream
 * поток это такой способ умного чтения
 * ifstream читает наш файл по строчкам до переноса строки
 * а stringstream разбивает строчку на слова по пробелам 
 * ofstream отвечает за запись в файл
 * на самом деле, cin и cout это тоже потоки, которые умеют правильно читать введенное в консоль
 */

/// Это новый метод. Он умеет правильно читать строчку, содержащую данные о книге, разделённые запятыми
std::string Bookshelf::split_by_comma(std::stringstream & line){ // принимает поток -- строку
    std::string word;
    std::string result = "";
    while (line >> word){   // пока не кончились слова (символы, разделенные пробелами) в потоке
        result += word;    // записываем все слова в название/автора, они ведь могут быть из нескольких слов
        if (word.back() == ','){    // запятая означает, что название/автор кончились
            result.pop_back();     // отрезаем запятую
            return result;        // и возвращаем строчку из слова/нескольких слов 
        }
        result += " ";      // поток читает без пробелов, поэтому между словами пробел надо дописать
    }
    return result;  
}


void Bookshelf::save(std::string filename){ // Этот метод сохраняет всё в файл
    std::string text = writeAll();         // writeAll больше не выводит, а возвращает строку со всеми книгами
    std::ofstream saver(filename);        // создаем поток записи
    saver << text;                       // просто суём все в файл
    saver.close();
}


void Bookshelf::load(std::string filename){ // Этот метод загружает информацию из файла
    std::string word;
    std::string line;
    std::string title;
    std::string author;
    int pages;
    std::ifstream loader(filename);    // создаём поток чтения
    int shelf_number = -1;            // счётчик полок
    
    while (!loader.eof()){          // пока не наступил конец файла end_of_file
        std::getline(loader, line);// берем строчку из потока loader, складываем её в строковую переменную line
        if(line == "") break;     // если строчка пустая, файл кончился
        std::stringstream linestream(line); // создаем поток строки и сразу кладём в него нашу строку
        word = "";
        linestream >> word;     
        if (word == "Полка"){  // если первое взятое из потока слово -- Полка,
            shelf_number++;   // то нужно увеличить номер полоки
            continue;        // и перейти на следующую иттерацию цикла
            // если условие выполнилось, continue телепортирует нас на следующую строчку файла
           // а блок цикла while начинается с начала c этой новой строкой
          // в которой уже не Полка номер, а данные о книжке
        }
        title = split_by_comma(linestream); // если мы не в строке с полкой, то записываем все слова названия
        author = split_by_comma(linestream); // до запятой, а затем автора
        linestream >> pages; // пагесы можно записать без понтов, мы точно знаем, что в строке только они
        // интересный факт -- поток еще и умеет записывать текст из файла в int, преобразуя в число, удобно

        // мы собрали из файла данные о книжке, теперь можно её создать
        this->addBook(shelf_number, PrintBook(title, author, pages)); 

    }

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////



Bookshelf::Bookshelf(unsigned int size) : shelves(size){    // конструктор, делает вектор полок размера size
}


bool Bookshelf::findBook(std::string title, std::string author) {  // проверка наличия книги в шкафу
    for (Shelf shelf : shelves){
        if (shelf.findBook(title, author)) return true;

    }
    return false;
}

/*
 * пора объяснить, почему капуста (абстракция)
 * в методе ниже есть эпическая запись
 * shelves[number].getPlace(getBook(title, author));
 * где number на самом деле тоже является результатом вызова какого-то метода
 * и получается что-то такое:
 * элемент_массива[так, метод поиска номера нужного элемента, найди мне номер]
 * и для него вызывается .метод_поиска_места()
 *
 * (этот метод был эпичнее, правда, но я его поменяла, но принцип понятен наверное
 * в main будут записи длиннее и с большим количиством участников)
 *
 * в итоге получается, что шкаф просто заставляет маленькие методы кооперироваться
 * и выполнять задачу для шкафа
 * и их описание похоже на капусту ._.
 */
// метод ниже выводит "адрес" -- два числа, номер полки и место книги на ней


/// Этот метод больше не пишет ничего, он возвращает строку
std::string Bookshelf::writeAddress(std::string title, std::string author) {
    unsigned int number = 0;
    unsigned int place = 0;
    std::string address = "";
    if (this->findBook(title, author)){
        number = findShelf(title, author);
        place = shelves[number].getPlace(title, author);
        address = std::string("Номер полки: ")
                + std::to_string(number)
                + std::string(" Место на полке: ")
                + std::to_string(place)
                + std::string("\n");
    } else address = std::string("Книга с названием ")
                        + title + std::string(" и автором ")
                        + author + std::string(" не найдена");
    return address;
}


void Bookshelf::addBook(unsigned int shelf_number, PrintBook abook) { // говорит полке добавить книгу
    shelves[shelf_number].addBook(abook);
}


/// Этот метод больше не пишет в консоль, он возвращает строку, слепленную из данных о всех книгах
std::string Bookshelf::writeAll() {    
    std::string all;
    int c = 0;
    for (Shelf shelf : shelves){
        all += "Полка " + std::to_string(c) + "\n";
        all += shelf.writeShelf();
        c++;
    }
    return all;
}


/// Тоже не пишет, а делает строку
std::string Bookshelf::writeShelf(unsigned int number) {   // выводит содержимое полке
    if(shelves.size() > number)
        return shelves[number].writeShelf(); // точнее, говорит полке самовывестись )
    return "Нет полки с таким номером";
}


void Bookshelf::removeBook(std::string title, std::string author) {    // удадяет книгу
    shelves[findShelf(title, author)].removeBook(title, author);      // мне очень нравится
}

void Bookshelf::removeBook(unsigned int shelf_number, unsigned int place) {   // удаляет книгу с места
    shelves[shelf_number].removeBook(place);
}


std::string Bookshelf::getSize() {    // возвращает размер шкафа
    return std::to_string(shelves.size());
}

/// Не пишет а возвращает строку
std::string Bookshelf::writeNumber() { // пишет размер шкафа на экран
    int all = 0;
    for (Shelf shelf : shelves){
        all += shelf.getSize();
    }
    return std::to_string(all) + std::string("\n");
}



//// Этот метод оказался не нужен. Некоторые другие методы тоже, но их стало лень убирать
/// а этот нет
//void Bookshelf::writeSize() {   // пишет размер полки
//    std::cout << shelves.size() << std::endl;
//}


////////////////////////////////// Эти методы используют исключения //////////////////////////////////////////

unsigned int Bookshelf::findShelf(std::string title, std::string author){ // возвращает полку на которой книга
    for (int i = 0; i < shelves.size(); i++){
        if (shelves[i].findBook(title, author))
            return i;
    }   // если ни на одной из полок этой книги нет
    throw std::domain_error("Книга с названием " + title + " и автором " + author + " не найдена\n");
}

PrintBook & Bookshelf::getBook(std::string title, std::string author) {// возвращает книгу по названию и автору
    return shelves[findShelf(title, author)].getBook(title, author);
}


PrintBook & Bookshelf::getBook(unsigned int place, unsigned int shelf_number) { // возвращает книгу по адресу
    return shelves[shelf_number].getBook(place);
}

void Bookshelf::putBook(PrintBook afterbook, PrintBook putbook) { // говорит полке
    shelves[findShelf(afterbook.getTitle(), afterbook.getAuthor())].putBook(afterbook, putbook);
}
    
/////////////////////////////////////////////////////////////////////////////////////////////////////////////


Bookshelf::~Bookshelf() {
}
