#ifndef BIS_H
#define BIS_H

#include <QMainWindow>
#include "horizshift.h"
#include "vij.h"
#include "autokey.h"
#include "feist.h"
#include "dihe.h"
#include "rsa.h"

QT_BEGIN_NAMESPACE
namespace Ui { class bis; }
QT_END_NAMESPACE

class bis : public QMainWindow
{
    Q_OBJECT

public:
    bis(QWidget *parent = nullptr);
    ~bis();

protected:
    QString bubSort(QString str);
    DiHe *diA;
    DiHe *diB;
    Encrypt *rsaA;
    Encrypt *rsaB;
    bool debug;
    QString strChar = "abcdefghijklmnopqrstuvwxyzабвгдеёжзийклмнопрстуфхцчшщъыьэюя";

protected slots:
    void crip();
    void uncrip();
    void clearDihe();

private slots:
    void on_btnClear_clicked();

    void on_btnDihe_A_clicked();

    void on_btnDihe_B_clicked();

    void on_btnDihe_key_from_a_clicked();

    void on_btnDihe_Key_From_B_clicked();

    void on_btnRSA_Open_A_clicked();

    void on_btnRSA_Open_B_clicked();

    void on_btnRSA_Decript_A_clicked();

    void on_actionRussian_toggled(bool arg1);

    void on_actionEnglish_toggled(bool arg1);

    void on_actionDebug_info_triggered(bool checked);

private:
    Ui::bis *ui;
};
#endif // BIS_H
