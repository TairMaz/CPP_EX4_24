// Tair Mazriv
// id: 209188382
// tairmazriv@gmail.com

#ifndef NODE_HPP
#define NODE_HPP

#include <vector>

template<typename T>
class Node {
private:
    T value;
    std::vector<Node<T>*> children;

public:
    // Constructor to initialize the node with a value
    Node(T val) : value(val) {}

    // Get the value of the node
    T getValue() const {
        return value;
    }

    // Get the list of child nodes
    std::vector<Node<T>*>& getChildren() {
        return children;
    }

    // Add a child node to the current node
    void addChildren(Node<T>* child) {
        children.push_back(child);
    }
};

#endif // NODE_HPP
