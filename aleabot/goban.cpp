
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

void Goban:: init_directions() {
    directions[0] = _bigsize;
    directions[1] = 1;
    directions[2] = -_bigsize;
    directions[3] = -1;
    directions[4] = -1 - _bigsize;
    directions[5] = -1 + _bigsize;
    directions[6] = 1 - _bigsize;
    directions[7] = 1 + _bigsize;
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

    int i=xcoord(location);
    int j=ycoord(location);
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

    string Goban::intToPlayer() {
        if (_isBlackTurn == 1)
            return "B";
        if (_isBlackTurn == 0)
            return "W";
        cerr << "player non existant"<< endl;
        assert(0);
    }


void Goban::show(){
    cerr << "coucou" << endl;

    for (int j=0; j<_bigsize; j++) {
        for (int i=0; i<_bigsize; i++) {
            if ( state [ ( j * (_bigsize)) + i ] == BLACK)
                cerr << "X" << " ";
            if ( state [ ( j * (_bigsize)) + i ] == WHITE)
                cerr << "O" << " ";
            if ( state [ ( j * (_bigsize)) + i ] == EDGE)
                cerr << "#" << " ";
            if ( state [ ( j * (_bigsize)) + i ] == EMPTY)
                cerr << "." << " ";
        }
        cerr << endl;
    }
    cerr << endl;



}

void Goban::clear(){
    setKomi (DEFAULT_KOMI);
    freeLocationsIndex=0;
    freeLocationsLastIndex=0;
    _ko=PASSMOVE;
    for (int i=0;i<_bigArea;i++) {
        state[i]=EDGE;
        chainNext[i]=i;
        chainId[i]=i;
        chainTrueLib[i]=100;
        chainLength[i]=0;
        intersectionUpdated[i]=0;
        intersectionUpdatedIndex=0;
        chainIdUpdatedIndex=0;
        if (isOnBoard(i)) {
            for (int color=0;color<2;color++)
                locationsValue[color][i]=1;
            state[i]=EMPTY;
            freeIndex[i]=freeLocationsIndex; freeLocations[freeLocationsIndex++]=i;
        }
    }

    lastPlayedMove=PASSMOVE;
    _isBlackTurn=1;
    _nbPass=0;

    init_directions();
}

    bool Goban::isOnBoard(int location) {
        if ( xcoord(location) == 0 || xcoord(location) == _size+1 || ycoord(location) == 0 || ycoord(location) == _size+1)
            return false;
        else
            return true;
    }

int Goban::xcoord(int location) {
    return (location%_bigsize);
}

int Goban::ycoord(int location) {
    return (int) (location/_bigsize);
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

bool Goban::is_eye(int location) {


    int templocation;
    for (int i=0;i<4;i++) {
        templocation=location+directions[i];
        if ( (state[templocation]!=_isBlackTurn) && (state[templocation]!=EDGE) ) { // same color
            return false;
        }
    }

    return true;
}

    bool Goban::is_legal(int location) {
        if (state[location] != EMPTY)
            return false;

        if (location == _ko)
            return false;

        if (is_suicide(location)) {
            return false;
        }


        return true;
    }

bool Goban::is_suicide(int v) {
    for (int i=0;i<4;i++) {
        int location=v+directions[i];
        if (state[location]==EMPTY) return false;
        else if (state[location]==_isBlackTurn) { // same color
            if (chainTrueLib[chainId[location]]>1) return false; // saved
        } else if (state[location]==_isBlackTurn^1) {
            if (chainTrueLib[chainId[location]]==1) return false; // capture
        }
    }
    return true;
}


void Goban::play(int player, int move) {

    freeLocationsLastIndex = freeLocationsIndex;

    chainIdUpdatedIndex=chainIdUpdatedIndex>intersectionUpdatedIndex
        ?chainIdUpdatedIndex:intersectionUpdatedIndex;
    chainIdUpdatedIndex++;
    intersectionUpdatedIndex=chainIdUpdatedIndex;

    _isBlackTurn = player;

    int v = move;

    if (v == PASSMOVE) {
        _ko = PASSMOVE;
        _isBlackTurn=!_isBlackTurn;
        _nbPass++;
        assert(_nbPass<3);
        return;
    }

    _nbPass=0;
    placeStone (v);

    for (int i=0;i<4;i++) {
        int location=v+directions[i];
        processNewNeighborhood(location,v);
    }


    for (int i=0;i<4;i++) {
        int location=v+directions[i];
        if ( (state[location]!=_isBlackTurn) && (chainTrueLib[chainId[location]] == 0) ) {
            removeChain (location);
        }
    }

    if (freeLocationsLastIndex == freeLocationsIndex) { // only case of ko
        _ko = freeLocations [freeLocationsIndex - 1]; // then ko
    } else {
        _ko = PASSMOVE;
    }


    _isBlackTurn=!_isBlackTurn;

}

void Goban::processNewNeighborhood(int newLocation, int oldLocation) {
    if (state[newLocation]>=EMPTY) return; // empty or edge

    if ( chainId [newLocation] != chainId [oldLocation] ) {
        uint id=chainId[newLocation];
        if (intersectionUpdated[id]<chainIdUpdatedIndex) {// not already updated by the stone
            intersectionUpdated[id]=chainIdUpdatedIndex;
            chainTrueLib[id] --;

        }
    }



    if (state[newLocation] != _isBlackTurn) { // same color of groups
        return;
    }

    if (chainId [newLocation] == chainId [oldLocation]) return; // already joined

    if (chainLength[chainId [oldLocation]] >= chainLength [chainId [newLocation]])
        mergeChains (oldLocation, newLocation);
    else
        mergeChains (newLocation, oldLocation);

}



void Goban::removeChain (int location) {
    int currentLocation=location;
    int tmpLocation;

    // We remove the stones
    do {
        removeStone (currentLocation);
        currentLocation = chainNext[currentLocation];
    } while (currentLocation != location);

    // We update the liberties of the other chains
    do {
        chainIdUpdatedIndex++;
        for (int i=0;i<4;i++) {
            int tmpLocation2=currentLocation+directions[i];
            if ((state[tmpLocation2]<EMPTY) && intersectionUpdated[chainId[tmpLocation2]]<chainIdUpdatedIndex) {
                chainTrueLib[chainId[tmpLocation2]]++;
                intersectionUpdated[chainId[tmpLocation2]]=chainIdUpdatedIndex;
            }
        }

        tmpLocation = currentLocation;
        currentLocation = chainNext[currentLocation];
        chainNext[tmpLocation] = tmpLocation;
    } while (currentLocation != location);

}


void Goban::placeStone (int location) {
    state[location] = _isBlackTurn;

    freeLocationsIndex--;
    freeIndex [freeLocations [freeLocationsIndex]] = freeIndex [location];
    freeLocations [freeIndex [location]] = freeLocations [freeLocationsIndex];


    chainId [location] = location;
    chainTrueLib[chainId[location]] = getFreeNeighborhood(location);
    chainLength[chainId[location]]=1;
    lastPlayedMove=location;

}


void Goban::removeStone (int location) {
    state[location] = EMPTY;

    freeIndex [location] = freeLocationsIndex;
    freeLocations [freeLocationsIndex++] = location;
    chainId[location]=location;
    chainTrueLib[chainId[location]] = 100;

}

void Goban::mergeChains (int baseChainLocation, int newChainLocation) {
    int currentLocation=newChainLocation;
    int baseId=chainId [baseChainLocation];
    chainLength[baseId]+=chainLength[chainId[newChainLocation]];
    intersectionUpdatedIndex++;
    do {
        if (getFreeNeighborhood(currentLocation)>0) {
            for (int i=0;i<4;i++) {
                int location=currentLocation+directions[i];
                if (state[location]==EMPTY && intersectionUpdated[location]<intersectionUpdatedIndex) {
                    if (!isOneLibertyOfChain(location, baseId))
                        chainTrueLib[baseId]++;
                    intersectionUpdated[location]=intersectionUpdatedIndex;
                }
            }
        }
        chainId [currentLocation] = chainId [baseChainLocation];
        currentLocation = chainNext[currentLocation];
    } while (currentLocation != newChainLocation);

    int tmp=chainNext[baseChainLocation];
    chainNext[baseChainLocation]=chainNext[newChainLocation];
    chainNext[newChainLocation]=tmp;

}

int Goban::getFreeNeighborhood(int location) {
    int res=0;
    for (int i=0;i<4;i++) {
        int templocation=location+directions[i];
        if (state[templocation]==EMPTY )
            res++;
    }
    return res;
}

    bool Goban::isOneLibertyOfChain(int location, int localChainId) {
        if (state[location] != EMPTY)
            return false;

        for (int i=0;i<4;i++) {
            int templocation=location+directions[i];  
            if (chainId[templocation] == localChainId)
                return true;
        }
        return false;
    }


// All the stones are considered to be alive
// Score is from the point of view of BLACK
float Goban::score () {

    int pointB=0;
    int pointW=0;

    for (int i=0; i<_bigsize*_bigsize; i++) {
        switch(state[i]) {
            case EDGE: 
                break;

            case WHITE: 
                pointW++;
                break;

            case BLACK: 
                pointB++;
                break;

            case EMPTY: 
                bool isB=false;
                bool isW=false;
                for (int j=0;j<4;j++) {
                    if (state[i+directions[j]] == BLACK) {
                        isB=true;
                    }
                    else if (state[i+directions[j]] == WHITE) {
                        isW=true;
                    }
                }
                if ((isB && isW) || (!isB && !isW)) 
                    break;
                else {
                    if (isB)
                        pointB++;
                    if (isW)
                        pointW++;
                }
        }
    }

    return (float) pointB-pointW-_komi;
}

int* Goban::getFreeLocations() {
    return freeLocations;
}

int Goban::getNbFreeLocations() {
    return freeLocationsIndex;
}

vector<int> Goban::getLegalLocations() {

    vector<int> res;
    for (int i=0; i<freeLocationsIndex; i++)
        if (is_legal(freeLocations[i]))// && !is_eye(freeLocations[i]))
            res.push_back(freeLocations[i]);

    //res.push_back(PASSMOVE);

    return res;

}




GobanKey Goban::getGobanKey() {

    // un int peut contenr 15 elements a 4 valeurs
    int nb_elem_per_int = 15;
    int nb_int = (int) ((_bigsize * _bigsize)/nb_elem_per_int) + 2; // +1 because (int) truncate to the inferior and +1 for the information int 
    int indice;

    GobanKey res = new uint[nb_int];

    // le premier int contient quelques infos
    // les suivants contiennent l'etat du goban
    res[0] = nb_int;  //nombre d'elements du tableau
    assert(getNbFreeLocations()<=pow((double)2,(double)12));
    res[0] = res[0]* (int)pow((double)2,(double)12);
    res[0] += getNbFreeLocations(); //nombre d'emplacements libres


    for (int i=1; i<nb_int; i++) {
        res[i]=0;
    }


    for (int i=0; i<_bigsize*_bigsize; i++) {
        indice = (int) (i/nb_elem_per_int + 1);
        res[indice] = res[indice]*4;
        res[indice]+=state[i];
    }



    return res;

}

bool Goban::equal_gobanKey(GobanKey gobanKey1, GobanKey gobanKey2) {

    int nb_elem = gobanKey1[0]>>12; 

    for (int i=0; i<nb_elem; i++) {
        if (gobanKey1[i] != gobanKey2[i])
            return false;
    }
    return true;
}

void Goban::showGobanKey(GobanKey gobanKey) {
    int nb_elem = gobanKey[0]>>12; 

    for (int i=0; i<nb_elem; i++) {
        cerr << gobanKey[i] << " ";
    }
    cerr << endl;


}

float Goban::MCsimu(int location, vector<int> & listMoves) {


    int nbMoves=0;
    int MAX_MOVES_SIMU=200;
    int locationMC;

    Goban* tempGoban = new Goban(*this);
    tempGoban->play(tempGoban->_isBlackTurn,location);

    int nbpass = tempGoban->_nbPass;

    while (nbpass < 2 && nbMoves<MAX_MOVES_SIMU) {
        //locationMC = tempGoban->selectMoveMC(); 
        locationMC = tempGoban->selectMoveMCexp(); 
        tempGoban->play(tempGoban->get_playerTurn(),locationMC);
        listMoves.push_back(locationMC);
        nbMoves++;
        //tempGoban->show();
        if (locationMC == PASSMOVE)
            nbpass++;
        else
            nbpass=0;
    }
    //tempGoban->show();
    float score=tempGoban->score();
    delete tempGoban;

    // score is from the point of view of Black
    return (score>0);
}

bool Goban::isTerminal() {
    return (_nbPass == 2);
}

int Goban::getNbPass() {
    return _nbPass;
}

int Goban::selectMoveMC() {

    int nbFreeLocations = getNbFreeLocations();
    if (nbFreeLocations == 0)
        return PASSMOVE;
    int debut=rand()%nbFreeLocations;

    for (int i=debut;i<nbFreeLocations;i++) {
        if (is_legal(freeLocations[i]) && !is_eye(freeLocations[i]))
            return freeLocations[i];
    }

    for (int i=0;i<debut;i++) {
        if (is_legal(freeLocations[i]) && !is_eye(freeLocations[i]))
            return freeLocations[i];
    }



    return PASSMOVE;
}

int Goban::selectMoveMCexp() {

    updateAllLocationsValue();
    int nbFreeLocations = getNbFreeLocations();
    if (nbFreeLocations == 0)
        return PASSMOVE;
    float sumVal=0;
    for (int i=0;i<nbFreeLocations;i++)
        sumVal+=locationsValue[_isBlackTurn][freeLocations[i]];

    if (sumVal==0)
        return PASSMOVE;

    float randomVal=(rand()/double(RAND_MAX))*sumVal;  


    int debut;
    float currentVal=0;
    
    for (int i=0;i<nbFreeLocations;i++) {
        currentVal+=locationsValue[_isBlackTurn][freeLocations[i]];
        if (randomVal <= currentVal) {
            debut=i;
            break;
//            return freeLocations[i];
        }
    }
 

    for (int i=debut;i<nbFreeLocations;i++) {
        if (is_legal(freeLocations[i]) && !is_eye(freeLocations[i]))
            return freeLocations[i];
        else {
            locationsValue[_isBlackTurn][freeLocations[i]] = 0;
    //        cerr << locationsValue[_isBlackTurn][freeLocations[i]] << endl;
     //       assert(0);
         }
    }

    for (int i=0;i<debut;i++) {
        if (is_legal(freeLocations[i]) && !is_eye(freeLocations[i]))
            return freeLocations[i];
        else {
            locationsValue[_isBlackTurn][freeLocations[i]] = 0;
        }
    }

   // assert(0);
    return PASSMOVE;


}

// we update only the moves close to the last played
void Goban::updateAllLocationsValue() {

    int nbFreeLocations = getNbFreeLocations();

    for (int i=0; i< nbFreeLocations; i++) {
        locationsValue[_isBlackTurn][freeLocations[i]] = 1;
    }


    if (lastPlayedMove == PASSMOVE)
        return;
    int location;
    for (int i=0; i<8 ; i++) {
        location=lastPlayedMove + directions[i];
        if (state[location] == EMPTY)
            updateLocationsValue(location);
    }
}

void Goban::updateLocationsValue(int location) {


    // not legal

        if (!is_legal(location)) {
            locationsValue[_isBlackTurn][location] = 0;
            return;
        }
    

    // eye
        if (is_eye(location)) {
            locationsValue[_isBlackTurn][location] = 0;
            return;
        }
   
        locationsValue[_isBlackTurn][location] = 10;

    // save groups
    
    //    if (save(location))
    //        locationsValue[_isBlackTurn][location] += 20000;

   
    // capture groups
    
        if (capture(location))
            locationsValue[_isBlackTurn][location] += 100;
           

    // patterns
        //if (patternValue[_isBlackTurn][getIndPattern(location)] > 0)
         //   cerr << "pattern match" << endl;
     //   locationsValue[_isBlackTurn][location] += patternValue[_isBlackTurn][getIndPattern(location)];
    
    

}

int Goban::getIndPattern(int location) {

	int res=state[location+directions[0]];
	for (int i=1; i<8 ; i++) {
		res=res<<2;
		res+=state[location+directions[i]];
	}
	assert (res < 65536);
	return res;

}





bool Goban::save(int location) {
 
    int templocation;
    int nb_empty = 0;
    bool danger = false;
    for (int i=0;i<4;i++) {
        templocation=location+directions[i];
        if ( (state[templocation]==_isBlackTurn) &&  (chainTrueLib[chainId[templocation]] ==1) ) { // does not cover all the cases
            danger = true;
        }
        if ( (state[templocation]==EMPTY))
            nb_empty++;
    }
    if (danger && nb_empty >= 2)
        return true;
    return false;

}

bool Goban::capture(int location) {
 
    int templocation;
    for (int i=0;i<4;i++) {
        templocation=location+directions[i];
        if ( (state[templocation]!=_isBlackTurn) &&  (chainTrueLib[chainId[templocation]] ==1) ) { 
            return true;
        }
    }
    return false;
}
