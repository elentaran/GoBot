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

#define PASSMOVE -1
#define RESIGN -2

#define DEFAULT_KOMI 6.5

#define BitBoardKey uint*


class BitBoard {

 public:
  BitBoard();
  BitBoard(int size);
  void play(int player, int move);
  void setSize(int size);
  int getSize();
  void show();
  void clear();
  void setKomi(float komi);
  void setTimeLeft(int timeLeft);


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
  bool is_legal(int location);
  bool is_suicide(int v);
    
  bool isTerminal();

  void set_playerTurn(int player);
  int get_playerTurn();

  int* getFreeLocations();
  vector<int> getLegalLocations();
  int _bigArea;
  int getNbFreeLocations();

  int getNbPass();


 private:
  int _size;
  int _bigsize;
  float _komi;
  int _timeLeft;
  int _ko;
  int _nbPass;
  int _isBlackTurn;
  int lastPlayedMove;

  // describe the Board



};





