
#include <iostream>
#include <sstream>
#include <climits>
#include <cassert>
#include <cstdlib>
#include <stdio.h>

using namespace std;

#define BOARDSIZE 9
#define MAXGROUP (BOARDSIZE*BOARDSIZE/2)
#define LBOARDSIZE (BOARDSIZE+2)
#define NBCASES (LBOARDSIZE*LBOARDSIZE)
#define INTBIT (sizeof(uint)*CHAR_BIT)
#define NBINT (((NBCASES+2)/INTBIT)+1) // +2: one bit for passmove, one bit for resign
//const int NBINT = ((NBCASES/(sizeof(int)*CHAR_BIT))+1);
//#define NBLL ceil((float)NBCASES/(sizeof(long long)*CHAR_BIT))

#define PASSMOVE NBCASES+1
#define RESIGN   NBCASES+2

class lbit {
    private:
        uint _val[NBINT];

    public:
        lbit();
        lbit(uint val[NBINT]);
        lbit(int val);
        string toString();
        string toStringBit();
        friend lbit operator | (const lbit lbit1, const lbit lbit2);
        friend lbit operator ^ (const lbit lbit1, const lbit lbit2);
        friend lbit operator & (const lbit lbit1, const lbit lbit2);
        friend lbit operator ~ (const lbit lbit1);
        friend lbit operator << (const lbit lbit1, int nbShift);
        friend lbit operator >> (const lbit lbit1, int nbShift);
        int operator [](int indice);

        bool isZero();
        int popcount();

        lbit dec();
        lbit getRand();

        int toInt();

};

ostream& operator<<(ostream& out, lbit& r);
