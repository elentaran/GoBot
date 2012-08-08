// GoBot

#include "goban.h"
#ifdef GTEST
#include "gtest/gtest.h"
#endif 
using namespace std;



int main(int nb_args, char* args[]) {

#ifdef GTEST
    testing::InitGoogleTest(&nb_args, args);
    return RUN_ALL_TESTS();
#endif 


    return 1;
}
