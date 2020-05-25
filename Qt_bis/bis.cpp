/*Версия от 25.05.2020*/
#include "bis.h"
#include "ui_bis.h"
#include <iostream>
#include <QDebug>

bis::bis(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::bis)
{
    ui->setupUi(this);
//    QString strRus = "абвгдеёжзийклмнопрстуфхцчшщъыьэюя";
//    QString strEng = "abcdefghijklmnopqrstuvwxyz";
//    QString key = "cipher";
//    QString text = "the treasure is buried near the house";
    QString key = ui->lineKey->text();
    QString text = ui->lineSource->text();

    ui->btnUnCrip->setEnabled(false);
    ui->btnDihe_B->setEnabled(false);
    ui->btnDihe_key_from_a->setEnabled(false);
    ui->btnDihe_Key_From_B->setEnabled(false);
    ui->btnRSA_Decript_A->setEnabled(false);
    ui->btnRSA_Open_B->setEnabled(false);
    connect(ui->btnCrip, SIGNAL(clicked()),
            this, SLOT(crip()));
    connect(ui->btnUnCrip, SIGNAL(clicked()),
            this, SLOT(uncrip()));
    connect(ui->btnDihe_Clear, SIGNAL(clicked()),
            this, SLOT(clearDihe()));
    on_actionEnglish_toggled(true);
}

bis::~bis()
{
    delete ui;
}

void bis::crip()
{
    QString str = ui->lineSource->text();
    QString key = ui->lineKey->text();
    QString outStr;
    if(ui->checkHoriz->isChecked()){
        horizshift shift;
        outStr = shift.crip(str, key);
    } else if(ui->checkVij->isChecked()) {
        Vij vij(strChar);
        outStr = vij.crip(str, key);
    } else if(ui->checkAutoKey->isChecked()) {
        autokey ak(strChar);
        outStr = ak.crip(str, key);
    } else if(ui->checkFeist->isChecked()) {
        Feist fs(strChar);
        outStr = fs.crip(str, key);
    } else {
        qDebug()<<"Choose a cipher!";
        return;
    }
    ui->btnUnCrip->setEnabled(true);
    ui->lineCript->setText(outStr);
    qDebug() << "Text Encrypted";
}
void bis::uncrip()
{
    QString crip = ui->lineCript->text();
    QString key = ui->lineKey->text();
    QString outStr;
    if(ui->checkHoriz->isChecked()) {
        horizshift shift;
        outStr = shift.uncrip(crip, key);
    } else if(ui->checkVij->isChecked()) {
        Vij vij(strChar);
        outStr = vij.uncrip(crip, key);
    } else if(ui->checkAutoKey->isChecked()) {
        autokey ak(strChar);
        outStr = ak.uncrip(crip, key);
    } else if(ui->checkFeist->isChecked()) {
        Feist fs(strChar);
        outStr = fs.uncrip(crip, key);
    }
    ui->btnUnCrip->setEnabled(false);
    ui->lineUncript->setText(outStr);
    qDebug() << "Text Decrypted";
}

void bis::clearDihe()
{
    ui->lineDihe_key->clear();
}

void bis::on_btnClear_clicked()
{
    ui->lineUncript->clear();
}

void bis::on_btnDihe_A_clicked()
{
    qDebug()<<"*---------------------------------------------------*";
    diA = new DiHe;
    ui->lineDihe_g->setText(QString::number(diA->getG()));
    ui->lineDihe_p->setText(QString::number(diA->getP()));
    ui->lineDihe_A->setText(QString::number(diA->getInOpen()));
    ui->lineDihe_Hide_A->setText(QString::number(diA->getHide()));
    if(diA->getInKey() != 0) {
        ui->btnDihe_B->setEnabled(true);
    } else {
        qDebug() << "Err: key is 0, please reset number";
    }
    qDebug()<<"*---------------------------------------------------*";
}

void bis::on_btnDihe_B_clicked()
{
    qDebug()<<"*---------------------------------------------------*";
    unsigned long long int g = ui->lineDihe_g->text().toInt();
    unsigned long long int p = ui->lineDihe_p->text().toInt();
    unsigned long long int OpenKey = ui->lineDihe_A->text().toInt();
    diB = new DiHe(g, p, OpenKey);
    ui->lineDihe_B->setText(QString::number(diB->getInOpen()));
    ui->lineDihe_Hide_B->setText(QString::number(diB->getHide()));
    diA->setOutOpen(diB->getInOpen());
    ui->btnDihe_key_from_a->setEnabled(true);
    ui->btnDihe_Key_From_B->setEnabled(true);
    qDebug()<<"*---------------------------------------------------*";
}

void bis::on_btnDihe_key_from_a_clicked()
{
    qDebug()<<"*---------------------------------------------------*";
    ui->lineDihe_key->setText(QString::number(diA->getKey()));
    qDebug()<<"*---------------------------------------------------*";
}

void bis::on_btnDihe_Key_From_B_clicked()
{
    qDebug()<<"*---------------------------------------------------*";
    ui->lineDihe_key->setText(QString::number(diB->getKey()));
    qDebug()<<"*---------------------------------------------------*";
}

void bis::on_btnRSA_Open_A_clicked()
{
    qDebug()<<"*--------------------A--------------------*";
    rsaA = new Encrypt();
    QVector<int64_t> temp = rsaA->getOpenKey();
    QString str = QString::number(temp[0]) + ";" + QString::number(temp[1]);
    ui->lineRSA_Open_A->setText(str);
    ui->btnRSA_Open_B->setEnabled(true);
    qDebug()<<"*--------------------EA--------------------*";
}

