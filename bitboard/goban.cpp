
#include "goban.h"


Goban::Goban() {
    _size = 9;
    _komi = DEFAULT_KOMI;
    _nbPass = 0;
    clear();
}

Goban::Goban(int size) {
    _size = size;
    _komi = DEFAULT_KOMI;
    clear();
}



void Goban::play(string player, string move) {


}


vector<int> Goban::getLegalLocations() {

    vector<int> res;
    return res;
}

void Goban::show(){
    cerr << "coucou" << endl;
}

// All the stones are considered to be alive
// Score is from the point of view of BLACK
float Goban::score () {

    return 0;
}


void Goban::clear(){
    setKomi (DEFAULT_KOMI);
    _ko=PASSMOVE;
    _lastPlayedMove=PASSMOVE;
    _isBlackTurn=1;
    _nbPass=0;

}


bool Goban::is_legal(int location) {

    return true;
}

bool Goban::is_suicide(int v) {
    return true;
}


void Goban::processNewNeighborhood(int newLocation, int oldLocation) {

}



void Goban::removeChain (int location) {

}


void Goban::placeStone (int location) {

}


void Goban::removeStone (int location) {

}

void Goban::mergeChains (int baseChainLocation, int newChainLocation) {

}

int Goban::getFreeNeighborhood(int location) {
    return 0;
}

bool Goban::isOneLibertyOfChain(int location, int localChainId) {
    return false;
}

LBIT::LBIT() {
    _val = 0;
}

LBIT::LBIT(int val) {
    _val = val;
}

void LBIT::show() {
    cerr << _val << endl;
    for (int i=0; i < 65; i++) {
        cerr << (_val >> i)%2 << " ";
    } 
    cerr << endl;

}
