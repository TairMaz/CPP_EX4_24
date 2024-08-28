// Tair Mazriv
// id: 209188382
// tairmazriv@gmail.com

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include <sstream>
#include <iostream>
#include "tree.hpp"
#include "complex.hpp"
#include "node.hpp"

using namespace std;

// Helper function to create a string tree
Tree<string> createStringTree() {

    Tree<string> tree;

    Node<string>* root = new Node<string>("Root");
    Node<string>* child1 = new Node<string>("Child1");
    Node<string>* child2 = new Node<string>("Child2");
    Node<string>* grandchild1 = new Node<string>("Grandchild1");
    Node<string>* grandchild2 = new Node<string>("Grandchild2");

    tree.add_root(root);
    tree.add_sub_node(root, child1);
    tree.add_sub_node(root, child2);
    tree.add_sub_node(child1, grandchild1);
    tree.add_sub_node(child1, grandchild2);
    return tree;
}

// Helper function to create a int tree
Tree<int> createIntTree() {
    Tree<int> tree;

    Node<int>* root = new Node<int>(1);
    Node<int>* child1 = new Node<int>(2);
    Node<int>* child2 = new Node<int>(3);
    Node<int>* grandchild1 = new Node<int>(4);
    Node<int>* grandchild2 = new Node<int>(5);
    Node<int>* grandchild3 = new Node<int>(6);
    Node<int>* grandchild4 = new Node<int>(7);

    tree.add_root(root);
    tree.add_sub_node(root, child1);
    tree.add_sub_node(root, child2);
    tree.add_sub_node(child1, grandchild1);
    tree.add_sub_node(child1, grandchild2);
    tree.add_sub_node(child2, grandchild3);
    tree.add_sub_node(child2, grandchild4);
    
    return tree;
}

Tree<Complex> createComplexTree() {
    Tree<Complex> tree;

    Complex c1(1.0, 1.0);
    Complex c2(2.0, 2.0);
    Complex c3(3.0, 3.0);
    Complex c4(4.0, 4.0);
    Complex c5(5.0, 5.0);

    Node<Complex>* node1 = new Node<Complex>(c1);
    Node<Complex>* node2 = new Node<Complex>(c2);
    Node<Complex>* node3 = new Node<Complex>(c3);
    Node<Complex>* node4 = new Node<Complex>(c4);
    Node<Complex>* node5 = new Node<Complex>(c5);


    tree.add_root(node1);
    tree.add_sub_node(node1, node2);
    tree.add_sub_node(node1, node3);
    tree.add_sub_node(node2, node4);
    tree.add_sub_node(node2, node5);

    return tree;
}

TEST_CASE("Tree Node Creation") {
    Node<std::string> node("Test");
    CHECK(node.getValue() == "Test");
    CHECK(node.getChildren().empty());
}

TEST_CASE("Tree Structure") {
    Tree<string> tree = createStringTree();

    CHECK(tree.get_root()->getValue() == "Root");
    CHECK(tree.get_root()->getChildren().size() == 2);
    CHECK(tree.get_root()->getChildren()[0]->getValue() == "Child1");
    CHECK(tree.get_root()->getChildren()[1]->getValue() == "Child2");
    CHECK(tree.get_root()->getChildren()[0]->getChildren().size() == 2);
}

