#include <gtest/gtest.h>

#include "../solution.h"

// 简单的测试示例
TEST(ExampleTest, BasicAssertions) {
    EXPECT_EQ(7 + 6, 13);
    EXPECT_EQ(Solution::test_func(7,6), 13);
}




// 测试套件示例
class MyTestSuite : public ::testing::Test {
protected:
    void SetUp() override {
        // 测试前的设置代码
    }

    void TearDown() override {
        // 测试后的清理代码
    }
};

TEST_F(MyTestSuite, Test1) {
    EXPECT_EQ(1 + 1, 2);
}