#include "lbit.h"


lbit::lbit() {
    for (int i=0;i<NBINT;i++) 
        _val[i] = 0;
    _indice = NOBIT;
}

lbit::lbit(int indice) {
    for (int i=0;i<NBINT;i++) 
        _val[i] = 0;
    _val[indice/INTBIT]= (0x1 << (indice%INTBIT));
    _indice = indice;
}

lbit::lbit(int val[NBINT]) {
    for (int i=0;i<NBINT;i++) 
        _val[i] = val[i];
    _indice = MULBIT;
}

int lbit::getInd() {
    return _indice;
}

string lbit::toString() {
    stringstream res;
    for (int i=0;i<NBINT;i++) {
        int a=_val[i];
        for (int j=0; j<INTBIT; j++) {
            res << (a & 0x1);
            a = a >> 1;
            if (((i*INTBIT+j)%LBOARDSIZE) == (LBOARDSIZE-1))
                res << endl;
            if ((i*INTBIT+j) >= (NBCASES-1))
                return res.str();
        }
    }
    return res.str();
}


lbit operator | (const lbit lbit1, const lbit lbit2) {
    int res[NBINT];
    for (int i=0; i<NBINT; i++) {
        res[i] = lbit1._val[i] | lbit2._val[i];
    }
    return (lbit(res));
}

lbit operator ^ (const lbit lbit1, const lbit lbit2) {
    int res[NBINT];
    for (int i=0; i<NBINT; i++) {
        res[i] = lbit1._val[i] ^ lbit2._val[i];
    }
    return (lbit(res));
}

lbit operator & (const lbit lbit1, const lbit lbit2) {
    int res[NBINT];
    for (int i=0; i<NBINT; i++) {
        res[i] = lbit1._val[i] & lbit2._val[i];
    }
    return (lbit(res));
}

lbit operator ~ (const lbit lbit1) {
    int res[NBINT];
    for (int i=0; i<NBINT; i++) {
        res[i] = ~ lbit1._val[i];
    }
    return (lbit(res));
}

int lbit::operator [](int indice) {
    return ((_val[indice/INTBIT] >> (indice%INTBIT)) & 0x1);
}

bool lbit::isZero() {
    bool res=true;
    for (int i=0; i<NBINT; i++) {
        if (_val[i] != 0)
            res=false;
    }
    return res;
}

ostream& operator<<(ostream& out, lbit& r)
{
    return out<< r.toString();
}

