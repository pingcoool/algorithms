#include <gtest/gtest.h>

#include "../solution.h"

// // 先序遍历
// TEST(ExampleTest, PreorderTraversal) {
//
// }




// 测试套件示例
class MyTestSuite : public ::testing::Test {
protected:
    void SetUp() override {
        // 测试前的设置代码
       //       1
       //     /   \
       //    /     \
       //   2       6
       //  / \     / \
       // 3   4   7   9
       //    /     \
       //   5       8
        root_ = std::make_shared<TreeNode<int> >(1);
        root_->left = std::make_shared<TreeNode<int> >(2);
        root_->left->left = std::make_shared<TreeNode<int> >(3);
        root_->left->right = std::make_shared<TreeNode<int> >(4);
        root_->left->right->left = std::make_shared<TreeNode<int> >(5);
        root_->right = std::make_shared<TreeNode<int> >(6);
        root_->right->left = std::make_shared<TreeNode<int> >(7);
        root_->right->left->right = std::make_shared<TreeNode<int> >(8);
        root_->right->right = std::make_shared<TreeNode<int> >(9);
    }

    void TearDown() override {
        // 测试后的清理代码

    }
public:
    std::shared_ptr<TreeNode<int> > root_{nullptr};
};

// 先序遍历
TEST_F(MyTestSuite, PreorderTraversal) {
    PreorderTraversal<int>(root_, [](const int& t) {
        printf("%d ", t);
    });
}

// 中序遍历
TEST_F(MyTestSuite, InorderTraversal) {
    InorderTraversal<int>(root_, [](const int& t) {
        printf("%d ", t);
    });
}

// 后序遍历
TEST_F(MyTestSuite, PostTraversal) {
    PostTraversal<int>(root_, [](const int& t) {
        printf("%d ", t);
    });
}

// 层序遍历
TEST_F(MyTestSuite, LevelOrderTraversal) {
    LevelOrderTraversal<int>(root_, [](const int& t) {
        printf("%d ", t);
    });
}

// 字符串表示
TEST_F(MyTestSuite, TreeFromString) {
    TreeFromString<int>("1(2(,4(5,)),3(6(,8),7))", [](const int& t) {
        printf("%c ", t);
    });
    printf("\n");
    TreeFromString<int>("1(2,3)", [](const int& t) {
        printf("%c ", t);
    });
}

// 从前序和中序遍历构建二叉树
TEST_F(MyTestSuite, BuildTreeFromPreAndIn) {
    std::vector<int> pre_order{1,2,3,4,5,6,7,8,9};
    std::vector<int> in_order{3,2,5,4,1,7,8,6,9};

    //  后续遍历
    auto root = BuildTreeFromPreAndIn<int>(pre_order, in_order);
    PostTraversal<int>(root, [](const int& t) {
        printf("%d ", t);
    });

}

