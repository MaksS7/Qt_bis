#include "autokey.h"
#include <QDebug>

autokey::autokey(QString _strChar):
    strChar(_strChar)

{

}

QString autokey::reSpace(QString str)
{
    for(int i(0); i < str.length(); i++) {
        if(str[i] == " ") {
            str.remove(i, 1);
            i--;
        }
    }
    return str;
}

QString autokey::crip(QString str, QString key)
{
    qDebug()<<"*-----------------------------------------*";
    qDebug()<<"Key"<<key<<endl;
    qDebug()<<"First step AK"<<str<<endl;

    str = reSpace(str);
    qDebug()<<"Next step"<<str<<endl;
    QString outStr;
    key.append(str);
    qDebug()<<"Next step"<<key<<endl;
    QVector<int> intKey;
    foreach(auto &i, key) {
        intKey.append(strChar.indexOf(i));
    }
    qDebug()<<"Next step"<<intKey<<endl;

    int loop(0);
    qDebug()<<"-------------------------------------------";
    foreach(auto &i, str) {
        int index = strChar.indexOf(i);
        index = ((index + intKey[loop]) + strChar.length()) % strChar.length();
        outStr.append(strChar[index]);
        index = 0;
        loop++;
        if(loop == key.length()) {
            loop = 0;
        }
        qDebug()<<"Next step"<<outStr<<endl;
    }
    qDebug()<<"-------------------------------------------";
    qDebug()<<"End AK"<<outStr<<endl;
    qDebug()<<"*-----------------------------------------*";
    return outStr;
}

QString autokey::uncrip(QString crip, QString key)
{
    qDebug()<<"*-----------------------------------------*";
    qDebug()<<"Key"<<key<<endl;
    qDebug()<<"First step AK"<<crip<<endl;
    QString outStr;
    QVector<int> intKey;
    int tempSizeLength = key.length();
    foreach(auto &i, key) {
        intKey.append(strChar.indexOf(i));
    }
    qDebug()<<"Next step"<<intKey<<endl;
    int loop(0);
    qDebug()<<"-------------------------------------------";
    foreach(auto &i, crip) {
        int index = strChar.indexOf(i);
        index = ((index - intKey[loop])+strChar.length()) % strChar.length();
        key.append(strChar[index]);
        intKey.append(strChar.indexOf(strChar[index]));
        index = 0;
        loop++;
        if(loop == key.length()) {
            loop = 0;
        }
        qDebug()<<"Next step"<<key<<endl;
        qDebug()<<"Next step"<<intKey<<endl;
    }
    qDebug()<<"-------------------------------------------";
    outStr = key.remove(0, tempSizeLength);
    qDebug()<<"-------------------------------------------";
    qDebug()<<"End AK"<<outStr<<endl;
    qDebug()<<"*-----------------------------------------*";
    return outStr;
}
