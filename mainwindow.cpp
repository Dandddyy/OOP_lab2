#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->listWidget->addItem("Додати таймер");
    ui->listWidget->addItem("Додати будильник");

    size = 0;
    aSize = 0;

    ui->label->setText("Таймерів немає");
    ui->label_3->setText("-----");
    ui->label_2->setText("Будильників немає");
    ui->label_4->setText("-----");
    ui->statusbar->showMessage(QTime::currentTime().toString("hh:mm:ss"));

    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(slotTimerAlarm()));
    timer->start(1000);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::MainTimer(std::string time, int iter){

    finaltime[iter] = time;

    strToInt(time, iter);

    res[iter] = 0;
    res[iter] += ihour[iter];
    res[iter] *= 60;
    res[iter] += iminute[iter];
    res[iter] *= 60;
    res[iter] += isecond[iter];
}

void MainWindow::AlgTimer(int iter){

    res[iter]--;

    isecond[iter] = res[iter] % 60;
    iminute[iter] = (res[iter]/60) % 60;
    ihour[iter] = (res[iter]/60) / 60;

    std::string hour = "00";
    std::string minute = "00";
    std::string second = "00";

    if(ihour[iter] < 10){
        hour[0] = '0';
        hour[1] = ihour[iter] + '0';
    }
    else{
        hour = std::to_string(ihour[iter]);
    }
    if(iminute[iter] < 10){
        minute[0] = '0';
        minute[1] = iminute[iter] + '0';
    }
    else{
        minute = std::to_string(iminute[iter]);
    }
    if(isecond[iter] < 10){
        second[0] = '0';
        second[1] = isecond[iter] + '0';
    }
    else{
        second = std::to_string(isecond[iter]);
    }

    for(int i = 0; i < 8; i++){
        if (i < 2) {
            finaltime[iter][i] = hour[i];
        }
        if (i > 2 && i < 5) {
            finaltime[iter][i] = minute[i - 3];
        }
        if (i > 5) {
            finaltime[iter][i] = second[i - 6];
        }
    }

}

void MainWindow::strToInt(std::string time, int iter) {

        std::string hour = "00";
        std::string minute = "00";
        std::string second = "00";

        for (int i = 0; i < 8; i++) {
            if (i < 2) {
                hour[i] = time[i];
            }
            if (i > 2 && i < 5) {
                minute[i - 3] = time[i];
            }
            if (i > 5) {
                second[i - 6] = time[i];
            }
        }
        ihour[iter] = atoi(hour.c_str());
        iminute[iter] = atoi(minute.c_str());
        isecond[iter] = atoi(second.c_str());

}

void MainWindow::AlarmAlg(std::string time, std::string time1, int iter){

    ares[iter] = 0;
    std::string hour = "00";
    std::string minute = "00";
    std::string hour1 = "00";
    std::string minute1 = "00";
    int iHour;
    int iMinute;
    int iHour1;
    int iMinute1;

    for (int i = 0; i < 5; i++) {
        if (i < 2) {
            hour[i] = time[i];
        }
        if (i > 2) {
            minute[i - 3] = time[i];
        }
    }
    iHour = atoi(hour.c_str());
    iMinute = atoi(minute.c_str());

    for (int i = 0; i < 5; i++) {
        if (i < 2) {
            hour1[i] = time1[i];
        }
        if (i > 2) {
            minute1[i - 3] = time1[i];
        }
    }
    iHour1 = atoi(hour1.c_str());
    iMinute1 = atoi(minute1.c_str());

    if(iHour == iHour1){
        if(iMinute1 > iMinute){
            if(iHour == 0){
                ares[iter] = 60 + iMinute - iMinute1;
                iHour = 23;
            }
            else{
                ares[iter] = 60 + iMinute - iMinute1;
                iHour--;
            }
            while(iHour != iHour1){
                if(iHour == 0){
                    ares[iter] = 60 + iMinute - iMinute1;
                    iHour = 23;
                }
                else{
                    ares[iter] = 60 + iMinute - iMinute1;
                    iHour--;
                }
            }
        }
        else{
            ares[iter] = iMinute - iMinute1;
        }
    }
    else{
        while(iHour != iHour1){
            if(iHour == 0){
                ares[iter] = 60 + iMinute - iMinute1;
                iHour = 23;
            }
            else{
                ares[iter] = 60 + iMinute - iMinute1;
                iHour--;
            }
        }
    }
}

