#include "mainwindow.h"
#include <QApplication>
using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("Таймер");
    w.setWindowIcon(QIcon(":/img/image/icon.png"));
    w.show();
    return a.exec();
}
