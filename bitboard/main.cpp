// GoBot

#include "GTPengine.h"


int main(int nb_args, char* args[]) {

  srand ( time(NULL) );
  GTPengine global_GTPengine =  GTPengine(nb_args,args);
  global_GTPengine.launch();

  return 1;
}