void MainWindow::on_action_triggered()
{
    QApplication::quit();
}


void MainWindow::on_pushButton_clicked()
{
    QString item = ui->listWidget->currentItem()->text();

    if(item == "Додати таймер"){
        if(size < 20){
            window = new AddTimerWindow;
            window->show();
            connect(window, &AddTimerWindow::signal, this, &MainWindow::slot);
        }
        else{
            QMessageBox::critical(this, "Помилка", "Досягнута максимальна кількість таймерів");
        }
    }
    else if(item == "Додати будильник"){
        if(aSize < 20){
            awindow = new AddAlarmWindow;
            awindow->show();
            connect(awindow, &AddAlarmWindow::signal4, this, &MainWindow::slot4);
        }
        else{
            QMessageBox::critical(this, "Помилка", "Досягнута максимальна кількість будильників");
        }
    }
}

void MainWindow::slot(QString a, QString b, QString c, bool d)
{
    std::string strSize = std::to_string(size + 1);

    MainTimer(a.toStdString(), size);
    line[size] = b.toStdString();
    firsttime[size] = a.toStdString();
    checkbox[size] = d;

    if(d == false){
        if(c.toStdString() == "" && b.toStdString() == ""){
            List[size] = "Таймер №" + strSize + ":    " + a.toStdString();
            name[size] = "Таймер №" + strSize;
        }
        else if(c.toStdString() != "" && b.toStdString() == ""){
            List[size] = c.toStdString() + ":    " + a.toStdString();
            name[size] = c.toStdString();
        }
        else if(c.toStdString() == "" && b.toStdString() != ""){
            List[size] = "Таймер №" + strSize + ":    " + a.toStdString() + "    Текст: " + b.toStdString() + ")";
            name[size] = "Таймер №" + strSize;
        }
        else if(c.toStdString() != "" && b.toStdString() != ""){
            List[size] = c.toStdString() + ":    " + a.toStdString() + "    Текст: " + b.toStdString() + ")";
            name[size] = c.toStdString();
        }
    }
    else{
        if(c.toStdString() == "" && b.toStdString() == ""){
            List[size] = "Таймер №" + strSize + ":    " + a.toStdString() + "    (Не турбувати)";
            name[size] = "Таймер №" + strSize;
        }
        else if(c.toStdString() != "" && b.toStdString() == ""){
            List[size] = c.toStdString() + ":    " + a.toStdString() + "    (Не турбувати)";
            name[size] = c.toStdString();
        }
        else if(c.toStdString() == "" && b.toStdString() != ""){
            List[size] = "Таймер №" + strSize + ":    " + a.toStdString() + "    Текст: " + b.toStdString() + ")    (Не турбувати)";
            name[size] = "Таймер №" + strSize;
        }
        else if(c.toStdString() != "" && b.toStdString() != ""){
            List[size] = c.toStdString() + ":    " + a.toStdString() + "    Текст: " + b.toStdString() + ")    (Не турбувати)";
            name[size] = c.toStdString();
        }
    }
    size++;
}

void MainWindow::slot2(QString item)
{
    for(int i = 0; i < size; i++){
        if(List[i] == item.toStdString()){
            for(int j = i; j < size - 1; j++){
                List[j] = List[j + 1];
                res[j] = res[j + 1];
                finaltime[j] = finaltime[j + 1];
                firsttime[j] = firsttime[j + 1];
                line[j] = line[j + 1];
                name[j] = name[j + 1];
                ihour[j] = ihour[j + 1];
                iminute[j] = iminute[j + 1];
                isecond[j] = isecond[j + 1];
                checkbox[j] = checkbox[j + 1];
            }
            List[size - 1] = "";
            res[size - 1] = 0;
            finaltime[size - 1] = "";
            firsttime[size - 1] = "";
            line[size - 1] = "";
            name[size - 1] = "";
            ihour[size - 1] = 0;
            iminute[size - 1] = 0;
            isecond[size - 1] = 0;
            checkbox[size - 1] = false;
        }
    }
    size--;
}

