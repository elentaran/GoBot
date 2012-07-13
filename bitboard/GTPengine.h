
#include "move_generator.h"

using namespace std;



class GTPengine {

 public:

  GTPengine(int nb_args, char* args[]);
  int launch();
  bool readCommand(string& command );
  bool executeCommand( string command );
  void send( string msg, bool isSuccessful= true);
  string createCommandList();
  void addCommand( string commandName);
  int readInt();
  float readFloat();
  string readString();

 private:
  move_generator _move_generator;
  string _commandList;

};
