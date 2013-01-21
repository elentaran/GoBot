
#include <iostream>
#include <sstream>
#include <climits>

using namespace std;

#define BOARDSIZE 9
#define MAXGROUP (BOARDSIZE*BOARDSIZE/2)
#define LBOARDSIZE (BOARDSIZE+2)
#define NBCASES (LBOARDSIZE*LBOARDSIZE)
#define INTBIT (sizeof(int)*CHAR_BIT)
#define NBINT ((NBCASES/INTBIT)+1)
//const int NBINT = ((NBCASES/(sizeof(int)*CHAR_BIT))+1);
//#define NBLL ceil((float)NBCASES/(sizeof(long long)*CHAR_BIT))

#define NOBIT   -1
#define MULBIT  -2

class lbit {
    private:
        int _val[NBINT];
        int _indice;

    public:
        lbit();
        lbit(int val[NBINT]);
        lbit(int val);
        int getInd();
        string toString();
        friend lbit operator | (const lbit lbit1, const lbit lbit2);
        friend lbit operator ^ (const lbit lbit1, const lbit lbit2);
        friend lbit operator & (const lbit lbit1, const lbit lbit2);
        friend lbit operator ~ (const lbit lbit1);
        int operator [](int indice);
        bool isZero();

};

ostream& operator<<(ostream& out, lbit& r);