void MainWindow::slot3(QString item)
{
    for(int i = 0; i < size; i++){
        if(List[i] == item.toStdString()){
            MainTimer(firsttime[i], i);
        }
    }
}

void MainWindow::slot4(QString a, QString b, QString c, bool d)
{
    std::string strSize = std::to_string(aSize + 1);

    aLine[aSize] = b.toStdString();
    aFirsttime[aSize] = a.toStdString();
    aFinaltime[aSize] = aFirsttime[aSize];
    acheckbox[aSize] = d;

    if(acheckbox[aSize] == false){
        if(c.toStdString() == "" && b.toStdString() == ""){
            aList[aSize] = "Будильник №" + strSize + ":    " + a.toStdString();
            aName[aSize] = "Будильник №" + strSize;
        }
        else if(c.toStdString() != "" && b.toStdString() == ""){
            aList[aSize] = c.toStdString() + ":    " + a.toStdString();
            aName[aSize] = c.toStdString();
        }
        else if(c.toStdString() == "" && b.toStdString() != ""){
            aList[aSize] = "Будильник №" + strSize + ":    " + a.toStdString() + "    Текст: " + b.toStdString() + ")";
            aName[aSize] = "Будильник №" + strSize;
        }
        else if(c.toStdString() != "" && b.toStdString() != ""){
            aList[aSize] = c.toStdString() + ":    " + a.toStdString() + "    Текст: " + b.toStdString() + ")";
            aName[aSize] = c.toStdString();
        }
    }
    else{
        if(c.toStdString() == "" && b.toStdString() == ""){
            aList[aSize] = "Будильник №" + strSize + ":    " + a.toStdString() + "    (Не турбувати)";
            aName[aSize] = "Будильник №" + strSize;
        }
        else if(c.toStdString() != "" && b.toStdString() == ""){
            aList[aSize] = c.toStdString() + ":    " + a.toStdString() + "    (Не турбувати)";
            aName[aSize] = c.toStdString();
        }
        else if(c.toStdString() == "" && b.toStdString() != ""){
            aList[aSize] = "Будильник №" + strSize + ":    " + a.toStdString() + "    Текст: " + b.toStdString() + ")    (Не турбувати)";
            aName[aSize] = "Будильник №" + strSize;
        }
        else if(c.toStdString() != "" && b.toStdString() != ""){
            aList[aSize] = c.toStdString() + ":    " + a.toStdString() + "    Текст: " + b.toStdString() + ")    (Не турбувати)";
            aName[aSize] = c.toStdString();
        }
    }
    aSize++;
}

void MainWindow::slot6(QString item)
{
    for(int i = 0; i < aSize; i++){
        if(aList[i] == item.toStdString()){
            for(int j = i; j < aSize - 1; j++){
                aList[j] = aList[j + 1];
                ares[j] = ares[j + 1];
                aFinaltime[j] = aFinaltime[j + 1];
                aFirsttime[j] = aFirsttime[j + 1];
                aLine[j] = aLine[j + 1];
                aName[j] = aName[j + 1];
            }
            aList[aSize - 1] = "";
            ares[aSize - 1] = 0;
            aFinaltime[aSize - 1] = "";
            aFirsttime[aSize - 1] = "";
            aLine[aSize - 1] = "";
            aName[aSize - 1] = "";
        }
    }
    aSize--;
}

void MainWindow::slot7(QString item)
{
    for(int i = 0; i < aSize; i++){
        if(aList[i] == item.toStdString()){
            aFinaltime[i] = aFirsttime[i];
        }
    }
}

