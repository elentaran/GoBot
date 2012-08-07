#include "goban.h"

using namespace std;

class Node {


    public:
    Node();
    Node(Goban goban, Node* father, int location, int indexFather);
    Node(Goban goban, vector<GobanKey> previousKey);
    void create(); 
    ~Node();
    void show();
    void removeSuperKo();
    bool isSuperKo(int loc);
    int GetIndexMoveUCB();
    int GetMoveFinal();
    int GetIndexFromLoc(int location);
    void descent();
    void update(float res, int loc, vector<int> listMoves); 
    void addNode(int indexLoc); 
    bool existChild(int indexLoc);
    bool isTerminal();
    float MCsimu(int indexLoc, vector<int> &listMoves);
    Node* GetChild(int indexLoc);
    vector<GobanKey> getPreviousKey();

    private:
    int _location;
    int _indexFather;
    Goban _goban; 
    Node* _father;
    vector<int> _legalMoves;
    vector<Node*> _children;
    vector<float> _sumScoreChildren;
    vector<int> _nbTrialsChildren;
    vector<float> _sumAMAFScoreChildren;
    vector<int> _nbAMAFTrialsChildren;

    GobanKey _gobanKey;
    vector<GobanKey> _previousKey;

};


