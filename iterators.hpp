// Tair Mazriv
// id: 209188382
// tairmazriv@gmail.com

#ifndef ITERATORS_HPP
#define ITERATORS_HPP

#include <stack>
#include <queue>
#include "node.hpp"

// PreOrder Iterator: Traverses the tree in pre-order (root, left, right).
template <typename T>
class PreOrderIter {
private:
    std::stack<Node<T>*> nodeStack; // Stack to keep track of nodes.

public:
    // Constructor initializes the stack with the root node if it exists.
    PreOrderIter(Node<T>* root) {
        if (root) { nodeStack.push(root); }
    }

    // Comparison operator for inequality.
    bool operator!=(const PreOrderIter& other) const {
        return nodeStack.empty() != other.nodeStack.empty();
    }

    // Dereference operator returns the current node.
    Node<T>* operator*() const { return nodeStack.top(); }

    // Pre-increment operator to move to the next node in pre-order.
    PreOrderIter& operator++() {
        const auto& children = nodeStack.top()->getChildren();
        nodeStack.pop();
        for (auto it = children.rbegin(); it != children.rend(); ++it) {
            nodeStack.push(*it);
        }
        return *this;
    }
};

// PostOrder Iterator: Traverses the tree in post-order (left, right, root).
template <typename T>
class PostOrderIter {
private:
    std::stack<Node<T>*> nodeStack; // Stack to store nodes in post-order.

public:
    // Constructor initializes the stack with all nodes in reverse post-order.
    PostOrderIter(Node<T>* root) {
        if (root) {
            std::stack<Node<T>*> stack;
            stack.push(root);
            while (!stack.empty()) {
                auto topNode = stack.top();
                stack.pop();
                nodeStack.push(topNode);
                for (auto node : topNode->getChildren()) {
                    stack.push(node);
                }
            }
        }
    }

    // Comparison operator for inequality.
    bool operator!=(const PostOrderIter& other) const {
        return !nodeStack.empty() || !other.nodeStack.empty();
    }

    // Dereference operator returns the current node.
    Node<T>* operator*() const { return nodeStack.top(); }

    // Pre-increment operator to move to the next node in post-order.
    PostOrderIter& operator++() {
        nodeStack.pop();
        return *this;
    }
};

// InOrder Iterator: Traverses the tree in in-order (left, root, right).
template <typename T>
class InOrderIter {
private:
    std::stack<Node<T>*> nodeStack; // Stack to keep track of nodes.
    Node<T>* curr; // Current node in the traversal.

    // Push all left children onto the stack.
    void pushLeft(Node<T>* node) {
        while (node) {
            nodeStack.push(node);
            if (!node->getChildren().empty()) {
                node = node->getChildren()[0];
            } else {
                node = nullptr;
            }
        }
    }

public:
    // Constructor initializes the stack with leftmost path from the root.
    InOrderIter(Node<T>* root) : curr(root) {
        pushLeft(root);
    }

    // Comparison operator for inequality.
    bool operator!=(const InOrderIter& other) const {
        return nodeStack.empty() != other.nodeStack.empty();
    }

    // Dereference operator returns the current node.
    Node<T>* operator*() const { return nodeStack.top(); }

    // Pre-increment operator to move to the next node in in-order.
    InOrderIter& operator++() {
        auto topNode = nodeStack.top();
        nodeStack.pop();
        if (topNode->getChildren().size() > 1) {
            pushLeft(topNode->getChildren()[1]);
        }
        return *this;
    }
};

// BFS Iterator: Traverses the tree in breadth-first order (level by level).
template <typename T>
class BFSIter {
private:
    std::queue<Node<T>*> nodeQueue; // Queue to manage nodes by level.

public:
    // Constructor initializes the queue with the root node if it exists.
    BFSIter(Node<T>* root) {
        if (root) { nodeQueue.push(root); }
    }

    // Comparison operator for inequality.
    bool operator!=(const BFSIter& other) const {
        return nodeQueue.empty() != other.nodeQueue.empty();
    }

    // Dereference operator returns the current node.
    Node<T>* operator*() const { return nodeQueue.front(); }

    // Pre-increment operator to move to the next node in BFS.
    BFSIter& operator++() {
        auto frontNode = nodeQueue.front();
        nodeQueue.pop();
        for (Node<T>* node : frontNode->getChildren()) {
            nodeQueue.push(node);
        }
        return *this;
    }
};

// DFS Iterator: Traverses the tree in depth-first order (pre-order variant).
template <typename T>
class DFSIter {
private:
    std::stack<Node<T>*> stack; // Stack to manage nodes in depth-first order.

public:
    // Constructor initializes the stack with the root node if it exists.
    DFSIter(Node<T>* root) {
        if (root) { stack.push(root); }
    }

    // Comparison operator for inequality.
    bool operator!=(const DFSIter& other) const {
        return stack.empty() != other.stack.empty();
    }

    // Dereference operator returns the current node.
    Node<T>* operator*() const { return stack.top(); }

    // Pre-increment operator to move to the next node in DFS.
    DFSIter& operator++() {
        Node<T>* topNode = stack.top();
        stack.pop();
        for (auto it = topNode->getChildren().rbegin(); it != topNode->getChildren().rend(); ++it) {
            stack.push(*it);
        }
        return *this;
    }
};

// Heap Iterator: Iterates over nodes in a heap structure.
template <typename T>
class HeapIter {
private:
    std::vector<Node<T>*> nodesList; // List of nodes representing a heap.
    size_t i; // Current index in the heap.

public:
    // Constructor initializes the iterator with the heap nodes and starting index.
    HeapIter(const std::vector<Node<T>*>& nodes, size_t i) : nodesList(nodes), i(i) {}

    // Comparison operator for inequality.
    bool operator!=(const HeapIter& other) const { return i != other.i; }

    // Dereference operator returns the current node.
    Node<T>* operator*() const { return nodesList[i]; }

    // Pre-increment operator to move to the next node in the heap.
    HeapIter& operator++() {
        ++i;
        return *this;
    }
};

#endif // ITERATORS_HPP
