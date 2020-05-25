/*Версия от 25.05.2020*/
#include "rsa.h"
#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>
#include <climits>
#include <stack>
#include <random>
#include <fstream>
using namespace std;

int64_t gcd(int64_t a, int64_t b) {
   int64_t t;
   while(1) {
      t = a % b;
      if(t == 0) {
          return b;
      }
      a = b;
      b = t;
   }
}

int64_t mul_inv(int64_t a, int64_t b)
{
    int64_t b0 = b, t, q;
    int64_t x0 = 0, x1 = 1;
    if (b == 1) return 1;
    while (a > 1) {
        q = a / b;
        t = b;
        b = a % b;
        a = t;
        t = x0;
        x0 = x1 - q * x0;
        x1 = t;
    }
    if (x1 < 0) {
        x1 += b0;
    }
    return x1;
}

Encrypt::Encrypt()
{
    p = 1171;
    q = 739;
    n = p * q;
    fi = (p - 1) * (q - 1);
    e = 2;
    int64_t track;
    while(e < fi) {
       track = gcd(e, fi);
       if(track == 1) {
          break;
       } else {
          e++;
       }
    }
//    double d1 = 1/e;
//    d = fmod(d1, fi);

    d = mul_inv(e, fi);
    OpenKey.append(e);
    OpenKey.append(n);
    HideKey.append(d);
    HideKey.append(n);

//    uint64_t m = 9;
//    crip = cript(m, e);
//    uncrip = cript(crip, d, n);
//    double uncrip = pow(crip, d);
//    crip = fmod(crip, n);
//    uncrip = fmod(uncrip, n);

//    qDebug()<<n<<fi<<d<<e<<crip<<uncrip;
}

QVector<int64_t> Encrypt::getOpenKey()
{
    return OpenKey;
}

int64_t Encrypt::getP()
{
    return p;
}

int64_t Encrypt::getQ()
{
    return q;
}

int64_t Encrypt::getN()
{
    return n;
}

int64_t Encrypt::cript(int64_t a, int64_t e, int64_t mod)
{
    int64_t res = 1;
    for(int64_t i(0); i < e; i++){
        res = (a * res) % mod;
    }
    return res;
}

QString Encrypt::cript(QString tempStr, int64_t e, int64_t mod)
{
    qDebug()<<"Str"<<tempStr;
    qDebug()<<"E"<<e;
    qDebug()<<"Mod"<<mod;

    for(int i(0); i < tempStr.length(); i++) {
        if(tempStr[i] == " ") {
            tempStr.remove(i, 1);
            i--;
        }
    }
    qDebug()<<"Next step"<<tempStr;

    QString out;
    qDebug()<<"-------------------------------------------";
    foreach(auto &i, tempStr) {
//        qDebug()<<i.unicode();
        out.append(QString::number(cript(i.unicode(), e, mod)) + ";");
        qDebug()<<"Loop step"<<i<<" == "<<i.unicode();
        qDebug()<<"Loop step"<<out<<": "<<i.unicode()<<"^"<<e<<"%"<<mod;
    }
    qDebug()<<"-------------------------------------------";
    out.remove(out.length()-1, 1);
    qDebug()<<"Next step"<<out;
//    qDebug()<<cript(9, e, mod);
    return out;
}

int64_t Encrypt::decript(int64_t m)
{
    return cript(m, HideKey[0], HideKey[1]);
}

QString Encrypt::decript(QStringList str)
{
    qDebug()<<"Next step"<<str;
    qDebug()<<"Hide key A"<<HideKey;
    QString out;
    qDebug()<<"-------------------------------------------";
    foreach(auto &i, str) {
        out.append(" ");
        out[out.length()-1].unicode() = cript(i.toInt(), HideKey[0], HideKey[1]);
        qDebug()<<"Loop step"<<out[out.length()-1].unicode()<<": "<<i.toInt()<<"^"<<HideKey[0]<<"%"<<HideKey[1];
        qDebug()<<"Loop step"<<out[out.length()-1].unicode()<<" == "<<out[out.length()-1];
    }
    qDebug()<<"-------------------------------------------";
    qDebug()<<"Next step"<<out;
    return out;
}
