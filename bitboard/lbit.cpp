#include "lbit.h"


lbit::lbit() {
    for (int i=0;i<NBINT;i++) 
        _val[i] = 0;
}

lbit::lbit(int indice) {
    for (int i=0;i<NBINT;i++) 
        _val[i] = 0;
    _val[indice/INTBIT]= (0x1 << (indice%INTBIT));
}

lbit::lbit(uint val[NBINT]) {
    for (int i=0;i<NBINT;i++) 
        _val[i] = val[i];
}

string lbit::toStringBit() {
    stringstream res;
    for (int i=0;i<NBINT;i++) {
        int a=_val[i];
        for (int j=0; j<INTBIT; j++) {
            res << (a & 0x1);
            a = a >> 1;
        }
        res << endl;
    }
    return res.str();
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
    uint res[NBINT];
    for (int i=0; i<NBINT; i++) {
        res[i] = lbit1._val[i] | lbit2._val[i];
    }
    return (lbit(res));
}

lbit operator ^ (const lbit lbit1, const lbit lbit2) {
    uint res[NBINT];
    for (int i=0; i<NBINT; i++) {
        res[i] = lbit1._val[i] ^ lbit2._val[i];
    }
    return (lbit(res));
}

lbit operator & (const lbit lbit1, const lbit lbit2) {
    uint res[NBINT];
    for (int i=0; i<NBINT; i++) {
        res[i] = lbit1._val[i] & lbit2._val[i];
    }
    return (lbit(res));
}

lbit operator ~ (const lbit lbit1) {
    uint res[NBINT];
    for (int i=0; i<NBINT; i++) {
        res[i] = ~ lbit1._val[i];
    }
    return (lbit(res));
}

int lbit::operator [](int indice) {
    return ((_val[indice/INTBIT] >> (indice%INTBIT)) & 0x1);
}

lbit operator << (const lbit lbit1, int nbShift) {
    assert (nbShift < INTBIT); // warning
    uint res[NBINT];
    for (int i=0; i<(NBINT-1); i++) {
        res[i] = (lbit1._val[i] >> nbShift) + (lbit1._val[i+1] << (INTBIT-nbShift));
    }
    res[(NBINT-1)] = lbit1._val[(NBINT-1)] >> nbShift;
    return (lbit(res));
}

lbit operator >> (const lbit lbit1, int nbShift) {
    assert (nbShift < INTBIT); // warning
    uint res[NBINT];
    for (int i=1; i<NBINT; i++) {
        res[i] = (lbit1._val[i] << nbShift) + (lbit1._val[i-1] >> (INTBIT-nbShift));
    }
    res[0] = lbit1._val[0] << nbShift;
    return (lbit(res));
}

bool lbit::isZero() {
    for (int i=0; i<NBINT; i++) {
        if (_val[i] != 0)
            return false;
    }
    return true;
}

int lbit::popcount() {
    int res=0;
    for (int i=0; i<NBINT; i++) {
        res+=__builtin_popcount(_val[i]); // return the number of 1 bits in the int
    }
    return res;
}

// decrement the lbit
lbit lbit::dec() {
    uint res[NBINT];
    for (int i=0; i<NBINT; i++) {
        res[i]=_val[i];
    }
    for (int i=0; i<NBINT; i++) {
        if (res[i] > 0) {
            res[i]--;
            return lbit(res);
        } else {
            res[i] = -1;
        }
    }
    return lbit(res);
}

lbit lbit::getRand() {
    int nbBit = popcount();
    int index = rand()%nbBit;
    //cerr << index << "/" << nbBit << endl;
    lbit res=lbit(_val);
    for (int i=0;i<index;i++)
        res = res & res.dec();
    res = res & ~(res.dec());
    return res;
}

ostream& operator<<(ostream& out, lbit& r)
{
    return out<< r.toString();
}

int lbit::toInt() {
    assert (popcount() == 1);
    int i=0;
    int index=__builtin_ffs(_val[i]);
    while (index == 0) {
        i++;
        index=__builtin_ffs(_val[i]); // return the index of the first bit to 1
    }
    return (i*INTBIT+index-1);
}
