#include "vij.h"
#include <QDebug>
#include <math.h>

Vij::Vij(QString mod):
    strChar(mod)
{

}

QString Vij::reSpace(QString str)
{
    for(int i(0); i < str.length(); i++) {
        if(str[i] == " ") {
            str.remove(i, 1);
            i--;
        }
    }
    return str;
}

QString Vij::crip(QString str, QString key)
{
    qDebug()<<"*-----------------------------------------*";
    qDebug()<<"Key"<<key<<endl;
    qDebug()<<"First step Vij"<<str<<endl;

    str = reSpace(str);
    qDebug()<<"Next step"<<str<<endl;
    QString outStr;
    QVector<int> intKey;
    foreach(auto &i, key) {
        intKey.append(strChar.indexOf(i));
    }
    qDebug()<<"Next step"<<intKey<<endl;
    int loop(0);
    qDebug()<<"-------------------------------------------";
    foreach(auto &i, str) {
        int index = strChar.indexOf(i);
        index = ((index + intKey[loop])+strChar.length()) % strChar.length();
        outStr.append(strChar[index]);
        index = 0;
        loop++;
        if(loop == key.length()) {
            loop = 0;
        }
        qDebug()<<"Next step"<<outStr<<endl;
    }
    qDebug()<<"-------------------------------------------";
    qDebug()<<"End Vij"<<outStr<<endl;
    qDebug()<<"*-----------------------------------------*";
    return outStr;
}

QString Vij::uncrip(QString crip, QString key)
{
    qDebug()<<"*-----------------------------------------*";
    qDebug()<<"Key"<<key<<endl;
    qDebug()<<"First step Vij"<<crip<<endl;
    QString outStr;
    QVector<int> intKey;
    foreach(auto &i, key) {
        intKey.append(strChar.indexOf(i));
    }
    qDebug()<<"Next step"<<intKey<<endl;
    int loop(0);
    qDebug()<<"-------------------------------------------";
    foreach(auto &i, crip) {
        int index = strChar.indexOf(i);
        index = ((index - intKey[loop])+strChar.length()) % strChar.length();
        outStr.append(strChar[index]);
        index = 0;
        loop++;
        if(loop == key.length()) {
            loop = 0;
        }
        qDebug()<<"Next step"<<outStr<<endl;
    }
    qDebug()<<"-------------------------------------------";
    qDebug()<<"End Vij"<<outStr<<endl;
    qDebug()<<"*-----------------------------------------*";
    return outStr;
}
