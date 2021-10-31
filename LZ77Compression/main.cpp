#include "mainwindow.h"
#include "LZ77Compression/LZ77Compression.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
