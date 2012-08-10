#include <cassert>
#include <cstdlib>
#include <cmath>
#include <cstdio>
#include <string>
#include <iostream>
#include <vector>

using namespace std;


#define WHITE 0
#define BLACK 1
#define EMPTY 2
#define EDGE 3

#define PASSMOVE -1
#define RESIGN -2

#define DEFAULT_KOMI 6.5


class LBIT {

    public:
    LBIT();
    LBIT(int val);
    void show();

    private:
    long _val;
    int _boardSize;


};



class Goban {

 public:
  Goban();
  Goban(int size);

  // usefull functions :)
  void play(string player, string move);
  vector<int> getLegalLocations();
  void show();
  float score ();
  void clear();

  // interface functions
  LBIT moveToLBIT (string move);
  string LBITToMove (LBIT move);

  // internal functions
 private:
  void play(int player, LBIT move);
  void removeChain (int location);
  void placeStone (int location);
  void removeStone (int location);
  void mergeChains (int baseChainLocation, int newChainLocation);
  void processNewNeighborhood(int newLocation, int oldLocation);
  int getFreeNeighborhood(int location);
  bool isOneLibertyOfChain(int location, int localChainId);
  bool isOnBoard(int location);

  bool is_legal(int location);
  bool is_suicide(int v);


 public:

  //getters
  int getSize() { return _size;};
  float getKomi() { return _komi;};
  int getTimeLeft() { return _timeLeft;};
  int getKo() { return _ko;};
  int getNbPass() { return _nbPass;};
  int get_playerTurn() { return _isBlackTurn;};
  int getLastPlayedMove() { return _lastPlayedMove;};

  //setters
  void setSize(int size) { _size = size; clear(); }
  void setKomi(float komi){ _komi = komi; }
  void setTimeLeft(int timeLeft){ _timeLeft = timeLeft; }
  void set_playerTurn(int player) { _isBlackTurn = player; }

 
 
 private:
  int _size;
  float _komi;
  int _timeLeft;
  int _ko;
  int _nbPass;
  int _isBlackTurn;
  int _lastPlayedMove;


};



