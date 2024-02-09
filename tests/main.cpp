#include <gtest/gtest.h>

/**
 * @brief This flag enables testing for vectors and matrices
 * @details This flag exists because compiling and running the tests for vectors and matrices takes a lot of time, so
 * we define it to false by default to save time.
 */
#define ALGEBRA_TESTING false

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}