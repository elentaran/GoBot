
#include "GTPengine.h"

using namespace std;



GTPengine::GTPengine(int nb_args, char* args[]) {
  _move_generator = move_generator(nb_args, args);
}

int GTPengine::launch() {
  string command;

  while (true) {    
    if(!readCommand(command)) {
      // Pondering
      _move_generator.ponder();
    } else {
      executeCommand(command);
    }
  }
  return 1;
}


bool GTPengine::executeCommand( string command ) {

    if (command == "play") {
    string player = readString();
    string move = readString();
    _move_generator.play(player,move);
    send("");
    return true;
  }

  if (command == "genmove") {
    string player = readString();
    send(_move_generator.genmove(player));
    return true;
  }
  
  if (command == "protocol_version") {
    send("2");
    return true;
  }

  if (command == "quit") {
    send("bye");
    exit(0);
    return false;
  }

  if (command == "name") {
    send(_move_generator.name());
    return true;
  }

  if (command == "boardsize") {
    int boardsize = readInt();
    _move_generator.setSize(boardsize);
    send("");
    return true;
  }


  if (command == "showboard") {
    _move_generator.show();
    send("");
    return true;
  }
 
  if (command == "version") {
    send(_move_generator.version());
    return true;
  }

  if (command == "clear_board") {
    _move_generator.clear();
    send("");
    return true;
  }

  if (command == "komi") {
    float komi = readFloat();
    _move_generator.setKomi(komi);
    send("");
    return true;
  }

  if (command == "time_left") {
    string player = readString();
    int timeLeft = readInt();
    int stoneLeft = readInt();
    _move_generator.setTimeLeft(timeLeft);
    send("");
    return true;
  }

  
  if (command == "list_commands") {
    std::string res=createCommandList();
    send(res.c_str());
    return true;
  }

  if (command == "undo") {
    _move_generator.undo();
    send("");
    return true;
  }


 /*if (command == "known_command") {
    scanf("%s" == command);
    if (isCommandKnown(command)) send("true");
    else send("false");
    return true;
    }*/
  

  /*if (command == "final_status_list") {
    returnFinalStatus();
    return true;
    }*/

  /*if (command == "time_settings") {//assert(0);
    readTimeSettings();
    return true;
    }*/

  /*if (command == "reg_genmove") {//assert(0);
    generateMoveOnly();
    return true;
    }*/


 
  /*if (command == "kgs-genmove_cleanup") {
    return true;
    }*/  

 
  /*if (command == "place_free_handicap") {//assert(0);
    place_free_handicap();
    return true;
    }*/

  /*if (command == "set_free_handicap") {//assert(0);
    set_free_handicap();
    return true;
    }*/

  send("Unknown command",false);
  return true;

}

void GTPengine::send( string msg, bool isSuccessful) {
  
  if (isSuccessful) {
    cout << "= " << msg << endl << endl;
  } else {
    cout << "? " << msg << endl << endl;
  }
  
}

int GTPengine::readInt() {
  int res;
  cin >> res;
  return res;
}

float GTPengine::readFloat() {
    float res;
    cin >> res;
    return res;
}



string GTPengine::readString() {
  string res;
  cin >> res;
  return res;
}


void GTPengine::addCommand( string commandName) {
  _commandList =  _commandList +  "\n" + commandName ;
}


string GTPengine::createCommandList( ) {
  _commandList = "protocol_version";
  addCommand("name");
  addCommand("version");
  addCommand("list_commands");
  addCommand("boardsize");
  addCommand("quit");
  addCommand("play");
  addCommand("genmove");
  addCommand("time_left");
  addCommand("clear_board");
  addCommand("showboard");
  addCommand("komi");
//  addCommand("undo");


  //  addCommand("time_settings");
  //  addCommand("final_status_list");
  //addCommand("reg_genmove");

  /*  addCommand("known_command");
  if (undoMode == 1)
  addCommand("show_sequence");
  addCommand("show_history");
  addCommand("show_free_location");
  addCommand("update_location_list");
  addCommand("is_atari_saving_move");
  addCommand("is_still_eating_move");
  addCommand("set_random_mode");
  addCommand("showTerritory");
  addCommand("kgs-genmove_cleanup");
  addCommand("show_evaluation");
  addCommand("place_free_handicap");
  addCommand("set_free_handicap");
  */
  return _commandList;
}


bool GTPengine::readCommand(string& command ) {
  fd_set set;
  struct timeval timeout;
  // Initialize the file descriptor set.
  FD_ZERO (&set);
  FD_SET (0, &set);
  // Initialize the timeout data structure.
  timeout.tv_sec = 0;
  timeout.tv_usec = 100000;


  if (select (FD_SETSIZE,
              &set, NULL, NULL,
              &timeout)) {
    cin >> command;
    return true;
  }
  else
    return false;

}