TEST_CASE("Iterators") {
    Tree<Complex> compTree;

    Complex c1(1.0, 1.0);
    Complex c2(2.0, 2.0);
    Complex c3(3.0, 3.0);
    Complex c4(4.0, 4.0);
    Complex c5(5.0, 5.0);

    Node<Complex>* node1 = new Node<Complex>(c1);
    Node<Complex>* node2 = new Node<Complex>(c2);
    Node<Complex>* node3 = new Node<Complex>(c3);
    Node<Complex>* node4 = new Node<Complex>(c4);
    Node<Complex>* node5 = new Node<Complex>(c5);

    compTree.add_root(node1);
    compTree.add_sub_node(node1, node2);
    compTree.add_sub_node(node1, node3);
    compTree.add_sub_node(node2, node4);
    compTree.add_sub_node(node2, node5);

    Tree<string> tree = createStringTree();

    // Test PreOrder Iterator
    auto preOrderIt = tree.begin_pre_order();
    CHECK((*preOrderIt)->getValue() == "Root");
    CHECK((*(++preOrderIt))->getValue() == "Child1");
    CHECK((*(++preOrderIt))->getValue() == "Grandchild1");
    CHECK((*(++preOrderIt))->getValue() == "Grandchild2");
    CHECK((*(++preOrderIt))->getValue() == "Child2");


    // Test DFS Iterator on Complex tree
    auto DFSIt = compTree.begin_dfs_scan();
    CHECK((*DFSIt)->getValue() == c1);
    CHECK((*(++DFSIt))->getValue() == c2);
    CHECK((*(++DFSIt))->getValue() == c4);
    CHECK((*(++DFSIt))->getValue() == c5);
    CHECK((*(++DFSIt))->getValue() == c3);


    // Test BFS Iterator is equal to the default iterator
    auto bfsIt = tree.begin_bfs_scan();
    auto It = tree.begin();

    CHECK((*bfsIt)->getValue() == (*It)->getValue());
    CHECK((*(++bfsIt))->getValue() == (*(++It))->getValue());
    CHECK((*(++bfsIt))->getValue() == (*(++It))->getValue());
    CHECK((*(++bfsIt))->getValue() == (*(++It))->getValue());
    CHECK((*(++bfsIt))->getValue() == (*(++It))->getValue());
}

TEST_CASE("Heap Construction") {
    Tree<int> tree = createIntTree();
    CHECK(tree.get_root()->getChildren()[0] > tree.get_root());

    tree.myHeap();
    CHECK(tree.get_root()->getChildren()[0]->getValue()  < tree.get_root()->getValue() );
    CHECK(tree.get_root()->getChildren()[1]->getValue()  > tree.get_root()->getValue() );
    CHECK(tree.get_root()->getChildren()[0]->getValue()  > tree.get_root()->getChildren()[0]->getChildren()[0]->getValue() );
    CHECK(tree.get_root()->getChildren()[0]->getValue() < tree.get_root()->getChildren()[0]->getChildren()[1]->getValue() );
}

TEST_CASE("Test Errors") {
    Tree<string> treeStr; // binary tree that contains string.
    Node<string> *root_node = new Node<string>("root");
    Node<string> *s1 = new Node<string>("string1");
    Node<string> *s2 = new Node<string>("string2");
    Node<string> *s3 = new Node<string>("string3");

    // Capture the output of cerr
    std::stringstream errorOutput;
    std::streambuf* oldCerrStreamBuf = std::cerr.rdbuf(errorOutput.rdbuf());

    treeStr.add_sub_node(root_node, s1);

    CHECK(errorOutput.str().find("Error") != std::string::npos); // there is no root in the tree
    errorOutput.str(""); // Clear the stream

    treeStr.add_root(root_node);
    treeStr.add_sub_node(root_node, s1);

    treeStr.add_sub_node(s2, s3);
    CHECK(errorOutput.str().find("Error") != std::string::npos); // s2 doesnt in the tree
    errorOutput.str(""); // Clear the stream

    treeStr.add_sub_node(root_node, s2);

    treeStr.add_sub_node(root_node, s3);
    CHECK(errorOutput.str().find("Error") != std::string::npos); // more then 2 children to parent root
    errorOutput.str(""); // Clear the stream

    treeStr.add_sub_node(s1, s2);
    CHECK(errorOutput.str().find("Error") != std::string::npos); // s2 already in the tree
    errorOutput.str(""); // Clear the stream

    std::cerr.rdbuf(oldCerrStreamBuf);
}
