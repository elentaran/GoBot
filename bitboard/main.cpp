// GoBot

//#include "bitboard.h"
#include "GTPengine.h"

int testlbit() {
    lbit testBit(36);
    lbit testBit2(12);
    cout << testBit << endl;
    cout << testBit2 << endl;
    lbit res = testBit & testBit2;
    cout << (testBit & testBit2).toString() << endl;
    cout << (testBit | testBit2).toString() << endl;
    cout << (testBit ^ testBit2).toString() << endl;
    cout << (~testBit).toString() << endl;
    cout << (testBit.popcount()) << endl;
    cout << (~testBit).popcount() << endl;
    testBit = ~testBit;
    cout << testBit << endl;
    cout << (testBit << 4).toString() << endl;
    cout << (testBit << 22).toString() << endl;
    cout << ((testBit >> 22) >> 22).toString() << endl;
    testBit = ~testBit;
    cout << testBit << endl;
    cout << "dec" << endl;
    cout << (testBit.dec()).toString() << endl;
    testBit = ~testBit;
    cout << testBit << endl;
    cout << "rand" << endl;
    cout << (testBit.getRand()).toString() << endl;
    cout << (testBit.getRand().toInt()) << endl;
    testBit = ~testBit;
    cout << (testBit.toInt()) << endl;
    cout << (testBit2.toInt()) << endl;
    cout << ((new lbit(59))->toInt()) << endl;

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


    //atest.play(38,BLACK);
    //atest.showBoard();
    return 1;
}

int testBitboardKo() {
    bitboard atest;
    atest.play(24,BLACK);
    atest.play(26,BLACK);
    atest.play(14,BLACK);
    atest.play(36,BLACK);

    atest.play(15,WHITE);
    atest.play(27,WHITE);
    atest.play(37,WHITE);
    atest.showBoard();
    atest.play(25,WHITE);
    atest.showBoard();
    return 1;
}

int testBitboardIO() {
    bitboard atest;
    cerr << atest.moveToString(lbit(15)) << endl;

    cerr << atest.moveToInt("A1") << endl;
    cerr << lbit(atest.moveToInt("A1")).toString() << endl;
    cerr << atest.moveToString(lbit(atest.moveToInt("A1"))) << endl;
    cerr << atest.moveToString(lbit(atest.moveToInt("E5"))) << endl;
    return 1;
}

int main(int nb_args, char* args[]) {

    srand(time(0));

    //testlbit();

    // testBitboardCreate();
    
    //testBitboardConnect1();
    //testBitboardConnect2();

    //testBitboardCapture();
    //testBitboardCapture2();

    //testBitboardKo();
    //testBitboardIO();
    
   
    
    GTPengine global_GTPengine(nb_args,args);
    global_GTPengine.launch();
    return 1;
}


