
#include "bitboard.h"


BitBoard::BitBoard() {
    _size = 9;
    _bigsize = _size + 2;
    _bigArea = _bigsize * _bigsize; 
    _komi = DEFAULT_KOMI;
    _nbPass = 0;
    clear();
}

BitBoard::BitBoard(int size) {
    _size = size;
    _bigsize = _size + 2;
    _bigArea = _bigsize * _bigsize; 
    _komi = DEFAULT_KOMI;
    clear();
}



void BitBoard::setSize(int size) {
    _size = size;
    _bigsize = _size + 2;
    _bigArea =  _bigsize * _bigsize; 
    clear();
}

int BitBoard::getSize() {
    return _size;
}

int BitBoard::moveToInt(string move) {
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

    return (j+1) * _bigsize + (i+1);
}

string BitBoard::intToMove(int location) {
    if (location == PASSMOVE) {
        return "PASS";
    }
    if (location == RESIGN) {
        return "RESIGN";
    }

    int i=0;
    int j=0;
    char tmp[10];
    snprintf(tmp,8,"%c%i",'A'+i-1,j);
    if (tmp[0] >= 'I') tmp[0]++;
    tmp[9]=0;

    string res = tmp;
    return res;
}


int BitBoard::playerToInt(string player) {
    char* token = (char *)player.c_str();
    if (token[0] == 'B' or token[0] == 'b')
        return BLACK;
    if (token[0] == 'W' or token[0] == 'w')
        return WHITE;

    cerr << "problem with player name" << endl;
    assert(0);
}


string BitBoard::intToPlayer(int player) {
    if (player == 1)
        return "B";
    if (player == 0)
        return "W";
    cerr << "player non existant"<< endl;
    assert(0);
}


void BitBoard::show(){
    cerr << "coucou" << endl;

    for (int j=0; j<_bigsize; j++) {
        for (int i=0; i<_bigsize; i++) {
        }
        cerr << endl;
    }
    cerr << endl;

}

void BitBoard::clear(){
    setKomi (DEFAULT_KOMI);
    _ko=PASSMOVE;
    lastPlayedMove=PASSMOVE;
    _isBlackTurn=1;
    _nbPass=0;

}



void BitBoard::setKomi(float komi){
    _komi = komi;
}

void BitBoard::setTimeLeft(int timeLeft){
    _timeLeft = timeLeft;
}

void BitBoard::set_playerTurn(int player) {
    _isBlackTurn = player;
}

int BitBoard::get_playerTurn() {
    return _isBlackTurn;
}


bool BitBoard::is_legal(int location) {

    return true;
}

bool BitBoard::is_suicide(int v) {
    return true;
}


void BitBoard::play(int player, int move) {


}

void BitBoard::processNewNeighborhood(int newLocation, int oldLocation) {

}



void BitBoard::removeChain (int location) {

}


void BitBoard::placeStone (int location) {

}


void BitBoard::removeStone (int location) {

}

void BitBoard::mergeChains (int baseChainLocation, int newChainLocation) {

}

int BitBoard::getFreeNeighborhood(int location) {

    return 0;
}

bool BitBoard::isOneLibertyOfChain(int location, int localChainId) {
    return false;
}


// All the stones are considered to be alive
// Score is from the point of view of BLACK
float BitBoard::score () {

    return 0;
}

int* BitBoard::getFreeLocations() {
    return NULL;
}

int BitBoard::getNbFreeLocations() {
    return NULL;
}

vector<int> BitBoard::getLegalLocations() {

    vector<int> res;

    return res;

}



bool BitBoard::isTerminal() {
    return (_nbPass == 2);
}

int BitBoard::getNbPass() {
    return _nbPass;
}

