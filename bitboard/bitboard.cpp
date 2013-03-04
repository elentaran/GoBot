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

    _komi = DEFAULT_KOMI;

    _ko[BLACK] = lbit();
    _ko[WHITE] = lbit();

    _nbPass = 0;

    return SUCCESS;
}

int bitboard::initEdges() {

    _stones[EDGE] = lbit();
    for (int i=0; i<NBINT*INTBIT; i++) {
        if (i/LBOARDSIZE == 0 || i/LBOARDSIZE == (LBOARDSIZE-1) || i%LBOARDSIZE == 0 || i%LBOARDSIZE == (LBOARDSIZE-1) || i>=NBCASES) {
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

    // the board is vertically inversed
    return (LBOARDSIZE -2 -j) * LBOARDSIZE + (i+1);
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

string bitboard::moveToString(lbit move) {
    int imove = move.toInt();
    if (imove == PASSMOVE) {
        return "PASS";
    }
    if (imove == RESIGN) {
        return "RESIGN";
    }

    int i=imove%LBOARDSIZE; // x coord
    int j= LBOARDSIZE - ((int) imove/LBOARDSIZE) - 1; // y coord (board inversed)
    assert (i>0 && i<LBOARDSIZE);
    assert (j>0 && j<LBOARDSIZE);
    char tmp[10];
    snprintf(tmp,8,"%c%i",'A'+i-1,j);
    if (tmp[0] >= 'I') tmp[0]++;
    tmp[9]=0;

    string res = tmp;
    return res;

}

string bitboard::genmove(int nextPlayer) {
    if (nextPlayer >= 0) _nextPlayer = nextPlayer;

    lbit legal = legalMoves(_nextPlayer); 

    lbit move;
    if (legal.isZero()) {
        move = lbit(PASSMOVE);
    }else{
        move = legal.getRand();
    }
    play(move, _nextPlayer);
    return moveToString(move);
}

int bitboard::play(lbit move, int nextPlayer) {


    if (nextPlayer >= 0) _nextPlayer = nextPlayer;

    if (move.toInt() == PASSMOVE) {
        _nbPass++;
    } else {

        _nbPass = 0;

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

    }

    // remove ko
    _ko[_nextPlayer] = lbit();
    
    // update _nextPlayer
    _nextPlayer = !_nextPlayer;

}

int bitboard::createGroup(lbit move) {

    lbit lib = getLib(move);
    lbit surroundings = getSurrounding(move);
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
    _groups[_nextPlayer][numOther] = _groups[_nextPlayer][(_nbGroup[_nextPlayer]-1)];
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
        lbit temp;
        for (int i=0; i<_nbGroup[_nextPlayer]; i++) {
            temp = _groups[_nextPlayer][i]._surroudings & _groups[!_nextPlayer][num1]._stones;  
            if (!temp.isZero()) {
                _groups[_nextPlayer][i]._lib = _groups[_nextPlayer][i]._lib | temp;
            }
        }

        // update ko
        if (_groups[!_nextPlayer][num1]._stones.popcount() == 1 && _groups[_nextPlayer][num2]._stones.popcount() == 1)
            _ko[!_nextPlayer] = _groups[!_nextPlayer][num1]._stones;

        // remove the group
        _stones[!_nextPlayer] = _stones[!_nextPlayer] & ~_groups[!_nextPlayer][num1]._stones;
        _groups[!_nextPlayer][num1] = _groups[!_nextPlayer][(_nbGroup[!_nextPlayer]-1)];
        _nbGroup[!_nextPlayer]--;
    }

    return 1;
}


// compute the legal moves
lbit bitboard::legalMoves(int player) {
    lbit legal = ~_stones[EDGE] &
                 ~_stones[BLACK] &
                 ~_stones[WHITE];

    // one point suicide
    lbit suicide = ((legal << 1) |
                   (legal >> 1) |
                   (legal << LBOARDSIZE) |
                   (legal >> LBOARDSIZE)) &
                    legal;
    legal = suicide;
                
    // suicide
    lbit legalLib = lbit();
    for (int i=0; i<_nbGroup[player]; i++) {
        if (_groups[player][i]._lib.popcount() == 1 && 
            getLib(_groups[player][i]._lib).isZero()) {
            legal = legal & ~(_groups[player][i]._lib);
         } else
            legalLib = legalLib | _groups[player][i]._lib;
    }
    legal = legal | legalLib;

    // capture
    for (int i=0; i<_nbGroup[!player]; i++) {
        if (_groups[!player][i]._lib.popcount() ==1)
            legal = legal | _groups[!player][i]._lib;
    }

    // ko
    legal = legal & ~_ko[player];
    
    return legal;
}

lbit bitboard::getLib(lbit move) {
    lbit lib = getSurrounding(move);
    lib = lib & (~_stones[BLACK]);
    lib = lib & (~_stones[WHITE]);
    return lib;
}

lbit bitboard::getSurrounding(lbit move) {
    lbit lib=lbit();
    lib = (((move << 1)
        | (move >> 1)
        | (move << LBOARDSIZE)
        | (move >> LBOARDSIZE))
        & (~move))
        & (~_stones[EDGE]);
    return lib;
}

bool bitboard::isSuicide(lbit move, int player) {

    
    return false;
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
    cerr << "black group" << endl;
    for (int i=0; i<_nbGroup[BLACK]; i++) {
        cerr << "num: " << i << endl;
        cerr << "stones: " << endl;
        cerr << _groups[BLACK][i]._stones.toString() << endl;
        cerr << "libs: " << endl;
        cerr << _groups[BLACK][i]._lib.toString() << endl;
        cerr << endl;
    }
//    cerr << "white group" << endl;
//    for (int i=0; i<_nbGroup[WHITE]; i++) {
//        cerr << "num: " << i << endl;
//        cerr << "stones: " << endl;
//        cerr << _groups[WHITE][i]._stones.toString() << endl;
//        cerr << "libs: " << endl;
//        cerr << _groups[WHITE][i]._lib.toString() << endl;
//        cerr << endl;
//    }
//   
    cerr << "legal Black" << endl;
    cerr << legalMoves(BLACK).toString() << endl;
    cerr << "legal White" << endl;
    cerr << legalMoves(WHITE).toString() << endl;
    cerr << endl;
}

group::group(lbit stones, lbit lib, lbit surroudings, int num) {
    _stones = stones;
    _lib = lib;
    _surroudings = surroudings;
    _num = num;
}


