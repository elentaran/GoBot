
#include "goban.h"


Goban::Goban() {
    _size = 9;
    _bigsize = _size + 2;
    _bigArea = _bigsize * _bigsize; 
    _komi = DEFAULT_KOMI;
    _nbPass = 0;
    clear();
}

Goban::Goban(int size) {
    _size = size;
    _bigsize = _size + 2;
    _bigArea = _bigsize * _bigsize; 
    _komi = DEFAULT_KOMI;
    clear();
}



void Goban::setSize(int size) {
    _size = size;
    _bigsize = _size + 2;
    _bigArea =  _bigsize * _bigsize; 
    clear();
}

int Goban::getSize() {
    return _size;
}

int Goban::moveToInt(string move) {
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

string Goban::intToMove(int location) {
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

    for (int j=0; j<_bigsize; j++) {
        for (int i=0; i<_bigsize; i++) {
        }
        cerr << endl;
    }
    cerr << endl;

}

void Goban::clear(){
    setKomi (DEFAULT_KOMI);
    _ko=PASSMOVE;
    lastPlayedMove=PASSMOVE;
    _isBlackTurn=1;
    _nbPass=0;

}



void Goban::setKomi(float komi){
    _komi = komi;
}

void Goban::setTimeLeft(int timeLeft){
    _timeLeft = timeLeft;
}

void Goban::set_playerTurn(int player) {
    _isBlackTurn = player;
}

int Goban::get_playerTurn() {
    return _isBlackTurn;
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

int* Goban::getFreeLocations() {
    return NULL;
}

int Goban::getNbFreeLocations() {
    return 0;
}

vector<int> Goban::getLegalLocations() {

    vector<int> res;

    return res;

}



bool Goban::isTerminal() {
    return (_nbPass == 2);
}

int Goban::getNbPass() {
    return _nbPass;
}

