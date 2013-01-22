#include "bitboard.h"


bitboard::bitboard() {
    init();
}

int bitboard::init() {

    cout << "init" << endl;
    _nextPlayer=BLACK;
    _nbGroup[WHITE]=0;
    _nbGroup[BLACK]=0;
    _stones[WHITE] = lbit();
    _stones[BLACK] = lbit();
    initEdges();
    initDirection();
    _legalMoves = ~_stones[EDGE];

    return SUCCESS;
}

int bitboard::initEdges() {

    _stones[EDGE] = lbit();
    for (int i=0; i<NBCASES; i++) {
        if (i/LBOARDSIZE == 0 || i/LBOARDSIZE == (LBOARDSIZE-1) || i%LBOARDSIZE == 0 || i%LBOARDSIZE == (LBOARDSIZE-1)) {
            lbit move(i);
            _stones[EDGE] = _stones[EDGE] | move;
        }
    }

    return SUCCESS;
}

int bitboard::initDirection() {
    _direction[UP] = -LBOARDSIZE;
    _direction[RIGHT] = 1;
    _direction[DOWN] = LBOARDSIZE;
    _direction[LEFT] = -1;
}


int bitboard::play(lbit move, int nextPlayer) {


    if (nextPlayer >= 0) _nextPlayer = nextPlayer;

    // add stone on the board
    _stones[_nextPlayer] = _stones[_nextPlayer] | move;
    
    // create group
    int numGroup1 = createGroup(move);

    // connect group
    // TODO problem join with itself and numgroup change in the middle of for and numgroup has to change if last
    // improvement idea: lib AND blackstones
    // -> isnull: nothing to do
    // -> !isnull: get group under the bits, connnect them
    for (int i=0; i<_nbGroup[_nextPlayer]; i++) {
        if (!((_groups[_nextPlayer][numGroup1])._lib & _groups[_nextPlayer][i]._stones).isZero()) {
            connectGroup(numGroup1,i);
        }
    }
    
    

    // update libertes and capture groups


    // update legal moves

    // update _nextPlayer
    _nextPlayer = !_nextPlayer;
    
}

int bitboard::createGroup(lbit move) {

    lbit lib = getLib(move);
    int numGroup = _nbGroup[_nextPlayer];
    group myGroup = group(move,lib,numGroup);
    _groups[_nextPlayer][numGroup] = myGroup;
    _nbGroup[_nextPlayer]++;

    return (numGroup);
}

int bitboard::connectGroup(int num1, int num2) {
}


lbit bitboard::legalMoves() {
}

lbit bitboard::getLib(lbit move) {
    lbit lib=lbit();
    lbit dir;
    for (int i=0; i<4; i++) {
        dir = lbit(move.getInd()+_direction[i]);
        lib = (lib | dir);
    }
    lib = lib & (~_stones[EDGE]);
    lib = lib & (~_stones[BLACK]);
    lib = lib & (~_stones[WHITE]);

    return lib;
}

bool bitboard::isLegal(lbit move) {
}

int bitboard::score() {
}

int bitboard::monteCarlo() {
}

string bitboard::toString() {


    stringstream res;
    for (int i=0;i<NBCASES;i++) {
        if (_stones[EDGE][i] == 1) {
            res << EDGE;
        } else if (_stones[WHITE][i] == 1) {
            res << WHITE;
        } else if (_stones[BLACK][i] == 1) {
            res << BLACK;
        } else {
            res << EMPTY;
        }
        if (i%LBOARDSIZE == (LBOARDSIZE-1)) {
            res << endl;
        }
    }
    return res.str();
}

void bitboard::showBoard() {
    cout << "board:" << endl;
    cout << toString() << endl;
    cout << "black group" << endl;
    for (int i=0; i<_nbGroup[BLACK]; i++) {
        cout << "num: " << i << endl;
        cout << _groups[BLACK][i]._stones.toString() << endl;
        cout << _groups[BLACK][i]._lib.toString() << endl;
        cout << endl;
    }
    cout << "white group" << endl;
    for (int i=0; i<_nbGroup[WHITE]; i++) {
        cout << "num: " << i << endl;
        cout << _groups[WHITE][i]._stones.toString() << endl;
        cout << _groups[WHITE][i]._lib.toString() << endl;
        cout << endl;
    }
}

group::group(lbit stones, lbit lib, int num) {
    _stones = stones;
    _lib = lib;
    _num = num;
}


