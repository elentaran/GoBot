#ifdef GTEST
#include "gtest/gtest.h"
#include "goban.h"

TEST(testCrash,createGoban) {
    Goban testGoban = Goban();
    Goban testGoban2 = Goban(19);
    Goban testGoban3 = Goban(1);
}

TEST(testCrash,basicMove) {
    Goban testGoban = Goban();
    testGoban.play(BLACK,PASSMOVE);
}

// TODO
TEST(testPlay,join2groups) {

}

// TODO
TEST(testPlay,capture) {

}

// TODO
TEST(testPlay,suicide) {

}

// TODO
TEST(testPlay,ko) {

}

TEST(testSpeed,1000moves) {
}

// TODO
TEST(testSuperKo,superko1) {
}

// TODO
TEST(testSuperKo,superko2) {
}

#endif
