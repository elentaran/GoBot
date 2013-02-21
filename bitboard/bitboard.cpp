#include "bitboard.h"


bitboard::bitboard() {
    init();
}

int bitboard::init() {

    _nextPlayer=BLACK;
    _nbGroup[WHITE]=0;
    _nbGroup[BLACK]=0;
    _stones[WHITE] = lbit();
    _stones[BLACK] = lbit();
    initEdges();
    initDirection();
    _legalMoves = ~_stones[EDGE];

    _komi = DEFAULT_KOMI;

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

void bitboard::setKomi(float komi) {
    _komi = komi;
}

int bitboard::moveToInt(string move) {
    if (move == "PASS" || move == "pass" || move == "Pass")
        return PASSMOVE;  

    int i,j=0;
    char* token = (char *)move.c_str();


    if ('A'<=token[0] && token[0]<='Z') {
        i=(int)(token[0]-(int)'A');
        if ((int)token[0]>=(int)'I') i--;// Be careful! Why there is no 'I' in the GNUGO? Or for all the protocol(I dont think so)?
    } else
        if ('a'<=token[0] && token[0]<='z') {
            i=(int)(token[0]-'a');
            if ((int)token[0]>=(int)'i') i--;
        } else return -2;

    j= (atoi(token+1) - 1);


    return (j+1) * LBOARDSIZE + (i+1);
}

int bitboard::playerToInt(string player) {
    char* token = (char *)player.c_str();
    if (token[0] == 'B' or token[0] == 'b')
        return BLACK;
    if (token[0] == 'W' or token[0] == 'w')
        return WHITE;

    cerr << "problem with player name" << endl;
    assert(0);
}

int bitboard::play(int moveInd, int nextPlayer) {

    lbit move = lbit(moveInd);

    if (nextPlayer >= 0) _nextPlayer = nextPlayer;

    // add stone on the board
    _stones[_nextPlayer] = _stones[_nextPlayer] | move;
    
    // create group
    int currentNumGroup = createGroup(move);

    // connect groups
    // Rem: we need to go from the last group to the first because connecting two groups will remove one group and can change the number of the last group.
    for (int i=(_nbGroup[_nextPlayer]-1); i>=0; i--) {
        if (!((_groups[_nextPlayer][currentNumGroup])._stones & _groups[_nextPlayer][i]._lib).isZero()) {
            currentNumGroup = connectGroup(currentNumGroup,i);
        }
    }

    // update libertes and capture groups
    // Rem: same as previously
    for (int i=(_nbGroup[!_nextPlayer]-1); i>=0; i--) {
        if (!((_groups[_nextPlayer][currentNumGroup])._stones & _groups[!_nextPlayer][i]._lib).isZero()) {
            removeLib(i,currentNumGroup);
        }
    }



    // update legal moves

    // update _nextPlayer
    _nextPlayer = !_nextPlayer;

}

int bitboard::createGroup(lbit move) {

    lbit lib = getLib(move.getInd());
    lbit surroundings = getSurrounding(move.getInd());
    int numGroup = _nbGroup[_nextPlayer];
    group myGroup = group(move,lib,surroundings,numGroup);
    _groups[_nextPlayer][numGroup] = myGroup;
    _nbGroup[_nextPlayer]++;

    return (numGroup);
}

int bitboard::connectGroup(int num1, int num2) {
    int numRes = num1;
    int numOther = num2;
    if (num2 < num1) {
        numRes = num2;
        numOther = num1;
    }
    // connect the stones
    _groups[_nextPlayer][numRes]._stones = _groups[_nextPlayer][numRes]._stones | _groups[_nextPlayer][numOther]._stones;
    // connect the libs
    _groups[_nextPlayer][numRes]._lib = _groups[_nextPlayer][numRes]._lib | _groups[_nextPlayer][numOther]._lib;
    _groups[_nextPlayer][numRes]._lib = _groups[_nextPlayer][numRes]._lib & ~_groups[_nextPlayer][numRes]._stones;
    _groups[_nextPlayer][numRes]._lib = _groups[_nextPlayer][numRes]._lib & ~_groups[_nextPlayer][numOther]._stones;
    // connect the surroundings
    _groups[_nextPlayer][numRes]._surroudings = _groups[_nextPlayer][numRes]._surroudings | _groups[_nextPlayer][numOther]._surroudings;
    // remove the group
    _groups[_nextPlayer][numOther] = _groups[_nextPlayer][_nbGroup[_nextPlayer]];
    _nbGroup[_nextPlayer]--;

    return numRes;

}

// num1: group that will have liberties removed
// num2: group that removes liberties
int bitboard::removeLib(int num1, int num2) {

    // update liberties
    _groups[!_nextPlayer][num1]._lib = _groups[!_nextPlayer][num1]._lib & ~_groups[_nextPlayer][num2]._stones;
    
    // kill group
    if (_groups[!_nextPlayer][num1]._lib.isZero()) {
        // add lib to all groups next to it
        for (int i=0; i<_nbGroup[_nextPlayer]; i++) {
            _groups[_nextPlayer][i]._lib = _groups[_nextPlayer][i]._lib | (_groups[_nextPlayer][i]._surroudings & _groups[!_nextPlayer][num1]._stones);
        }

        // remove the group
        _stones[!_nextPlayer] = _stones[!_nextPlayer] & ~_groups[!_nextPlayer][num1]._stones;
        _groups[!_nextPlayer][num1] = _groups[!_nextPlayer][_nbGroup[!_nextPlayer]];
        _nbGroup[!_nextPlayer]--;
    }
    return 1;
}


lbit bitboard::legalMoves() {
}

lbit bitboard::getLib(int moveInd) {
    lbit lib = getSurrounding(moveInd);
    lib = lib & (~_stones[BLACK]);
    lib = lib & (~_stones[WHITE]);
    return lib;
}

lbit bitboard::getSurrounding(int moveInd) {
    lbit lib=lbit();
    lbit dir;
    for (int i=0; i<4; i++) {
        dir = lbit(moveInd+_direction[i]);
        lib = (lib | dir);
    }
    lib = lib & (~_stones[EDGE]);
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
    cerr << "board:" << endl;
    cerr << toString() << endl;
    cerr << "nbGroup black " << _nbGroup[BLACK] << endl;
    cerr << "nbGroup white " << _nbGroup[WHITE] << endl;
  /*  cerr << "black group" << endl;
    for (int i=0; i<_nbGroup[BLACK]; i++) {
        cerr << "num: " << i << endl;
        cerr << "stones: " << endl;
        cerr << _groups[BLACK][i]._stones.toString() << endl;
        cerr << "libs: " << endl;
        cerr << _groups[BLACK][i]._lib.toString() << endl;
        cerr << endl;
    }
    cerr << "white group" << endl;
    for (int i=0; i<_nbGroup[WHITE]; i++) {
        cerr << "num: " << i << endl;
        cerr << "stones: " << endl;
        cerr << _groups[WHITE][i]._stones.toString() << endl;
        cerr << "libs: " << endl;
        cerr << _groups[WHITE][i]._lib.toString() << endl;
        cerr << endl;
    }
    */
    cerr << endl;
}

group::group(lbit stones, lbit lib, lbit surroudings, int num) {
    _stones = stones;
    _lib = lib;
    _surroudings = surroudings;
    _num = num;
}


