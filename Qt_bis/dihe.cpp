/*Версия от 25.05.2020*/
#include "dihe.h"
#include <QRandomGenerator>
#include <cmath>

DiHe::DiHe()
{
    randInt();
}

DiHe::DiHe(unsigned long long _g, unsigned long long _p, unsigned long long _outOpen):
    g(_g),
    p(_p),
    outOpen(_outOpen)
{
    randInt();
    if(key(outOpen, Hide) == inKey) {
        qDebug() << "Key Cheked!";
    } else {
        qDebug() << "Err: Overflow need reset b";
    }
}

unsigned long long int DiHe::getG()
{
    return g;
}

unsigned long long int DiHe::getP()
{
    return p;
}

unsigned long long int DiHe::openKey()
{
    return (long long int) pow(g, Hide) % p;
}

unsigned long long DiHe::key(long long Open, long long Hide)
{
    return (long long int) pow(Open, Hide) % p;
}

unsigned long long DiHe::getInOpen()
{
    return inOpen;
}

unsigned long long DiHe::getHide()
{
    return Hide;
}

unsigned long long DiHe::getKey()
{
    if(key(outOpen, Hide) == inKey){
        unsigned long long temp = key(outOpen, Hide);
        qDebug()<<"get key"<<temp<<": "<<outOpen<<"^"<<Hide<<"%"<<p;
        return temp;
    } else {
        qDebug() << "Err: Error in number key please reset number";
        return 0;
    }
}

unsigned long long DiHe::getInKey()
{
    return inKey;
}

void DiHe::setOutOpen(unsigned long long _out)
{
    outOpen = _out;
}

void DiHe::randInt()
{
    while(true){
        if(p == 0 && g == 0){
            p = QRandomGenerator::global()->bounded(5000);
            g = QRandomGenerator::global()->bounded(5,10);
        }
        Hide = QRandomGenerator::global()->bounded(5,20);
        if(Hide != p && Hide != g) {
            break;
        }
    }
    qDebug()<<"P"<<p;
    qDebug()<<"G"<<g;
    qDebug()<<"Hide"<<Hide;

    inOpen = openKey();
    qDebug()<<"Open key = "<<inOpen<<": "<< g<<"^"<<Hide<<"%"<<p;

    inKey = key(inOpen, Hide);

    if(inKey == 0){
        qDebug() << "Err: Key is 0, please reset number";
    }
}
