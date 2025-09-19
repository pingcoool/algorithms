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
        // 0 -> 1 -> 2 -> 3 -> 4 -> 5 -> 6 -> 7 -> 8 -> 9

        head_ = std::make_shared<Node<int> >(0);
        auto cur = head_;
        for (int i = 1; i < 10; ++i) {
            cur->next = std::make_shared<Node<int> >(i);
            cur = cur->next;
        }
    }

    void TearDown() override {
        // 测试后的清理代码
    }

public:
    std::shared_ptr<Node<int>> head_;
};

// 遍历链表
TEST_F(MyTestSuite, TraversalLinkedList) {
    TraversalLinkedList<int>(head_, [](int t) {
        printf("%d, ", t);
    });
}

// 逆转链表
TEST_F(MyTestSuite, ReverseLinkedList) {
    auto res = ReverseLinkedList(head_);

    TraversalLinkedList<int>(res, [](int t) {
        printf("%d, ", t);
    });
}