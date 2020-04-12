#ifndef FEIST_H
#define FEIST_H
#include <QString>
#include "autokey.h"
#include "vij.h"


class Feist
{
public:
    Feist(QString _strChar);
    QString crip(QString str, QString key);
    QString uncrip(QString crip, QString key);
protected:
    QString strChar;
    QString reSpace(QString str);
};

#endif // FEIST_H
