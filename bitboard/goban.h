#include <cassert>
#include <cstdlib>
#include <cmath>
#include <cstdio>
#include <string>
#include <iostream>
#include <vector>

using namespace std;


#define MAX_FAST_BOARD_SIZE (19)
#define MAX_FAST_BOARD_AREA ((MAX_FAST_BOARD_SIZE+2)*(MAX_FAST_BOARD_SIZE+2))

// Don't change those definitions!!!!!
#define WHITE 0
#define BLACK 1
#define EMPTY 2
#define EDGE 3
// Don't change those definitions!!!!!

#define PASSMOVE -1
#define RESIGN -2

#define DEFAULT_KOMI 6.5

#define GobanKey uint*

extern float patternValue[2][65536];

class Goban {

 public:
  Goban();
  Goban(int size);
  void play(int player, int move);
  void setSize(int size);
  int getSize();
  void show();
  void clear();
  void setKomi(float komi);
  void setTimeLeft(int timeLeft);

  void init_directions();

  int xcoord(int location);
  int ycoord(int location);

  void removeChain (int location);
  void placeStone (int location);
  void removeStone (int location);
  float score ();
  void mergeChains (int baseChainLocation, int newChainLocation);
  void processNewNeighborhood(int newLocation, int oldLocation);
  int getFreeNeighborhood(int location);
  bool isOneLibertyOfChain(int location, int localChainId);
  bool isOnBoard(int location);

  int moveToInt(string move);
  string intToMove(int location);
  int playerToInt(string player); 
  string intToPlayer(int player);
  string intToPlayer();
  bool is_legal(int location);
  bool is_suicide(int v);
  bool is_eye(int location);
    
  bool isTerminal();

  void set_playerTurn(int player);
  int get_playerTurn();

  int* getFreeLocations();
  vector<int> getLegalLocations();
  int _bigArea;
  int getNbFreeLocations();

  int getNbPass();

  GobanKey getGobanKey();
  bool equal_gobanKey(GobanKey gobanKey1, GobanKey gobanKey2);
  void showGobanKey(GobanKey gobanKey);

  float MCsimu(int location, vector<int> &listMoves);
  int selectMoveMC();
  int selectMoveMCexp();
  void updateAllLocationsValue();
  void updateLocationsValue(int location);
  int getIndPattern(int location);
  bool capture(int location);
  bool save(int location);


 private:
  int _size;
  int _bigsize;
  float _komi;
  int _timeLeft;
  int _ko;
  int _nbPass;
  int _isBlackTurn;
  int lastPlayedMove;
  int directions[8]; // 4 first are classic directions, 4 last are diagonals

  // describe the Board
  int state[MAX_FAST_BOARD_AREA];
  int chainNext[MAX_FAST_BOARD_AREA];
  int chainId[MAX_FAST_BOARD_AREA];
  int chainTrueLib[MAX_FAST_BOARD_AREA];
  int chainLength[MAX_FAST_BOARD_AREA];


  // used for the update of the board  
  int intersectionUpdated [MAX_FAST_BOARD_AREA];
  int intersectionUpdatedIndex;
  int chainIdUpdatedIndex;


  // list of free locations
  int freeIndex[MAX_FAST_BOARD_AREA];
  int freeLocations[MAX_FAST_BOARD_AREA];
  float locationsValue[2][MAX_FAST_BOARD_AREA];
  int freeLocationsIndex;
  int freeLocationsLastIndex;


};





