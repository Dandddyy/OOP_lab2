#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "addtimerwindow.h"
#include "listtimerwindow.h"
#include "addalarmwindow.h"
#include "listalarmwindow.h"
#include <QTimer>
#include <QTime>
#include <stdlib.h>
#include <string>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    int GetASize(){return aSize;}
    int GetSize(){return size;}

private slots:
    void on_action_triggered();

    void on_pushButton_clicked();

    void slot(QString a, QString b, QString c, bool d);

    void slot2(QString item);

    void slot3(QString item);

    void slot4(QString a, QString b, QString c, bool d);

    void slot6(QString item);

    void slot7(QString item);

    void slotTimerAlarm();

    void MainTimer(std::string time, int iter);

    void AlgTimer(int iter);

    void strToInt(std::string time, int iter);

    void AlarmAlg(std::string time, std::string time1, int iter);

    void on_toolButton_clicked();

    void on_toolButton_2_clicked();

private:
    Ui::MainWindow *ui;
    AddTimerWindow *window;
    ListTimerWindow *lstwindow;
    AddAlarmWindow *awindow;
    ListAlarmWindow *alstwindow;
    QTimer *timer;
    std::string finaltime[20];
    std::string line[20];
    std::string name[20];
    std::string firsttime[20];
    std::string aFinaltime[20];
    std::string aLine[20];
    std::string aName[20];
    std::string aFirsttime[20];
    int ihour[20];
    int iminute[20];
    int isecond[20];
    int res[20];
    int ares[20];
    std::string List[20];
    std::string aList[20];
    int size;
    int aSize;
    bool checkbox[20];
    bool acheckbox[20];

signals:
    void signal1(std::string[20], int);
    void signal5(std::string[20], int);
};
#endif // MAINWINDOW_H