void MainWindow::slotTimerAlarm()
{
    int kolTimers = 0;
    int checker = 0;
    for(int i = 0; i < size; i++){
        if(res[i] > 0){
            if(res[checker] > res[i] || res[checker] <= 0){
                checker = i;
            }
        }
    }
    for(int i = 0; i < size; i++){
        if(finaltime[i].size() != 0 && res[i] > 0){
            AlgTimer(i);
            kolTimers++;
        }
    }
    if(finaltime[checker].size() == 0){
        ui->label->setText("Таймерів немає");
        ui->label_3->setText("-----");
    }
    else if(finaltime[checker] == "00:00:00"){
        if(line[checker] == ""){
            if(checkbox[checker] == false){
                QApplication::beep();
                QMessageBox::warning(this, "Увага", QString::fromStdString(name[checker] + ": Кінець таймеру"));
            }
            finaltime[checker] = "";
        }
        else{
            if(checkbox[checker] == false){
                QApplication::beep();
                QMessageBox::warning(this, "Увага", QString::fromStdString(name[checker] + ": " + line[checker]));
            }
            finaltime[checker] = "";
        }
    }
    else{
        ui->label_3->setText(QString::fromStdString(name[checker]));
        if(kolTimers > 1){
            ui->label->setText(QString::fromStdString(finaltime[checker] + "\n (" + std::to_string(kolTimers) + ")"));
        }
        else{
            ui->label->setText(QString::fromStdString(finaltime[checker]));
        }
    }

    int kolAlarms = 0;
    int achecker = 0;
    for(int i = 0; i < aSize; i++){
        AlarmAlg(aFinaltime[i], (QTime::currentTime().toString("hh:mm")).toStdString(), i);
        if(aFinaltime[i] != ""){
            kolAlarms++;
        }
    }
    for(int i = 0; i < aSize; i++){
        if(ares[i] >= 0){
            if(ares[achecker] > ares[i] || aFinaltime[achecker] == ""){
                achecker = i;
            }
        }
    }
    if(aFinaltime[achecker].size() == 0){
        ui->label_2->setText("Будильників немає");
        ui->label_4->setText("-----");
    }
    else if(aFinaltime[achecker] == (QTime::currentTime().toString("hh:mm")).toStdString()){
        if(aLine[achecker] == ""){
            if(acheckbox[achecker] == false){
                QApplication::beep();
                QMessageBox::warning(this, "Увага", QString::fromStdString(aName[achecker] + ": Кінець будильнику"));
            }
            aFinaltime[achecker] = "";
        }
        else{
            if(acheckbox[achecker] == false){
                QApplication::beep();
                QMessageBox::warning(this, "Увага", QString::fromStdString(aName[achecker] + ": " + aLine[achecker]));
            }
            aFinaltime[achecker] = "";
        }
    }
    else{
        ui->label_4->setText(QString::fromStdString(aName[achecker]));
        if(kolAlarms > 1){
            ui->label_2->setText(QString::fromStdString(aFinaltime[achecker] + "\n (" + std::to_string(kolAlarms) + ")"));
        }
        else{
            ui->label_2->setText(QString::fromStdString(aFinaltime[achecker]));
        }

    }
    ui->statusbar->showMessage(QTime::currentTime().toString("hh:mm:ss"));
}


void MainWindow::on_toolButton_clicked()
{
    lstwindow = new ListTimerWindow;
    lstwindow->show();
    connect(this, &MainWindow::signal1, lstwindow, &ListTimerWindow::slot1);
    connect(lstwindow, &ListTimerWindow::signal2, this, &MainWindow::slot2);
    connect(lstwindow, &ListTimerWindow::signal3, this, &MainWindow::slot3);
    emit signal1(List, size);
}


void MainWindow::on_toolButton_2_clicked()
{
    alstwindow = new ListAlarmWindow;
    alstwindow->show();
    connect(this, &MainWindow::signal5, alstwindow, &ListAlarmWindow::slot5);
    connect(alstwindow, &ListAlarmWindow::signal6, this, &MainWindow::slot6);
    connect(alstwindow, &ListAlarmWindow::signal7, this, &MainWindow::slot7);
    emit signal5(aList, aSize);
}

//dfgfdg
