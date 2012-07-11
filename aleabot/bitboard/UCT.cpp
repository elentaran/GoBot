#include "UCT.h"


Node::Node() {


}

// Node creation except root
Node::Node(Goban goban, Node* father, int location, int indexFather) {

    _location = location;
    _indexFather = indexFather;
    _father = father;
    _goban = goban;
//    _gobanKey = goban.getGobanKey();
//    _previousKey = _father->getPreviousKey();
//    _previousKey.push_back(_gobanKey);
    _legalMoves = _goban.getLegalLocations();
    //removeSuperKo();
    _legalMoves.push_back(PASSMOVE);
    create();
}

// Root Creation
Node::Node(Goban goban, vector<GobanKey> previousKey ) {

    _location = PASSMOVE;
    _indexFather = -1;
    _father = NULL;
    _goban = goban;
    _gobanKey = goban.getGobanKey();
    _previousKey = previousKey;
    _previousKey.push_back(_gobanKey);
    _legalMoves = _goban.getLegalLocations();
    removeSuperKo();
    _legalMoves.push_back(PASSMOVE);
    create();

}

void Node::create() {

   for (int i=0;i<_legalMoves.size();i++) {
        _sumScoreChildren.push_back(1);
        _nbTrialsChildren.push_back(2);
        _children.push_back(NULL);
    }

/*
   for (int i=0;i<_goban._bigArea;i++) {
        _sumAMAFScoreChildren.push_back(1);
        _nbAMAFTrialsChildren.push_back(2);
   }

*/
}


Node::~Node() {

    for (int i=0; i<_children.size(); i++)
        delete _children[i];
    
}


void Node::show() {

    int bestIndex=0;    
    float bestScore=0;
    for (int i=0; i<_legalMoves.size(); i++) {
           int score = _nbTrialsChildren[i];
        
        if (score > bestScore) {
            bestScore = score;
            bestIndex = i;
        }
    }

/*
    for (int i=0;i<_legalMoves.size();i++) {
        cerr << _goban.intToMove(_legalMoves[i]) << "(" << _sumScoreChildren[i]/_nbTrialsChildren[i] << "/"<< _nbTrialsChildren[i] << ")";
        cerr << "[" << _sumAMAFScoreChildren[_legalMoves[i]] /_nbAMAFTrialsChildren[_legalMoves[i]] << "/"<< _nbAMAFTrialsChildren[_legalMoves[i]] << "] ";
    }
    cerr << endl;
*/
    
    cerr << _goban.intToMove(_legalMoves[bestIndex]) << "(" << _sumScoreChildren[bestIndex]/_nbTrialsChildren[bestIndex] << "/"<< _nbTrialsChildren[bestIndex] << ")";
 //   cerr << "[" << _sumAMAFScoreChildren[_legalMoves[bestIndex]]/_nbAMAFTrialsChildren[_legalMoves[bestIndex]] << "/"<< _nbAMAFTrialsChildren[_legalMoves[bestIndex]] << "] ";
    cerr << endl;

}

void Node::removeSuperKo() {

    for (int i=0; i<_legalMoves.size(); i++) {
        if ( isSuperKo(_legalMoves[i]))
            _legalMoves.erase(_legalMoves.begin()+i);
    }
    return;

}

bool Node::isSuperKo(int loc) {

    Goban tempGoban = Goban(_goban);

    tempGoban.play(tempGoban.get_playerTurn(),loc);
    GobanKey testKey = tempGoban.getGobanKey();

    for (int i=0; i<_previousKey.size(); i++) {
        if (tempGoban.equal_gobanKey(testKey,_previousKey[i])) {
           //tempGoban->showGobanKey(testKey); 
            cerr << "SUPERKO!!" << endl;
            return true;
        }
    }

    return false;
}

int Node::GetIndexMoveUCB() {

    float score;
    int bestIndex=0;    
    float bestScore=0;
    float coef_explo=.5;
    float k_AMAF=500;
    float beta_AMAF;
    int nbTrialsTot=0;
    float AMAFval,UCBval,EXPLOval;



     for (int i=0; i<_legalMoves.size(); i++)
        nbTrialsTot+=_nbTrialsChildren[i];

    for (int i=0; i<_legalMoves.size(); i++) {

            
           // AMAFval = _sumAMAFScoreChildren[_legalMoves[i]]/_nbAMAFTrialsChildren[_legalMoves[i]];
           // beta_AMAF = sqrt(k_AMAF/(k_AMAF + 3*nbTrialsTot));
            
            UCBval = (_sumScoreChildren[i]/_nbTrialsChildren[i]);
            EXPLOval = sqrt(log(nbTrialsTot)/_nbTrialsChildren[i]); 
            

            
            //score = (1-beta_AMAF) * (UCBval + coef_explo * EXPLOval) + beta_AMAF * AMAFval;
            score = UCBval + coef_explo * EXPLOval;
            // cerr << "AMAF : " << coef_AMAF * AMAFval << " UCB : " << UCBval << " explo : " << coef_explo * EXPLOval << " score : " << score << endl;
            //string temp;
            //cin >> temp;

        
        if (score > bestScore) {
            bestScore = score;
            bestIndex = i;
        }
    }

    return bestIndex;
}

