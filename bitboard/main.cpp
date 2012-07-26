// GoBot

#include "GTPengine.h"
#ifdef GTEST
#include "gtest/gtest.h"
#endif 
using namespace std;




int main(int nb_args, char* args[]) {

#ifdef GTEST
    testing::InitGoogleTest(&nb_args, args);
    return RUN_ALL_TESTS();
#endif 

    srand ( time(NULL) );
    GTPengine global_GTPengine =  GTPengine(nb_args,args);
    global_GTPengine.launch();

    return 1;
}
