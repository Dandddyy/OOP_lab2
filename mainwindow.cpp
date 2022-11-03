#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    size = 0;
    aSize = 0;
    finalListSize = 0;

    ui->comboBox->addItem("Від старого до нового");
    ui->comboBox->addItem("Від нового до старого");
    ui->comboBox->addItem("Спочатку таймери");
    ui->comboBox->addItem("Спочатку будильники");
    ui->comboBox->addItem("За часом до закінчкння (від < до >)");
    ui->comboBox->addItem("За часом до закінчкння (від > до <)");
    ui->label->setText("Таймерів немає");
    ui->label_3->setText("-----");
    ui->label_2->setText("Будильників немає");
    ui->label_4->setText("-----");
    ui->statusbar->showMessage(QTime::currentTime().toString("hh:mm:ss"));
    ui->pushButton->hide();
    ui->pushButton_2->hide();

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

    strToInt(time, iter, 0);

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

void MainWindow::strToInt(std::string time, int iter, bool CH) {

    std::string hour = "00";
    std::string minute = "00";
    std::string second = "00";
    if(CH == 0){
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
    else{
        int inhour;
        int inminute;
        int insecond;
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
        inhour = atoi(hour.c_str());
        inminute = atoi(minute.c_str());
        insecond = atoi(second.c_str());

        Result[iter] = 0;
        Result[iter] += inhour;
        Result[iter] *= 60;
        Result[iter] += inminute;
        Result[iter] *= 60;
        Result[iter] += insecond;
    }
}

void MainWindow::AlarmAlg(std::string time, std::string time1, int iter, bool CH){
    if(CH == 0){
        ares[iter] = 0;
    }
    else{
        Result[iter] = 0;
    }
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

    if(CH == 0){
        if(iHour == iHour1){
            if(iMinute1 > iMinute){
                if(iHour == 0){
                    ares[iter] = 60 + iMinute - iMinute1;
                    iHour = 23;
                    iMinute1 = 0;
                    iMinute = 0;
                }
                else{
                    ares[iter] = 60 + iMinute - iMinute1;
                    iHour--;
                    iMinute1 = 0;
                    iMinute = 0;
                }
                while(iHour != iHour1){
                    if(iHour == 0){
                        ares[iter] += 60 + iMinute - iMinute1;
                        iHour = 23;
                    }
                    else{
                        ares[iter] += 60 + iMinute - iMinute1;
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
                    ares[iter] += 60 + iMinute - iMinute1;
                    iHour = 23;
                    iMinute1 = 0;
                    iMinute = 0;
                }
                else{
                    ares[iter] += 60 + iMinute - iMinute1;
                    iHour--;
                    iMinute1 = 0;
                    iMinute = 0;
                }
            }
        }
    }
    else{
        if(iHour == iHour1){
            if(iMinute1 > iMinute){
                if(iHour == 0){
                    Result[iter] = 60 + iMinute - iMinute1;
                    iHour = 23;
                    iMinute1 = 0;
                    iMinute = 0;
                }
                else{
                    Result[iter] = 60 + iMinute - iMinute1;
                    iHour--;
                    iMinute1 = 0;
                    iMinute = 0;
                }
                while(iHour != iHour1){
                    if(iHour == 0){
                        Result[iter] += 60 + iMinute - iMinute1;
                        iHour = 23;
                    }
                    else{
                        Result[iter] += 60 + iMinute - iMinute1;
                        iHour--;
                    }
                }
            }
            else{
                Result[iter] = iMinute - iMinute1;
            }
        }
        else{
            while(iHour != iHour1){
                if(iHour == 0){
                    Result[iter] += 60 + iMinute - iMinute1;
                    iHour = 23;
                    iMinute1 = 0;
                    iMinute = 0;
                }
                else{
                    Result[iter] += 60 + iMinute - iMinute1;
                    iHour--;
                    iMinute1 = 0;
                    iMinute = 0;
                }
            }
        }
    }
}

bool MainWindow::DoNotDisturb(std::string firstT, std::string secondT, std::string currentT)
{
    bool check = true;
    if(ui->checkBox->isChecked()){
        int ifirstT;
        int isecondT;
        int icurrentT;
        std::string shour = "00";
        std::string sminute = "00";

        shour[0] = firstT[0];
        shour[1] = firstT[1];
        sminute[0] = firstT[3];
        sminute[1] = firstT[4];
        ifirstT = atoi(shour.c_str())*60 + atoi(sminute.c_str());

        shour[0] = secondT[0];
        shour[1] = secondT[1];
        sminute[0] = secondT[3];
        sminute[1] = secondT[4];
        isecondT = atoi(shour.c_str())*60 + atoi(sminute.c_str());

        shour[0] = currentT[0];
        shour[1] = currentT[1];
        sminute[0] = currentT[3];
        sminute[1] = currentT[4];
        icurrentT = atoi(shour.c_str())*60 + atoi(sminute.c_str());

        if(ifirstT < isecondT){
            if(ifirstT <= icurrentT && icurrentT <= isecondT){
                check = false;
            }
        }
        else{
            if(ifirstT <= icurrentT || icurrentT <= isecondT){
                check = false;
            }
        }
    }
    return check;
}

void MainWindow::on_action_triggered()
{
    QApplication::quit();
}


void MainWindow::on_pushButton_clicked()
{
    QString item = ui->listWidget->currentItem()->text();
    int index = ui->listWidget->currentRow();
    ui->listWidget->takeItem(index);
    for(int i = 0; i < finalListSize; i++){
        if(finalList[i] == item.toStdString()){

            for(int k = 0; k < 20; k++){
                if(k < size){
                    if(List[k] == finalList[i]){
                        for(int j = k; j < size - 1; j++){
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
                        for(int q = i; q < finalListSize - 1; q++){
                            finalList[q] = finalList[q + 1];
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
                        finalList[finalListSize - 1] = "";
                        finalListSize--;
                        size--;
                        k = 20;
                    }
                }
                if(k < aSize){
                    if(aList[k] == finalList[i]){
                        for(int j = k; j < aSize - 1; j++){
                            aList[j] = aList[j + 1];
                            ares[j] = ares[j + 1];
                            aFinaltime[j] = aFinaltime[j + 1];
                            aFirsttime[j] = aFirsttime[j + 1];
                            aLine[j] = aLine[j + 1];
                            aName[j] = aName[j + 1];
                        }
                        for(int q = i; q < finalListSize - 1; q++){
                            finalList[q] = finalList[q + 1];
                        }
                        aList[aSize - 1] = "";
                        ares[aSize - 1] = 0;
                        aFinaltime[aSize - 1] = "";
                        aFirsttime[aSize - 1] = "";
                        aLine[aSize - 1] = "";
                        aName[aSize - 1] = "";
                        finalList[finalListSize - 1] = "";
                        finalListSize--;
                        aSize--;
                    }
                }
            }
        }
    }
    if(ui->listWidget->count() == 0){
        ui->pushButton->hide();
        ui->pushButton_2->hide();
    }
}

void MainWindow::slot(QString a, QString b, QString c, bool d)
{
    MainTimer(a.toStdString(), size);
    line[size] = b.toStdString();
    firsttime[size] = a.toStdString();
    checkbox[size] = d;

    if(c.toStdString() == ""){
        bool ch = true;
        for(int k = 1; k < size + 2; k++){
            ch = true;
            for(int i = 0; i < size; i++){
                if(name[i] == "Таймер №" + std::to_string(k)){
                    ch = false;
                }
            }
            if(ch == true){
                name[size] = "Таймер №" + std::to_string(k);
                k = size + 2;
            }
        }
    }
    else{
        name[size] = c.toStdString();
    }

    if(d == false){
        if(b.toStdString() == ""){
            List[size] = name[size] + ":    " + a.toStdString();
        }
        else{
            List[size] = name[size] + ":    " + a.toStdString() + "    «" + b.toStdString() + "»";
        }
    }
    else{
        if(b.toStdString() == ""){
            List[size] = name[size] + ":    " + a.toStdString() + "    (Не турбувати)";
        }
        else{
            List[size] = name[size] + ":    " + a.toStdString() + "    «" + b.toStdString() + "»    (Не турбувати)";
        }
    }

    finalList[finalListSize] = List[size];
    ui->listWidget->addItem(QString::fromStdString(finalList[finalListSize]));
    finalListSize++;
    size++;
    ui->pushButton->show();
    ui->pushButton_2->show();
    ui->pushButton_3->click();
}

void MainWindow::slot4(QString a, QString b, QString c, bool d)
{
    aLine[aSize] = b.toStdString();
    aFirsttime[aSize] = a.toStdString();
    aFinaltime[aSize] = aFirsttime[aSize];
    acheckbox[aSize] = d;

    if(c.toStdString() == ""){
        bool ch = true;
        std::string strSize = std::to_string(aSize + 1);
        int k = 0;
        while(aName[aSize] == ""){
            for(int i = 0; i < aSize; i++){
                if(aName[i] == "Будильник №" + strSize){
                    ch = false;
                }
            }
            if(ch == true){
                aName[aSize] = "Будильник №" + strSize;
            }
            k++;
            strSize = std::to_string(k);
        }
    }
    else{
        aName[aSize] = c.toStdString();
    }

    if(acheckbox[aSize] == false){
        if(b.toStdString() == ""){
            aList[aSize] = aName[aSize] + ":    " + a.toStdString();
        }
        else{
            aList[aSize] = aName[aSize] + ":    " + a.toStdString() + "    «" + b.toStdString() + "»";
        }
    }
    else{
        if(b.toStdString() == ""){
            aList[aSize] = aName[aSize] + ":    " + a.toStdString() + "    (Не турбувати)";
        }
        else {
            aList[aSize] = aName[aSize] + ":    " + a.toStdString() + "    «" + b.toStdString() + "»    (Не турбувати)";
        }
    }

    finalList[finalListSize] = aList[aSize];
    ui->listWidget->addItem(QString::fromStdString(finalList[finalListSize]));
    ui->pushButton->show();
    ui->pushButton_2->show();
    finalListSize++;
    aSize++;
    ui->pushButton_3->click();
}

void MainWindow::slotTimerAlarm()
{   
    QString F = ui->timeEdit->text();
    QString S = ui->timeEdit_2->text();
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
            if(checkbox[checker] == false && DoNotDisturb(F.toStdString(), S.toStdString(), (QTime::currentTime().toString("hh:mm")).toStdString()) == true){
                QApplication::beep();
                QMessageBox::warning(this, "Увага", QString::fromStdString(name[checker] + ": Кінець таймеру"));
            }
            finaltime[checker] = "";
        }
        else{
            if(checkbox[checker] == false && DoNotDisturb(F.toStdString(), S.toStdString(), (QTime::currentTime().toString("hh:mm")).toStdString()) == true){
                QApplication::beep();
                QMessageBox::warning(this, "Увага", QString::fromStdString(name[checker] + ": " + line[checker]));
            }
            finaltime[checker] = "";
        }
    }
    else{
        ui->label_3->setText(QString::fromStdString(name[checker]));
        if(kolTimers > 1){
            ui->label->setText(QString::fromStdString(finaltime[checker] + " (" + std::to_string(kolTimers) + ")"));
        }
        else{
            ui->label->setText(QString::fromStdString(finaltime[checker]));
        }
    }

    int kolAlarms = 0;
    int achecker = 0;
    for(int i = 0; i < aSize; i++){
        AlarmAlg(aFinaltime[i], (QTime::currentTime().toString("hh:mm")).toStdString(), i, 0);
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
            if(acheckbox[achecker] == false && DoNotDisturb(F.toStdString(), S.toStdString(), (QTime::currentTime().toString("hh:mm")).toStdString()) == true){
                QApplication::beep();
                QMessageBox::warning(this, "Увага", QString::fromStdString(aName[achecker] + ": Кінець будильнику"));
            }
            aFinaltime[achecker] = "";
        }
        else{
            if(acheckbox[achecker] == false && DoNotDisturb(F.toStdString(), S.toStdString(), (QTime::currentTime().toString("hh:mm")).toStdString()) == true){
                QApplication::beep();
                QMessageBox::warning(this, "Увага", QString::fromStdString(aName[achecker] + ": " + aLine[achecker]));
            }
            aFinaltime[achecker] = "";
        }
    }
    else{
        ui->label_4->setText(QString::fromStdString(aName[achecker]));
        if(kolAlarms > 1){
            ui->label_2->setText(QString::fromStdString(aFinaltime[achecker] + " (" + std::to_string(kolAlarms) + ")"));
        }
        else{
            ui->label_2->setText(QString::fromStdString(aFinaltime[achecker]));
        }
    }
    ui->statusbar->showMessage(QTime::currentTime().toString("hh:mm:ss"));
}


void MainWindow::on_toolButton_clicked()
{
    if(size < 20){
        window = new AddTimerWindow;
        window->setWindowTitle("Додати таймер");
        window->setWindowIcon(QIcon(":/img/image/icon.png"));
        window->show();
        connect(window, &AddTimerWindow::signal, this, &MainWindow::slot);
    }
    else{
        QMessageBox::critical(this, "Помилка", "Досягнута максимальна кількість таймерів");
    }
}

void MainWindow::on_toolButton_2_clicked()
{
    if(aSize < 20){
        awindow = new AddAlarmWindow;
        awindow->setWindowTitle("Додати будильник");
        awindow->setWindowIcon(QIcon(":/img/image/icon.png"));
        awindow->show();
        connect(awindow, &AddAlarmWindow::signal4, this, &MainWindow::slot4);
    }
    else{
        QMessageBox::critical(this, "Помилка", "Досягнута максимальна кількість будильників");
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    if(ui->listWidget->count() > 0){
        QString item = ui->listWidget->currentItem()->text();
        for(int i = 0; i < aSize; i++){
            if(aList[i] == item.toStdString()){
                aFinaltime[i] = aFirsttime[i];
            }
        }
        for(int i = 0; i < size; i++){
            if(List[i] == item.toStdString()){
                MainTimer(firsttime[i], i);
            }
        }
    }
}

void MainWindow::on_pushButton_3_clicked()
{
    QString text = ui->comboBox->currentText();

    if(text == "Від старого до нового"){
        for(int i = finalListSize - 1; i >= 0; i--){
            ui->listWidget->takeItem(i);
        }
        for(int i = 0; i < finalListSize; i++){
            ui->listWidget->addItem(QString::fromStdString(finalList[i]));
        }
    }
    else if(text == "Від нового до старого"){
        for(int i = finalListSize - 1; i >= 0; i--){
            ui->listWidget->takeItem(i);
        }
        for(int i = finalListSize - 1; i >= 0; i--){
            ui->listWidget->addItem(QString::fromStdString(finalList[i]));
        }
    }
    else if(text == "Спочатку таймери"){
        for(int i = finalListSize - 1; i >= 0; i--){
            ui->listWidget->takeItem(i);
        }
        int k = 0;
        for(int i = 0; i < finalListSize; i++){
            if(i < size){
                ui->listWidget->addItem(QString::fromStdString(List[i]));
            }
            else{
                ui->listWidget->addItem(QString::fromStdString(aList[k]));
                k++;
            }
        }
    }
    else if(text == "Спочатку будильники"){
        for(int i = finalListSize - 1; i >= 0; i--){
            ui->listWidget->takeItem(i);
        }
        int k = 0;
        for(int i = 0; i < finalListSize; i++){
            if(i < aSize){
                ui->listWidget->addItem(QString::fromStdString(aList[i]));
            }
            else{
                ui->listWidget->addItem(QString::fromStdString(List[k]));
                k++;
            }
        }
    }
    else if(text == "За часом до закінчкння (від < до >)"){
        std::string L[40];
        for(int i = finalListSize - 1; i >= 0; i--){
            ui->listWidget->takeItem(i);
        }
        int k = 0;
        int z = 0;
        for(int i = 0; i < finalListSize; i++){
            if(finalList[i] == aList[k]){
                AlarmAlg(aFirsttime[k], (QTime::currentTime().toString("hh:mm")).toStdString(), i, 1);
                k++;
                Result[i] *= 60;
            }
            if(finalList[i] == List[z]){
                strToInt(firsttime[i], i, 1);
                z++;
            }
            L[i] = finalList[i];
        }
        int i, key, j;
        std::string key2;
        for (i = 1; i < finalListSize; i++)
        {
            key = Result[i];
            key2 = L[i];
            j = i - 1;
            while (j >= 0 && Result[j] > key)
            {
                Result[j + 1] = Result[j];
                L[j + 1] = L[j];
                j = j - 1;
            }
            Result[j + 1] = key;
            L[j + 1] = key2;
        }
        for(i = 0; i < finalListSize; i++){
            ui->listWidget->addItem(QString::fromStdString(L[i]));
        }
    }
    else if(text == "За часом до закінчкння (від > до <)"){
        std::string L[40];
        for(int i = finalListSize - 1; i >= 0; i--){
            ui->listWidget->takeItem(i);
        }
        int k = 0;
        int z = 0;
        for(int i = 0; i < finalListSize; i++){
            if(finalList[i] == aList[k]){
                AlarmAlg(aFirsttime[k], (QTime::currentTime().toString("hh:mm")).toStdString(), i, 1);
                k++;
                Result[i] *= 60;
            }
            if(finalList[i] == List[z]){
                strToInt(firsttime[i], i, 1);
                z++;
            }
            L[i] = finalList[i];
        }
        int i, key, j;
        std::string key2;
        for (i = 1; i < finalListSize; i++)
        {
            key = Result[i];
            key2 = L[i];
            j = i - 1;
            while (j >= 0 && Result[j] < key)
            {
                Result[j + 1] = Result[j];
                L[j + 1] = L[j];
                j = j - 1;
            }
            Result[j + 1] = key;
            L[j + 1] = key2;
        }
        for(i = 0; i < finalListSize; i++){
            ui->listWidget->addItem(QString::fromStdString(L[i]));
        }
    }
}

