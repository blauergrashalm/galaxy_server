#include "gtest/gtest.h"
#include "gamechange.hpp"

TEST(GameChange, applyChange)
{
    auto field = std::make_shared<Field>(0, 0);
    std::shared_ptr<Player> player;
    {
        auto change = std::make_shared<GameChange>(player, field);
        change->apply();

        ASSERT_TRUE(field->last_change.lock() == change);
    }
    ASSERT_FALSE(field->last_change.lock());
}