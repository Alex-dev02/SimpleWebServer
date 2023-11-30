#include <gtest/gtest.h>

// First comes the name of the test suite (e.g. NetworkingTests, RouterTests)
// Second comes the name of the test itself
TEST(HelloWorldTest, HelloWorldAssertion) {
  EXPECT_STRNE("hello", "world");
}
