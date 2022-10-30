#ifndef ADDALARMWINDOW_H
#define ADDALARMWINDOW_H
#include <string>
#include <QDialog>

namespace Ui {
class AddAlarmWindow;
}

class AddAlarmWindow : public QDialog
{
    Q_OBJECT

public:
    explicit AddAlarmWindow(QWidget *parent = nullptr);
    ~AddAlarmWindow();

private slots:

    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::AddAlarmWindow *ui;

signals:
    void signal4(QString, QString, QString, bool);
};

#endif // ADDALARMWINDOW_H
