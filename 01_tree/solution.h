//
// Created by pingooosm on 25-8-26.
//

#ifndef SOLUTION_H
#define SOLUTION_H
#include <assert.h>
#include <functional>
#include <memory>
#include <queue>
#include <stack>
#include <string>

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

/***
 * 二叉树前序遍历
 */
template <typename T>
void PreorderTraversal(std::shared_ptr<TreeNode<T>> root, const std::function<void(const T&)>& callback) {
    if (root == nullptr) {
        return;
    }
    callback(root->data);
    PreorderTraversal(root->left, callback);
    PreorderTraversal(root->right, callback);
}

/***
 * 二叉树前序遍历, 不使用递归
 * 思路: 根出栈，右进栈，左进栈
 */
template <typename T>
void PreorderTraversalStack(std::shared_ptr<TreeNode<T>> root, const std::function<void(const T&)>& callback) {
    if (root == nullptr) {
        return;
    }
    std::stack<std::shared_ptr<TreeNode<T>>> s;
    s.push(root);
    while (!s.empty()) {
        auto cur = s.top();
        s.pop();
        callback(cur->data);
        if (cur->right != nullptr) {
            s.push(cur->right);
        }
        if (cur->left != nullptr) {
            s.push(cur->left);
        }
    }
}

/***
 * 二叉树中序遍历
 */
template <typename T>
void InorderTraversal(std::shared_ptr<TreeNode<T>> root, const std::function<void(const T&)>& callback) {
    if (root == nullptr) {
        return;
    }
    InorderTraversal(root->left, callback);
    callback(root->data);
    InorderTraversal(root->right, callback);
}

/***
 * 二叉树中序遍历, 不使用递归
 * 思路: 左沿线进栈，出栈后处理右节点
 */
template <typename T>
void InorderTraversalStack(std::shared_ptr<TreeNode<T>> root, const std::function<void(const T&)>& callback) {
    if (root == nullptr) {
        return;
    }
    std::stack<std::shared_ptr<TreeNode<T>>> s;
    auto cur = root;
    while (cur != nullptr || !s.empty()) {
        // 循环找最左
        while (cur != nullptr) {
            s.push(cur);
            cur = cur->left;
        }
        // 打印最左节点
        auto node = s.top();
        s.pop();
        callback(node->data);

        // 出栈后, 处理右节点
        cur = node->right;
    }
}

/***
 * 二叉树后序遍历
 */
template <typename T>
void PostTraversal(std::shared_ptr<TreeNode<T>> root, const std::function<void(const T&)>& callback) {
    if (root == nullptr) {
        return;
    }
    PostTraversal(root->left, callback);
    PostTraversal(root->right, callback);
    callback(root->data);
}

/***
 * 二叉树后序遍历, 不使用递归
 * 思路: 双栈法, 左右根 为逆序的 根右左
 */
template <typename T>
void PostTraversalStack(std::shared_ptr<TreeNode<T>> root, const std::function<void(const T&)>& callback) {
    if (root == nullptr) {
        return;
    }
    std::stack<std::shared_ptr<TreeNode<T>>> s;
    std::stack<std::shared_ptr<TreeNode<T>>> res;
    s.push(root);
    while (!s.empty()) {
        auto cur = s.top();
        s.pop();
        res.push(cur);
        if (cur->left != nullptr) {
            s.push(cur->left);
        }
        if (cur->right != nullptr) {
            s.push(cur->right);
        }
    }
    while (!res.empty()) {
        callback(res.top()->data);
        res.pop();
    }
}

/***
 * 二叉树层序遍历
 */
template <typename T>
void LevelOrderTraversal(std::shared_ptr<TreeNode<T>> root, const std::function<void(const T&)>& callback) {
    if (root == nullptr) {
        return;
    }
    auto queue = std::queue<std::shared_ptr<TreeNode<T>>>();
    queue.push(root);
    // 利用队列的顺序特性, 每次只处理当前节点及其子节点, 实现层序遍历
    while (!queue.empty()) {
        auto node = queue.front();
        queue.pop();

        callback(node->data);
        if (node->left) {
            queue.push(node->left);
        }
        if (node->right) {
            queue.push(node->right);
        }
    }
}

