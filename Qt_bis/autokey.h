#ifndef AUTOKEY_H
#define AUTOKEY_H
#include "QString"

class autokey
{
public:
    autokey(QString _strChar);
    QString crip(QString str, QString key);
    QString uncrip(QString crip, QString key);
    QString reSpace(QString str);
protected:
    QString strChar;
};

#endif // AUTOKEY_H
