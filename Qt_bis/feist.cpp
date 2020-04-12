#include "feist.h"
#include <QDebug>
#include <iostream>

Feist::Feist(QString _strChar):
    strChar(_strChar)
{

}

QString Feist::reSpace(QString str)
{
    for(int i(0); i < str.length(); i++) {
        if(str[i] == " ") {
            str.remove(i, 1);
            i--;
        }
    }
    return str;
}

QString Feist::crip(QString str, QString key)
{
    qDebug()<<"*-----------------------------------------*";
    qDebug()<<"Key"<<key<<endl;
    qDebug()<<"First step Fei"<<str<<endl;

    str = reSpace(str);
    qDebug()<<"Next step"<<str<<endl;
    QString outStr;
    Vij ak(strChar);
    QString left, right;
    int sizeStr = 0;
    QString mist = " ";

    if(str.length() %2 ) {
        sizeStr = str.length() - str.length() % 2;
        mist[0] = str[sizeStr / 2];
    } else {
        sizeStr = str.length();
    }
    right = str.right(sizeStr / 2);
    left = str.left(sizeStr / 2);
    qDebug()<<"Next step"<<right<<endl;
    qDebug()<<"Next step"<<left<<endl;

    QString tempCrip;
    QString test;
    QString test1;

    qDebug()<<"-------------------------------------------";
    for(int i(0); i < 3; i++) {
        tempCrip = ak.crip(left, key);
        for(int j(0); j < tempCrip.length(); j++) {
            right[j] = strChar[((strChar.indexOf(right[j]) ^ strChar.indexOf(tempCrip[j])) + strChar.length()) % strChar.length()];
        }
        QString temp = right;
        right = left;
        left = temp;
        qDebug()<<"Next step r"<<right<<endl;
        qDebug()<<"Next step l"<<left<<endl;
        tempCrip.clear();
    }
    qDebug()<<"-------------------------------------------";

    outStr.append(left);
    if(mist != " ") {
        outStr.append(mist);
    }
    outStr.append(right);
    qDebug()<<"Next step"<<outStr<<endl;

//    for(int i(0); i < outStr.length(); i++) {
//        outStr[i] = outStr[i].unicode() + 100;
//    }
    qDebug()<<"End Fei"<<outStr<<endl;
    qDebug()<<"*-----------------------------------------*";
    return outStr;
}

QString Feist::uncrip(QString crip, QString key)
{
    qDebug()<<"*-----------------------------------------*";
    qDebug()<<"Key"<<key<<endl;
    qDebug()<<"First step Fei"<<crip<<endl;
//    for(int i(0); i < crip.length(); i++) {
//        crip[i] = crip[i].unicode() - 100;
//    }
    qDebug()<<"Next step"<<crip<<endl;
    crip = reSpace(crip);
    qDebug()<<"Next step"<<crip<<endl;
    QString outStr;
    Vij ak(strChar);
    QString left, right;
    int sizeStr = 0;
    QString mist = " ";

    if(crip.length() % 2) {
        sizeStr = crip.length() - crip.length() % 2;
        mist[0] = crip[sizeStr / 2];
    } else {
        sizeStr = crip.length();
    }
    right = crip.right(sizeStr / 2);
    left = crip.left(sizeStr / 2);
    qDebug()<<"Next step"<<right<<endl;
    qDebug()<<"Next step"<<left<<endl;

    QString tempCrip;
//    QString temp = right;
//    right = left;
//    left = temp;
    qDebug()<<"-------------------------------------------";
    for(int i(0); i < 3; i++) {
        tempCrip = ak.crip(right, key);
        for(int j(0); j < tempCrip.length(); j++) {
            left[j] = strChar[((strChar.indexOf(left[j]) ^ strChar.indexOf(tempCrip[j])) + strChar.length()) % strChar.length()];
        }
        QString temp = right;
        right = left;
        left = temp;
        qDebug()<<"Next step"<<right<<endl;
        qDebug()<<"Next step"<<left<<endl;
        tempCrip.clear();
    }
    qDebug()<<"-------------------------------------------";

//    temp = right;
//    right = left;
//    left = temp;

    outStr.append(left);
    if(mist != " ") {
        outStr.append(mist);
    }
    outStr.append(right);
    qDebug()<<"End Fei"<<outStr<<endl;
    qDebug()<<"*-----------------------------------------*";
    return outStr;
}