/***
 *  二叉树从字符串表示中解析
 *  思路: 找出字符串的组织逻辑: 根(左, 右), 按照这个组织逻辑分治解析
 *        注意需要在递归方法中返回已经处理过的位置信息
 */
template <typename T>
size_t TreeFromString4(const std::string& str, size_t i, size_t j, const std::function<void(const T&)>& callback) {
    if (j<i) {
        return 0;
    }

    // 中
    size_t cur = i;
    // root 节点为空
    if (!isdigit(str[i])) {
        callback('x');
        return cur;
    }
    // root 节点非空
    callback(str[cur]);
    ++cur;

    // 左
    if (str[cur] == '(' && cur<=j) {
        cur = TreeFromString4(str, cur+1, j, callback);
    }

    // 右
    if (str[cur] == ',' && cur<=j) {
        cur = TreeFromString4(str, cur+1, j, callback);
        ++cur; // 处理 )
    }
    return cur;
}

template <typename T>
void TreeFromString(const std::string& str, const std::function<void(const T&)>& callback) {
    TreeFromString4(str, 0, str.size(), callback);
}

/***
 * 从前序和中序遍历构建二叉树
 * 前提: 所有节点的 value 都不同
 * 思路: 前序遍历第一个节点必然是根节点; 中序遍历根节点左侧必然是左子树的中序遍历结果
 */
template <typename T>
std::shared_ptr<TreeNode<T> > BuildTreeFromPreAndIn(const std::vector<T> pre_order, size_t pre_i, size_t pre_j,
                                                    const std::vector<T> in_order, size_t in_i, size_t in_j) {
    if (pre_j < pre_i) {
        return nullptr;
    }
    if (pre_i == pre_j) {
        return std::make_shared<TreeNode<T>>(pre_order[pre_i]);
    }
    auto root = std::make_shared<TreeNode<T>>(pre_order[pre_i]);

    // find root in in_order
    size_t in_root = 0;
    bool found = false;
    for (size_t i=in_i; i<=in_j; ++i) {
        if (in_order[i] == root->data) {
            in_root = i;
            found = true;
            break;
        }
    }
    assert(found);
    auto left = BuildTreeFromPreAndIn(pre_order, pre_i + 1, pre_i + (in_root - in_i), in_order, in_i, in_root - 1);
    auto right = BuildTreeFromPreAndIn(pre_order, pre_i + (in_root - in_i) + 1, pre_j, in_order, in_root + 1, in_j);
    root->left = left;
    root->right = right;
    return root;
}

template <typename T>
std::shared_ptr<TreeNode<T> > BuildTreeFromPreAndIn(const std::vector<T> pre_order, const std::vector<T> in_order) {
    return BuildTreeFromPreAndIn(pre_order, 0, pre_order.size()-1, in_order, 0, in_order.size()-1);
}


/***
 * 序列化二叉树
 * 思路: 前序遍历
 */
template <typename T>
std::string SerializeTree(std::shared_ptr<TreeNode<T>> root) {
    std::string res;
    if (root == nullptr) {
        res += "#,";
        return res;
    }
    res += std::to_string(root->data);
    res += ",";
    res += SerializeTree(root->left);
    res += SerializeTree(root->right);
    return res;
}


/***
 * 反序列化二叉树
 * 思路: 前序遍历
 */
template <typename T>
std::shared_ptr<TreeNode<T>> DeserializeTree(const std::string& str, size_t& index) {
    assert(index < str.size());
    if (str.at(index) == '#') {
        index += 2;
        return nullptr;
    }
    assert(isdigit(str.at(index)));
    auto root = std::make_shared<TreeNode<T>>(str.at(index) - '0');
    index += 2;
    root->left = DeserializeTree<T>(str, index);
    root->right = DeserializeTree<T>(str, index);
    return root;
}

class Solution {
public:
    static int test_func(int a, int b) {
        return a + b;
    }
};



#endif //SOLUTION_H
