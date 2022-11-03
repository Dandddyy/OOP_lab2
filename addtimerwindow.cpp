#include "addtimerwindow.h"
#include "ui_addtimerwindow.h"
#include <QString>
#include <string>


AddTimerWindow::AddTimerWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddTimerWindow)
{
    ui->setupUi(this);
}

AddTimerWindow::~AddTimerWindow()
{
    delete ui;
}

void AddTimerWindow::on_pushButton_2_clicked()
{
    close();
}

void AddTimerWindow::on_pushButton_clicked()
{
    int checkForSpace = 0;
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
    if(time == "00:00:00"){
        ui->label_5->setText("Таймера немає");
    }
    for(int i = 0; i < Name.size(); i++){
        if(Name[i] == ' '){
            checkForSpace++;
        }
    }
    if(checkForSpace == Name.size()){
        Name = "";
    }
    if(Name.size() <= 20){
        if(LineText.size() <= 20 && time != "00:00:00"){
            emit signal(time, LineText, Name , checkbox);
            close();
        }
    }
    else{
        ui->label_4->setText("Більше 20 символів");
    }
}

