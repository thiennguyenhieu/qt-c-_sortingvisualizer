#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":/SortVisualizerIcon.png"));

    MainWindow window;
    window.show();

    return a.exec();
}
