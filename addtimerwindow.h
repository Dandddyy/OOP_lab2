#ifndef ADDTIMERWINDOW_H
#define ADDTIMERWINDOW_H
#include <string>
#include <QDialog>

namespace Ui {
class AddTimerWindow;
}

class AddTimerWindow : public QDialog
{
    Q_OBJECT

public:
    explicit AddTimerWindow(QWidget *parent = nullptr);
    ~AddTimerWindow();

private slots:

    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::AddTimerWindow *ui;

signals:
    void signal(QString, QString, QString, bool);
};

#endif // ADDTIMERWINDOW_H
