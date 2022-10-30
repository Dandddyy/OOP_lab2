#ifndef LISTTIMERWINDOW_H
#define LISTTIMERWINDOW_H

#include <QDialog>
#include <string>

namespace Ui {
class ListTimerWindow;
}

class ListTimerWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ListTimerWindow(QWidget *parent = nullptr);
    ~ListTimerWindow();

public slots:
    void slot1(std::string list[20], int s);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::ListTimerWindow *ui;

signals:

    void signal2(QString);

    void signal3(QString);
};

#endif // LISTTIMERWINDOW_H
