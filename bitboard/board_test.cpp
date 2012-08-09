#ifdef GTEST
#include "gtest/gtest.h"
#include "goban.h"

TEST(testCrash,createGoban) {
    Goban testGoban = Goban();
    Goban testGoban2 = Goban(9);
}

TEST(testCrash,part2) {
}

#endif
