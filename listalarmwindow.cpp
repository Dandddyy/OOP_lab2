#include "listalarmwindow.h"
#include "ui_listalarmwindow.h"

ListAlarmWindow::ListAlarmWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ListAlarmWindow)
{
    ui->setupUi(this);
}

ListAlarmWindow::~ListAlarmWindow()
{
    delete ui;
}

void ListAlarmWindow::slot5(std::string list[20], int s)
{
    for(int i = 0; i < s; i++){
        ui->listWidget->addItem(QString::fromStdString(list[i]));
    }
}

void ListAlarmWindow::on_pushButton_clicked()
{
    close();
}


void ListAlarmWindow::on_pushButton_2_clicked()
{
    if(ui->listWidget->count() > 0){
        QString item = ui->listWidget->currentItem()->text();
        int index = ui->listWidget->currentRow();
        ui->listWidget->takeItem(index);
        emit signal6(item);
    }
}


void ListAlarmWindow::on_pushButton_3_clicked()
{
    if(ui->listWidget->count() > 0){
        QString item = ui->listWidget->currentItem()->text();
        emit signal7(item);
    }
}

