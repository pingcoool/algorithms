//
// Created by pingooosm on 25-8-26.
//

#ifndef SOLUTION_H
#define SOLUTION_H
#include <functional>
#include <memory>

template <typename T>
struct TreeNode {
    explicit TreeNode(const T& rhs) {
        data = rhs;
    };
    virtual ~TreeNode() = default;
    std::shared_ptr<TreeNode> left{nullptr};
    std::shared_ptr<TreeNode> right{nullptr};
    T data;
};

template <typename T>
void PreorderTraversal(std::shared_ptr<TreeNode<T>> root, const std::function<void(const T&)>& callback) {
    if (root == nullptr) {
        return;
    }
    callback(root->data);
    PreorderTraversal(root->left, callback);
    PreorderTraversal(root->right, callback);
}
template <typename T>
void InorderTraversal(std::shared_ptr<TreeNode<T>> root, const std::function<void(const T&)>& callback) {
    if (root == nullptr) {
        return;
    }
    InorderTraversal(root->left, callback);
    callback(root->data);
    InorderTraversal(root->right, callback);
}
template <typename T>
void PostTraversal(std::shared_ptr<TreeNode<T>> root, const std::function<void(const T&)>& callback) {
    if (root == nullptr) {
        return;
    }
    PostTraversal(root->left, callback);
    PostTraversal(root->right, callback);
    callback(root->data);
}

class Solution {
public:
    static int test_func(int a, int b) {
        return a + b;
    }
};



#endif //SOLUTION_H
