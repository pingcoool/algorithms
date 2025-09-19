//
// Created by pingooosm on 25-8-26.
//

#ifndef SOLUTION_H
#define SOLUTION_H
#include <functional>
#include <memory>

template<typename T>
struct Node {
    explicit Node(T data) : data(data) {
    }

    std::shared_ptr<Node<T> > next;
    T data;
};

/***
 * 遍历链表
 */
template<typename T>
void TraversalLinkedList(std::shared_ptr<Node<T> > head, const std::function<void(T t)>& callback) {
    auto& cur = head;
    while (cur != nullptr) {
        callback(cur->data);
        cur = cur->next;
    }
}

/***
 * 逆转链表
 */
template<typename T>
std::shared_ptr<Node<T> > ReverseLinkedList(std::shared_ptr<Node<T> > head) {
    // 初始化
    std::shared_ptr<Node<T> > prev = nullptr;
    std::shared_ptr<Node<T> > cur = nullptr;
    std::shared_ptr<Node<T> > next = head;
    while (next != nullptr) {
        // 行进
        prev = cur;
        cur = next;
        next = cur->next;
        // 逆转
        cur->next = prev;
    }
    return cur;
}

class Solution {
public:
    static int test_func(int a, int b) {
        return a + b;
    }
};



#endif //SOLUTION_H
