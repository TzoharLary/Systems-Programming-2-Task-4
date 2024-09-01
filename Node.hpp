// ID: 207492315
// Email: Tzohary1234@gmail.com
#ifndef NODE_HPP
#define NODE_HPP

#include <vector>
#include <iostream>

template <typename T>
class Node {
private:
    T value;
    std::vector<Node<T> *> children_; // vector of pointers to child nodes

public:
    Node(T val) : value(val) {}
    ~Node() {}
    void clearChildren() {
        children_.clear();
    }
    void addChild(Node<T> *child) {
        children_.push_back(child);
    }
    int getCurrentChildrenNum() const {
        return children_.size();
    }
    T getValue() const {
        return value;
    }
    const std::vector<Node<T> *> &getChildren() {
        return children_;
    }


};

#endif // NODE_HPP
