#include "boost/timer.hpp"
//#include "boost/program_options.hpp"
#include "UCT.h"


using namespace std;
//namespace po = boost::program_options;
  

class move_generator {

 public:
  move_generator();
  move_generator(int nb_args, char* args[]);
  void ponder();
  const string name();
  const string version();
  string genmove(string player);


  void play(string player, string move);
  void setSize(int boardsize);
  void show();
  void clear();
  void setKomi(float komi);
  void setTimeLeft(int timeLeft);

  void undo();


  void handleArguments(int nb_args, char* args[]);

  bool isSuperKo(int location);

  void initPatternValue();
  int codeSymPattern(int numSym, int* pattern); 
  int codePattern(int* pattern); 

 private:
  //Node* _rootNode;
  Goban _gameGoban;
  int _timeLeft;
  int _undoMode;
  float _komi;
  int _nb_sim;
  vector<int> _previousMoves;
  vector<int> _previousColors;
  vector<GobanKey> _previousKeys;
  


};
