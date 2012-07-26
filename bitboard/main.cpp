// GoBot

#include "GTPengine.h"
#include "gtest/gtest.h"
using namespace std;




int main(int nb_args, char* args[]) {

    cout << "hello world" << endl;
    testing::InitGoogleTest(&nb_args, args);
    return RUN_ALL_TESTS();

    srand ( time(NULL) );
    GTPengine global_GTPengine =  GTPengine(nb_args,args);
    global_GTPengine.launch();

    return 1;
}
