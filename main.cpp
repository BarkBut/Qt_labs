#include "mainwindow.h"
#include <QApplication>

/// Автогенерируемый файл

// main по умолчанию принимает аргументы командной строки, но это не используется
int main(int argc, char *argv[])
{
    QApplication a(argc, argv); // пересылка сигналов и слотов
    MainWindow w;              // отрисовка главного окна
    w.show();                 // говорим главному окну появится

    return a.exec();    // возвращает статус завершения работы окна
}
