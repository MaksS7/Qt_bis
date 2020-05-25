#ifndef RSA_H
#define RSA_H
#include <QString>
#include <cmath>
#include <QDebug>

class Encrypt
{
public:
    Encrypt();
    QVector<int64_t> OpenKey;
    QVector<int64_t> getOpenKey();
    int64_t getP();
    int64_t getQ();
    int64_t getN();
    int64_t crip;
    int64_t uncrip;
    int64_t cript(int64_t a, int64_t e, int64_t mod = LONG_MAX);
    QString cript(QString tempStr, int64_t e, int64_t mod = LONG_MAX);
    int64_t decript(int64_t m);
    QString decript(QStringList str);


protected:
    QVector<int64_t> HideKey;
    int64_t p;
    int64_t q;
    int64_t n;
    int64_t fi;
    int64_t d;
    int64_t m;
    int64_t e;
    QString engText = "the treasure is buried near the house";
};

#endif // RSA_H
