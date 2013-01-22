#include "lbit.h"


#define BLACK 0
#define WHITE 1
#define EMPTY 2
#define EDGE  3

#define FAIL  -1
#define SUCCESS 1

#define UP      0
#define RIGHT   1
#define DOWN    2
#define LEFT    3

class group {

    public:
        lbit _stones;
        lbit _lib;
        int _num;

        group(lbit stones, lbit lib, int num);
        group() {};


};

class bitboard {

    private:
        lbit _stones[4];
        lbit _legalMoves;
        int _nextPlayer;
        group _groups[2][MAXGROUP];
        int _nbGroup[2];
        int _direction[4];

    public:
        bitboard();
        int init();
        int initEdges();
        int initDirection();
        bool isLegal(lbit move);
        int play(lbit move, int nextPlayer=-1);
        lbit getLib(lbit move); 
        int createGroup(lbit move);
        int connectGroup(int num1, int num2); 
        lbit legalMoves();
        int score();
        int monteCarlo();
        string toString();
        void showBoard();

};

