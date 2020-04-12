#ifndef VIJ_H
#define VIJ_H
#include <QString>


class Vij
{
public:
    Vij(QString _strChar);
    QString crip(QString str, QString key);
    QString uncrip(QString crip, QString key);
    QString strChar = "abcdefghijklmnopqrstuvwxyzабвгдеёжзийклмнопрстуфхцчшщъыьэюя";
    QString reSpace(QString str);
};

#endif // VIJ_H
