/**
 * @file Player.cpp
 * @author Dave Blair (dblair@seafoamtechnologies.com)
 * @brief This is a Unit Test Fixture to the Card class
 * @version 0.1
 * @date 2024-09-25
 *
 * @copyright Copyright (c) 2024 Seafoam Technologies
 *
 */
#include <gtest/gtest.h>
#include <vector>

#include <Node.hpp>
#include <Asset.hpp>
#include <AdventureGameMap.hpp>
#include <Player.hpp>
#include <Combatant.hpp>
#include <Monster.hpp>

// https://google.github.io/googletest/reference/assertions.html

/**
 * @brief Test parameterized constructor that creates a valid Card object.
 *      In this case, a card is created at the lowest valid suit integer
 *      and the highest valid value integer. Suit 1, Value 1
 */
/*TEST(NodeTest, ValidNode)
{
    ASSERT_EQ(8, 8);
}
*/
TEST(AssetTest, ConstructandGet) {
    chants::Asset magnet("Magnet", "A nice souvenir to put on the fridge at home.", 15, false);

    EXPECT_EQ(magnet.GetName(), "Magnet");
    EXPECT_EQ(magnet.GetMessage(), "A nice souvenir to put on the fridge at home.");
    EXPECT_EQ(magnet.GetValue(), 15);
    EXPECT_FALSE(magnet.isOffensive());
}

TEST(AssetTest, OffensiveAsset) 
{
    chants::Asset hammer("Hammer", "A hammer to help defend yourself", 150, true);

    EXPECT_TRUE(hammer.isOffensive());
    EXPECT_EQ(hammer.GetName(), "Hammer");
    EXPECT_EQ(hammer.GetMessage(), "A hammer to help defend yourself");
    EXPECT_EQ(hammer.GetValue(), 150);
}

TEST(AssetTest, hasBeenUsed){
    chants::Asset drinkingwater("Drinking Water", "This may keep you from going thirsty.", 100, false);

    EXPECT_FALSE(drinkingwater.hasBeenUsed);
}