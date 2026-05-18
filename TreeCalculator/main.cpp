#include "mainwindow.h"
#include <QApplication>
#include <QFile>
#include <QTextStream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":/icons/terraria_.ico"));
    QFile file(":/style/style.qss");
    if (file.open(QFile::ReadOnly | QFile::Text)) {
        QTextStream stream(&file);
        a.setStyleSheet(stream.readAll());
    }

    MainWindow w;
    w.show();

    return a.exec();
}
