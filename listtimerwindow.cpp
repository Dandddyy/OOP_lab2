#include "listtimerwindow.h"
#include "ui_listtimerwindow.h"

ListTimerWindow::ListTimerWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ListTimerWindow)
{
    ui->setupUi(this);
}

ListTimerWindow::~ListTimerWindow()
{
    delete ui;
}

void ListTimerWindow::slot1(std::string list[20], int s)
{
    for(int i = 0; i < s; i++){
        ui->listWidget->addItem(QString::fromStdString(list[i]));
    }
}

void ListTimerWindow::on_pushButton_clicked()
{
    close();
}


void ListTimerWindow::on_pushButton_2_clicked()
{
    if(ui->listWidget->count() > 0){
        QString item = ui->listWidget->currentItem()->text();
        int index = ui->listWidget->currentRow();
        ui->listWidget->takeItem(index);
        emit signal2(item);
    }
}


void ListTimerWindow::on_pushButton_3_clicked()
{
    if(ui->listWidget->count() > 0){
        QString item = ui->listWidget->currentItem()->text();
        emit signal3(item);
    }
}

