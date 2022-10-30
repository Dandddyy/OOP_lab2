#include "addalarmwindow.h"
#include "ui_addalarmwindow.h"

AddAlarmWindow::AddAlarmWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddAlarmWindow)
{
    ui->setupUi(this);
}

AddAlarmWindow::~AddAlarmWindow()
{
    delete ui;
}

void AddAlarmWindow::on_pushButton_2_clicked()
{
    close();
}


void AddAlarmWindow::on_pushButton_clicked()
{
    bool checkbox = false;
    QString LineText = "";
    QString Name = "";
    QString time = ui->timeEdit->text();
    if(ui->checkBox->isChecked()){
        LineText = ui->lineEdit->text();
    }
    if(ui->checkBox_2->isChecked()){
        checkbox = true;
    }
    Name = ui->lineEdit_2->text();
    if(LineText.size() > 20){
        ui->label_3->setText("Більше 20 символів");
    }
    if(Name.size() <= 20){
        if(LineText.size() <= 20){
            emit signal4(time, LineText, Name, checkbox);
            close();
        }
    }
    else{
        ui->label_4->setText("Більше 20 символів");
    }
}

