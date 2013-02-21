#include "lbit.h"

#define DEFAULT_KOMI 6.5

#define PASSMOVE -1

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
        lbit _surroudings;
        int _num;

        group(lbit stones, lbit lib, lbit surroudings, int num);
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
        float _komi;

    public:
        bitboard();
        int init();
        int initEdges();
        int initDirection();
        
        void setKomi(float komi);
        int moveToInt(string move); 
        int playerToInt(string player); 

        bool isLegal(lbit move);
        int play(int moveInd, int nextPlayer=-1);
        lbit getLib(int moveInd); 
        lbit getSurrounding(int moveInd); 
        int createGroup(lbit move);
        int connectGroup(int num1, int num2); 
        int removeLib(int num1, int num2); 
        lbit legalMoves();
        int score();
        int monteCarlo();
        string toString();
        void showBoard();

};