int Node::GetMoveFinal() {

    float thresholdResign=0.05;

    int bestIndex=0;    
    float bestScore=0;
    float score;
    
     for (int i=0; i<_legalMoves.size(); i++) {
        if (_nbTrialsChildren[i] != 0) {
           // score = (_sumScoreChildren[i]/_nbTrialsChildren[i]);
            score = _nbTrialsChildren[i];
        } else {
            score = 0;
        }
        if (score > bestScore) {
            bestScore = score;
            bestIndex = i;
        }
    }


    if ((_sumScoreChildren[bestIndex]/_nbTrialsChildren[bestIndex])< thresholdResign)
        return RESIGN;

    return _legalMoves[bestIndex];
}



Node* Node::GetChild(int indexLoc) {
    return _children[indexLoc];
}

vector<GobanKey> Node::getPreviousKey() {
    return _previousKey;
}

void Node::descent() {


    // Tree descent
    Node* currentNode = this;
    int newIndexLoc;
    vector<int> listMoves;

    while (true) {
    
        newIndexLoc = currentNode->GetIndexMoveUCB();
        listMoves.push_back(currentNode->_legalMoves[newIndexLoc]);
        if (!currentNode->existChild(newIndexLoc) || currentNode->GetChild(newIndexLoc)->isTerminal())
            break;

        currentNode = currentNode->GetChild(newIndexLoc);
    }
        

    // MC part
    float resMC = currentNode->MCsimu(newIndexLoc,listMoves);

/*
    for (int i=0; i<listMoves.size(); i++)
        cerr << _goban.intToMove(listMoves[i]) << " ";
    cerr << endl;
*/

    // Node Creation part
    if (!currentNode->existChild(newIndexLoc))
        currentNode->addNode(newIndexLoc);

    // Update part
   currentNode = this;
    while (true) {
        newIndexLoc = currentNode->GetIndexFromLoc(listMoves[0]);
        currentNode->update(resMC,newIndexLoc,listMoves); 
        if (!currentNode->existChild(newIndexLoc) || currentNode->GetChild(newIndexLoc)->isTerminal())
            break;
        currentNode = currentNode->GetChild(newIndexLoc);
        listMoves.erase(listMoves.begin(),listMoves.begin()+1);
    }

    

}


int Node::GetIndexFromLoc(int location) {

    int res=RESIGN;
    for (int i=0; i<_legalMoves.size(); i++)
        if (_legalMoves[i] == location)
            res = i;

    assert (res != RESIGN);
    return res;
    
}

bool Node::existChild(int indexLoc) {
    return (_children[indexLoc] != NULL);
}

bool Node::isTerminal() {
    return _goban.isTerminal();
}

void Node::update(float res, int indexLoc, vector<int> listMoves) {

    //score is from the point of view of black
    if (_goban.get_playerTurn()!=BLACK)
        res = 1-res;
    
    _sumScoreChildren[indexLoc]+=res;
    _nbTrialsChildren[indexLoc]++;
/*
    for (int i=0;i<listMoves.size()/2;i+=2) {
        if (listMoves[i]>=0) {
            _sumAMAFScoreChildren[listMoves[i]]+=res;
            _nbAMAFTrialsChildren[listMoves[i]]++;
        }
    }
*/
    
/*     for (int i =0;i<listMoves.size();i++) {
        cerr << _goban.intToMove(listMoves[i]) << " ";
    }
    cerr << endl;*/
}

void Node::addNode(int indexLoc) {

    if (_nbTrialsChildren[indexLoc] < 5)
        return;

    Goban tempGoban = Goban(_goban);
    tempGoban.play(tempGoban.get_playerTurn(),_legalMoves[indexLoc]);

    Node* tempNode= new Node(tempGoban,this,_legalMoves[indexLoc],indexLoc);
    _children[indexLoc]=tempNode;
    

}

float Node::MCsimu(int indexLoc, vector<int> & listMoves) {
    return _goban.MCsimu(_legalMoves[indexLoc], listMoves);
}
