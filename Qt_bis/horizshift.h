#ifndef HORIZSHIFT_H
#define HORIZSHIFT_H
#include <QString>

class horizshift
{
public:
    horizshift();
    ~horizshift();
    QString crip(QString str, QString key);
    QString uncrip(QString crip, QString key);
protected:
    QString bubSort(QString str);
};

#endif // HORIZSHIFT_H
