#include "lbit.h"

#define DEFAULT_KOMI 6.5

#define BLACK 0
#define WHITE 1
#define EMPTY 2
#define EDGE  3

#define FAIL    -1
#define SUCCESS 1

#define UP      0
#define RIGHT   1
#define DOWN    2
#define LEFT    3


class group {

    public:
        lbit _stones;
        lbit _lib;
        lbit _surroudings;
        int _num;

        group(lbit stones, lbit lib, lbit surroudings, int num);
        group() {};


};

class bitboard {

    private:
        lbit _stones[4];
        int _nextPlayer;
        group _groups[2][MAXGROUP];
        int _nbGroup[2];
        int _direction[4];
        float _komi;
        lbit _ko[2];
        int _nbPass;

    public:
        bitboard();
        int init();
        int initEdges();
        int initDirection();
        
        void setKomi(float komi);
        int moveToInt(string move); 
        int playerToInt(string player); 
        string moveToString(lbit move);

        bool isLegal(lbit move);
        bool isSuicide(lbit move, int player);
        int play(lbit move, int nextPlayer=-1);
        string genmove(int nextPlayer=-1);
        lbit getLib(lbit move); 
        lbit getSurrounding(lbit move); 
        int createGroup(lbit move);
        int connectGroup(int num1, int num2); 
        int removeLib(int num1, int num2); 
        lbit legalMoves(int player);
        int score();
        int monteCarlo();
        string toString();
        void showBoard();

};

