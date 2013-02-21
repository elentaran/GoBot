// GoBot

//#include "bitboard.h"
#include "GTPengine.h"

int testlbit() {
    lbit testBit(4);
    lbit testBit2(12);
    cout << testBit << endl;
    cout << testBit2 << endl;
    lbit res = testBit & testBit2;
    cout << (testBit & testBit2).toString() << endl;
    cout << (testBit | testBit2).toString() << endl;
    cout << (testBit ^ testBit2).toString() << endl;
    cout << (~testBit).toString() << endl;
    return 1;
}

int testBitboardCreate() {
    bitboard atest;
    cout << atest.toString() << endl;
    atest.showBoard();
    return 1;
}

int testBitboardConnect1() {

    bitboard atest;
    atest.showBoard();
    atest.play(15,BLACK);
    atest.showBoard();
    atest.play(16,BLACK);
    atest.showBoard();
    atest.play(17,BLACK);
    atest.showBoard();
    atest.play(19,BLACK);
    atest.showBoard();
    atest.play(18,BLACK);
    atest.showBoard();
    return 1;
}

int testBitboardConnect2() {

    bitboard atest;
    atest.play(26,BLACK);
    atest.play(28,BLACK);
    atest.play(16,BLACK);
    atest.play(38,WHITE);
    atest.showBoard();
    atest.play(27,BLACK);
    atest.showBoard();
    return 1;
}

int testBitboardCapture() {
    bitboard atest;
    atest.play(26,BLACK);
    atest.play(28,BLACK);
    atest.play(16,BLACK);
    atest.play(27,WHITE);
    atest.showBoard();
    atest.play(38,BLACK);
    atest.showBoard();
    return 1;
}

int testBitboardCapture2() {
    bitboard atest;
    atest.play(24,BLACK);
    atest.play(25,BLACK);
    atest.play(27,BLACK);
    atest.play(26,BLACK);
    atest.play(28,BLACK);
    atest.play(29,BLACK);
    atest.play(30,BLACK);
    atest.play(46,BLACK);
    atest.play(47,BLACK);
    atest.play(48,BLACK);
    atest.play(49,BLACK);
    atest.play(50,BLACK);
    atest.play(51,BLACK);
    atest.play(52,BLACK);
    atest.play(35,BLACK);
    atest.play(41,BLACK);

    atest.play(36,WHITE);
    atest.play(37,WHITE);

    atest.play(39,WHITE);
    atest.play(40,WHITE);
    atest.showBoard();


    atest.play(38,BLACK);
    atest.showBoard();
    return 1;
}

int main(int nb_args, char* args[]) {


    // testlbit();

    // testBitboardCreate();
    
    //testBitboardConnect1();
    //testBitboardConnect2();

    //testBitboardCapture();
    //testBitboardCapture2();
    GTPengine global_GTPengine(nb_args,args);
    global_GTPengine.launch();
    return 1;
}


