/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** TestVector
*/

#include "utils/Vector.hpp"
#include <gtest/gtest.h>

TEST(Vector, CreateIntVector)
{
    EXPECT_NO_THROW(GameEngine::Vector2<int> vector(0, 0));
}

TEST(Vector, IntVectorNullLenght)
{
    GameEngine::Vector2<int> vector(0, 0);
    EXPECT_EQ(vector.length(), 0);
}

TEST(Vector, IntVectorLenght0_5)
{
    GameEngine::Vector2<int> vector(0, 5);
    EXPECT_EQ(vector.length(), 5.0f);
}

TEST(Vector, IntVectorLenght42_0)
{
    GameEngine::Vector2<int> vector(42, 0);
    EXPECT_EQ(vector.length(), 42.0f);
}
