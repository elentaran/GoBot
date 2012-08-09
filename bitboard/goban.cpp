
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





int Goban::moveToInt(string move) {
    if (move == "PASS" || move == "pass" || move == "Pass")
        return PASSMOVE;  

    return 1;
}

string Goban::intToMove(int location) {
    if (location == PASSMOVE) {
        return "PASS";
    }
    if (location == RESIGN) {
        return "RESIGN";
    }

    return "PASS";
}


int Goban::playerToInt(string player) {
    char* token = (char *)player.c_str();
    if (token[0] == 'B' or token[0] == 'b')
        return BLACK;
    if (token[0] == 'W' or token[0] == 'w')
        return WHITE;

    cerr << "problem with player name" << endl;
    assert(0);
}


string Goban::intToPlayer(int player) {
    if (player == 1)
        return "B";
    if (player == 0)
        return "W";
    cerr << "player non existant"<< endl;
    assert(0);
}


void Goban::show(){
    cerr << "coucou" << endl;

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


void Goban::play(int player, int move) {


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


// All the stones are considered to be alive
// Score is from the point of view of BLACK
float Goban::score () {

    return 0;
}



vector<int> Goban::getLegalLocations() {

    vector<int> res;

    return res;

}

