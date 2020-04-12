#include "gtest/gtest.h"
#include "../include/gamegen.hpp"

TEST(GameGen, countEmptySpots)
{
    auto game_gen = new GameGen();

    {
        DotSpace space;
        space.push_back(DotSpaceColumn{0, 0, 0});
        space.push_back(DotSpaceColumn{0, 0, 0});
        space.push_back(DotSpaceColumn{0, 0, 0});
        EXPECT_EQ(game_gen->countEmptySpots(space), 9);
    }

    {
        DotSpace space;
        space.push_back(DotSpaceColumn{1, 1, 1});
        space.push_back(DotSpaceColumn{1, 1, 1});
        space.push_back(DotSpaceColumn{1, 1, 1});
        EXPECT_EQ(game_gen->countEmptySpots(space), 0);
    }

    {
        DotSpace space;
        space.push_back(DotSpaceColumn{1, 0, 1});
        space.push_back(DotSpaceColumn{0, 1, 1});
        space.push_back(DotSpaceColumn{1, 1, 0});
        EXPECT_EQ(game_gen->countEmptySpots(space), 3);
    }
    delete game_gen;
}
