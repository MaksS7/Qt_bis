#ifndef DIHE_H
#define DIHE_H
#include <QString>
#include <QDebug>

class DiHe
{
public:
    DiHe();
    DiHe(unsigned long long int _g, unsigned long long int _p, unsigned long long int _outOpen);
    unsigned long long int getG();
    unsigned long long int getP();
    unsigned long long int getInOpen();
    unsigned long long int getHide();
    unsigned long long int getKey();
    unsigned long long int getInKey();
    void setOutOpen(unsigned long long int _out);
    void randInt();

protected:
    unsigned long long int key(long long Open, long long Hide);
    unsigned long long int g = 0;
    unsigned long long int p = 0;
    unsigned long long int Hide = 0;
    unsigned long long int outOpen = 0;
    unsigned long long int inOpen = 0;
    unsigned long long int inKey = 0;
    unsigned long long int outKey = 0;
    unsigned long long int openKey();

};

#endif // DIHE_H