void bis::on_btnRSA_Open_B_clicked()
{
    qDebug()<<"*--------------------B--------------------*";
    rsaB = new Encrypt();
//    QVector<uintmax_t> temp = rsaB->getOpenKey();
//    QString str = QString::number(temp[0]) + ";" + QString::number(temp[1]);
//    ui->lineRSA_Open_B->setText(str);
    QVector<int64_t> temp = rsaA->getOpenKey();
    qDebug()<<"Open Key A"<<temp;
    QString text = ui->lineRSA_Source->text();
    QString cript = rsaB->cript(text, temp[0], temp[1]);  //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! предовать полноый ключ
    ui->lineRSA_Cripted->clear();
    ui->lineRSA_Cripted->setText(cript);
    ui->btnRSA_Decript_A->setEnabled(true);
    qDebug()<<"*--------------------EB--------------------*";
}

void bis::on_btnRSA_Decript_A_clicked()
{
    qDebug()<<"*-----------------------------------------*";
    QString text = ui->lineRSA_Cripted->text();
    QStringList tempStr = text.split(";");
    ui->lineRSA_Decripted->setText(rsaA->decript(tempStr));
    qDebug()<<"*-----------------------------------------*";
}
//translate gui rus/eng.
void bis::on_actionRussian_toggled(bool arg1)
{
    ui->labelSL->setText("Исходный текст");
    ui->labelSL_RSA->setText("Исходный текст");
    ui->labelKey->setText("Ключ");
    ui->labelKey_DiHe->setText("Ключ");
    ui->labelOpenA->setText("Открытый ключ А");
    ui->labelOpenB->setText("Открытый ключ Б");
    ui->labelOpenG->setText("Открытое Г");
    ui->labelOpenP->setText("Открытое П");
    ui->labelOpenA_RSA->setText("Открытый ключ А");
    ui->labelHideA_DiHe->setText("Закрытый ключ А");
    ui->labelHideB_DiHe->setText("Закрытый ключ Б");
    ui->labelCriptedSL->setText("Зашифрованное сообщение");
    ui->labelDecriptedSL->setText("Восстановленное сообщение");
    ui->labelCripted_RSA->setText("Зашифрованное сообщение");
    ui->labelDecripted_RSA->setText("Восстановленное сообщение");
    ui->labelKey->setText("Ключ");
    ui->btnCrip->setText("Зашифровать");
    ui->btnUnCrip->setText("Расшифровать");
    ui->btnClear->setText("Очистить");
    ui->btnDihe_Clear->setText("Очистить");
    ui->btnDihe_A->setText("Открытый ключ А");
    ui->btnDihe_B->setText("Открытый ключ Б");
    ui->btnDihe_key_from_a->setText("Ключ из А");
    ui->btnDihe_Key_From_B->setText("Ключ из Б");
    ui->btnRSA_Open_A->setText("Открытый ключ");
    ui->btnRSA_Decript_A->setText("Расшифровать");
    ui->btnRSA_Open_B->setText("Зашифровать для А");
    ui->actionRussian->setEnabled(!arg1);
    ui->actionEnglish->setEnabled(arg1);
    ui->actionEnglish->setCheckable(!arg1);
    ui->actionEnglish->setCheckable(arg1);
}

void bis::on_actionEnglish_toggled(bool arg1)
{
    ui->labelSL->setText("Source massage");
    ui->labelSL_RSA->setText("Source message");
    ui->labelKey->setText("Key");
    ui->labelKey_DiHe->setText("Key");
    ui->labelOpenA->setText("Open key A");
    ui->labelOpenB->setText("Open key B");
    ui->labelOpenG->setText("Open G");
    ui->labelOpenP->setText("Open P");
    ui->labelOpenA_RSA->setText("Open key A");
    ui->labelHideA_DiHe->setText("Hiden key B");
    ui->labelHideB_DiHe->setText("Hiden key Б");
    ui->labelCriptedSL->setText("Encrypt message");
    ui->labelDecriptedSL->setText("Decrypted message");
    ui->labelCripted_RSA->setText("Encrypt message");
    ui->labelDecripted_RSA->setText("Decrypted message");
    ui->labelKey->setText("Key");
    ui->btnCrip->setText("Encrypting");
    ui->btnUnCrip->setText("Decrypting");
    ui->btnClear->setText("Clear");
    ui->btnDihe_Clear->setText("Clear");
    ui->btnDihe_A->setText("Open key A");
    ui->btnDihe_B->setText("Open key B");
    ui->btnDihe_key_from_a->setText("Key from A");
    ui->btnDihe_Key_From_B->setText("Key from B");
    ui->btnRSA_Open_A->setText("Open key");
    ui->btnRSA_Decript_A->setText("Decrypting");
    ui->btnRSA_Open_B->setText("Encrypting for A");
    ui->actionEnglish->setChecked(arg1);
    ui->actionEnglish->setEnabled(!arg1);
    ui->actionRussian->setEnabled(arg1);
    ui->actionRussian->setCheckable(!arg1);
    ui->actionRussian->setCheckable(arg1);
}

//uint64_t sqre(uint64_t x) {
//    return x * x;
//}

//uint64_t binpow(uint64_t a, uint64_t e, uint64_t mod = ULLONG_MAX) {
//    uint64_t temp = e == 0 ? 1 : (e & 1U ? a * binpow(a, e - 1, mod) % mod : sqre(binpow(a, e / 2, mod)) % mod);
//    qDebug()<<temp<<endl;
//    return temp;
//}

void bis::on_actionDebug_info_triggered(bool checked)
{
    debug = checked;
}
