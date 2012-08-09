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
TEST(testPlay, comprehensionInput) {
    Goban testGoban = Goban(9);
    testGoban.play(BLACK,PASSMOVE);
    testGoban.play(WHITE,RESIGN);
    //testGoban.play(WHITE,"A1");
    //testGoban.play(BLACK,"J9");
    //testGoban.play(WHITE,"E5");
}

// TODO
TEST(testPlay, legalMove) {
    Goban testGoban = Goban(9);
//    testGoban.play(WHITE,"A1");
//    EXPECT_FALSE(testGoban.isLegal("A1"));
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
