#include <gtest/gtest.h>
#include "Entity.hpp"

// Demonstrate some basic assertions.
TEST(HelloTest, BasicAssertions2) {
  // Expect two strings not to be equal.
  EXPECT_STRNE("hello", "hello");
  // Expect equality.
  EXPECT_EQ(7 * 6, 42);
}
