// GoBot

#include "bitboard.h"



int main(int nb_args, char* args[]) {

    /*
    lbit testBit(4);
    lbit testBit2(12);
    cout << testBit << endl;
    cout << testBit2 << endl;
    lbit res = testBit & testBit2;
    cout << (testBit & testBit2).toString() << endl;
    cout << (testBit | testBit2).toString() << endl;
    cout << (testBit ^ testBit2).toString() << endl;
    cout << (~testBit).toString() << endl;
    */

    bitboard atest;
    cout << atest.toString() << endl;
    atest.play(lbit(15));
    cout << atest.toString() << endl;

    return 1;
}
