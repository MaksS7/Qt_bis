/*Версия от 25.05.2020*/
#include "horizshift.h"
#include <QDebug>
#include <QWidget>

horizshift::horizshift()
{
}

horizshift::~horizshift()
{

}
QString horizshift::bubSort(QString str)
{
    for(int i(0); i < str.length(); i++) {
        for(int j(0); j < str.length(); j++) {
            if(str[j] > str[i]) {
                QChar temp = str[j];
                str[j] = str[i];
                str[i] = temp;
            }
        }
    }
    return str;
}

QString reSpace(QString str)
{
    for(int i(0); i < str.length(); i++) {
        if(str[i] == " ") {
            str.remove(i, 1);
            i--;
        }
    }
    return str;
}

QString horizshift::crip(QString str, QString key)
{
    qDebug()<<"*-----------------------------------------*";
    QStringList list;
    QString tempKey = key;
    qDebug()<<"Key"<<key<<endl;
    qDebug()<<"First step Hor"<<str<<endl;
    str = reSpace(str);
    qDebug()<<"Next step"<<str<<endl;
    QString temp;
    for(int j(0); j < key.length(); j++) {
        for(int i(j); i < str.length(); i += key.length()) {
            temp += str[i];
        }
        list.append(temp);
        temp.clear();
    }
    qDebug()<<"Next step"<<list<<endl;
    qDebug()<<"-------------------------------------------";

    for(int i(0); i < key.length(); i++) {
        for(int j(0); j < key.length(); j++) {
            if(key[j] > key[i]){
                QChar tempChar = key[j];
                key[j] = key[i];
                key[i] = tempChar;

                temp = list[j];
                list[j] = list[i];
                list[i] = temp;
            }
        }
        qDebug()<<"Next step "<<list<<endl;
    }
    qDebug()<<"-------------------------------------------";

    QString outStr;
    foreach(auto &i, list) {
        outStr.append(i + " ");
    }
    qDebug()<<"End Hor"<<outStr<<endl;
    qDebug()<<"*-----------------------------------------*";

    return outStr;
}

QString horizshift::uncrip(QString crip, QString key)
{
    qDebug()<<"*-----------------------------------------*";
    qDebug()<<"Key"<<key<<endl;
    qDebug()<<"First step Hor"<<crip<<endl;

    QString temp;
    QStringList list;
    list = crip.split(" ");
    list.removeLast();
    qDebug()<<"Next step"<<list<<endl;

    QVector<int> keyInt;
    QString tempKey = bubSort(key);
    qDebug()<<"Key"<<tempKey<<endl;

    QStringList outList = list;

    for(int i (0); i < key.length(); i++) {
        for(int j(0); j < key.length(); j++) {
            if(key[i] == tempKey[j]) {
                keyInt.append(j);
                tempKey.replace(j, 1, " ");
            }
        }
    }
    qDebug()<<"Key"<<keyInt<<endl;

    for(int i(0); i < keyInt.length(); i++) {
        outList[i] = list[keyInt[i]];
    }
    qDebug()<<"Next step"<<outList<<endl;

    for(int i(0); i < list.length(); i++){
        for(int j(0); j < list[i].length(); j++) {
            list[i].replace(j, 1, " ");
        }
    }
    qDebug()<<"Next step"<<list<<endl;

    for(int i(0); i < outList.length(); i++){
        for(int j(0); j < outList[i].length(); j++) {
            list[j][i] = outList[i][j];
        }
    }
    qDebug()<<"Next step"<<list<<endl;

    QString outStr;
    foreach(auto &i, list) {
        outStr.append(i);
    }
    qDebug()<<"End Hor"<<outStr<<endl;
    qDebug()<<"*-----------------------------------------*";
    return outStr;
}
