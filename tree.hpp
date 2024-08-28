// Tair Mazriv
// id: 209188382
// tairmazriv@gmail.com

#ifndef TREE_HPP
#define TREE_HPP

#include <algorithm>
#include <vector>
#include <iostream>
#include <stdexcept>
#include "node.hpp"
#include "iterators.hpp"
#include "treeGUI.hpp"

using namespace std;

template <typename T, size_t k = 2>
class Tree {
private:
    Node<T>* root;

    // Helper function to gather all nodes in the tree into a vector.
    void gatherNodes(Node<T>* currNode, vector<Node<T>*>& nodeList) {
        if (currNode == nullptr) {
            return;
        }
        nodeList.push_back(currNode);

        // Recursively gather nodes from children.
        for (Node<T>* node : currNode->getChildren()) {
            gatherNodes(node, nodeList);
        }
    }

    // Helper function to create a balanced binary heap from a sorted list of nodes.
    Node<T>* makeHeap(const vector<Node<T>*>& nodesList, size_t start, size_t end) {
        if (start >= end) {
            return nullptr;
        }
        size_t middle = (start + end) / 2;
        Node<T>* node = nodesList[middle];
        node->getChildren().clear();
        node->addChildren(makeHeap(nodesList, start, middle));
        node->addChildren(makeHeap(nodesList, middle + 1, end));
        return node;
    }

public:
    Tree() : root(nullptr) {}
    
    // Function to set the root of the tree.
    void add_root(Node<T>* node) { root = node; }
    Node<T>* get_root() { return root; }
    
    // Function to add a child node to a parent node, with enforcement of k children limit.
    void add_sub_node(Node<T>* parent, Node<T>* child) {
        if (parent == nullptr) {
            cerr << "Parent node cannot be null." << endl;
            return;
        }

        // Check if the parent exists in the tree
        if (!node_exists(root, parent)) {
            cerr << "Error: Parent node " << parent->getValue() << " is not in the tree." << endl;
            return;
        }

        // Check if the child is already in the tree
        if (node_exists(root, child)) {
            cerr << "Error: Node " << child->getValue() << " is already in the tree." << endl;
            return;
        }

        // Check if the parent already has k children
        if (parent->getChildren().size() >= k) {
            cerr << "Error: Cannot add more than " << k << " children to node " << parent->getValue() << "." << endl;
            return;
        }

        parent->addChildren(child);
        cout << "Added child " << child->getValue() << " to parent " << parent->getValue() << endl;
    }

    // Helper function to check if a node exists in the tree
    bool node_exists(Node<T>* currentNode, Node<T>* targetNode) {
        if (currentNode == nullptr) {
            return false;
        }
        if (currentNode == targetNode) {
            return true;
        }
        for (auto child : currentNode->getChildren()) {
            if (node_exists(child, targetNode)) {
                return true;
            }
        }
        return false;
    }

    // Iterators for different tree traversals.
    PreOrderIter<T> begin_pre_order() { return PreOrderIter<T>(root); }
    PreOrderIter<T> end_pre_order() { return PreOrderIter<T>(nullptr); }
    
    PostOrderIter<T> begin_post_order() { return PostOrderIter<T>(root); }
    PostOrderIter<T> end_post_order() { return PostOrderIter<T>(nullptr); }

    InOrderIter<T> begin_in_order() { return InOrderIter<T>(root); }
    InOrderIter<T> end_in_order() { return InOrderIter<T>(nullptr); }

    BFSIter<T> begin_bfs_scan() { return BFSIter<T>(root); }
    BFSIter<T> end_bfs_scan() { return BFSIter<T>(nullptr); }

    DFSIter<T> begin_dfs_scan() { return DFSIter<T>(root); }
    DFSIter<T> end_dfs_scan() { return DFSIter<T>(nullptr); }

    HeapIter<T> begin_heap() { 
        vector<Node<T>*> nodesList;
        gatherNodes(root, nodesList);
        return HeapIter<T>(nodesList); 
    }
    HeapIter<T> end_heap() { return HeapIter<T>({}); }

    // Default iterator using BFS.
    BFSIter<T> begin() { return BFSIter<T>(root); }
    BFSIter<T> end() { return BFSIter<T>(nullptr); }

    // Function to transform the tree into a heap.
    void myHeap() {
        vector<Node<T>*> nodesList;
        gatherNodes(root, nodesList);
        sort(nodesList.begin(), nodesList.end(), 
            [](Node<T>* a, Node<T>* b) { return a->getValue() < b->getValue(); });
        root = makeHeap(nodesList, 0, nodesList.size());
    }

    // Function to render the tree using a GUI.
    void renderTree() const {
        if (root) {
            TreeGUI<T> gui;
            gui.renderTree(root);
        } else {
            cerr << "Tree is empty, cannot render." << endl;
        }
    }

    // Overloading the << operator to trigger rendering of the tree.
    friend ostream& operator<<(ostream& os, const Tree<T, k>& tree) {
        tree.renderTree();
        return os;
    }

    // Destructor to clean up all nodes in the tree.
    ~Tree() { destroy_tree(root); }

    // Helper function to recursively delete all nodes.
    void destroy_tree(Node<T>* node) {
        if (node) {
            for (auto child : node->getChildren()) {
                destroy_tree(child);
            }
            delete node;
        }
    }
};

#endif // TREE_HPP
