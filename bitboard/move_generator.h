#include "bitboard.h"


using namespace std;
  

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


 private:
  bitboard _gameGoban;
  int _timeLeft;
  int _undoMode;
  float _komi;
  


};
