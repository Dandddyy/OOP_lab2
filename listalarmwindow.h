#ifndef LISTALARMWINDOW_H
#define LISTALARMWINDOW_H
#include <string>
#include <QDialog>

namespace Ui {
class ListAlarmWindow;
}

class ListAlarmWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ListAlarmWindow(QWidget *parent = nullptr);
    ~ListAlarmWindow();

public slots:

    void slot5(std::string list[20], int s);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::ListAlarmWindow *ui;

signals:

    void signal6(QString);

    void signal7(QString);
};

#endif // LISTALARMWINDOW_H
