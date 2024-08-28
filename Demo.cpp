// Tair Mazriv
// id: 209188382
// tairmazriv@gmail.com

/**
 * Demo app for Ex4
 */
#include <iostream>
#include <string>
#include "node.hpp"
#include "tree.hpp"
#include "complex.hpp"

using namespace std;

int main(){

    Node<double> *root_node1 = new Node<double>(1.1);
    Tree<double> tree; // Binary tree that contains doubles.
    tree.add_root(root_node1);
    Node<double> *n1 = new Node<double>(1.2);
    Node<double> *n2 = new Node<double>(1.3);
    Node<double> *n3 = new Node<double>(1.4);
    Node<double> *n4 = new Node<double>(1.5);
    Node<double> *n5 = new Node<double>(1.6);

    tree.add_sub_node(root_node1, n1);
    tree.add_sub_node(root_node1, n2);
    tree.add_sub_node(n1, n3);
    tree.add_sub_node(n1, n4);
    tree.add_sub_node(n2, n5);

    // // The tree should look like:
    // /**
    //  *       root = 1.1
    ///  *     /       
    //  *    1.2      1.3
    //  *   /  \      /
    //  *  1.4  1.5  1.6
    //  */

    cout << "Pre Order iterator" << endl; 
    for (auto node = tree.begin_pre_order(); node != tree.end_pre_order(); ++node){
        cout << (*node)->getValue() << endl;
    } // prints: 1.1, 1.2, 1.4, 1.5, 1.3, 1.6

    cout << "Post Order iterator:" <<endl;
    for (auto node = tree.begin_post_order(); node != tree.end_post_order(); ++node){
        cout << (*node)->getValue() << endl;
    } // prints: 1.4, 1.5, 1.2, 1.6, 1.3, 1.1

    cout << "In Order iterator:" <<endl;
    for (auto node = tree.begin_in_order(); node != tree.end_in_order(); ++node){
        cout << (*node)->getValue() << endl;
    } // prints: 1.4, 1.2, 1.5, 1.1, 1.6, 1.3

    cout << "BFS iterator:" <<endl;
    for (auto node = tree.begin_bfs_scan(); node != tree.end_bfs_scan(); ++node){
        cout << (*node)->getValue() << endl;
    } // prints: 1.1, 1.2, 1.3, 1.4, 1.5, 1.6

    cout << "default iterator:" <<endl;
    for (auto *node : tree){
        cout << node->getValue() << endl;
    } // same as BFS: 1.1, 1.2, 1.3, 1.4, 1.5, 1.6

    cout << tree; // Should print the graph using GUI.
    tree.myHeap();
    cout << tree;


    Node<string> *root_node = new Node<string>("root");
    Node<string> *s1 = new Node<string>("string1");
    Node<string> *s2 = new Node<string>("string2");
    Node<string> *s3 = new Node<string>("string3");
    Node<string> *s4 = new Node<string>("string4");
    Node<string> *s5 = new Node<string>("string5");
    Node<string> *s6 = new Node<string>("string6");
    Node<string> *s7 = new Node<string>("string7");
    Node<string> *s8 = new Node<string>("string8");

    Tree<string, 3> treeStr; // 3 ary tree that contains string.
    treeStr.add_root(root_node);
    treeStr.add_sub_node(root_node, s1);
    treeStr.add_sub_node(root_node, s2);
    treeStr.add_sub_node(root_node, s3);
    treeStr.add_sub_node(root_node, s4);  //will not be added to the root
    treeStr.add_sub_node(s1, s4);
    treeStr.add_sub_node(s1, s5);
    treeStr.add_sub_node(s7, s8);  //will not be added because s7 doesnt in the tree
    treeStr.add_sub_node(s3, s6);
    treeStr.add_sub_node(s3, s7);
    treeStr.add_sub_node(s7, s6);  //will not be added because s6 is already in the tree
    treeStr.add_sub_node(s7, s8);

    cout << treeStr;
    treeStr.myHeap();
    cout << treeStr;


    Node<Complex> *root_nodeComp = new Node<Complex>(Complex(1.1, 1.1));
    Node<Complex> *n1c = new Node<Complex>(Complex(1.2, 1.2));
    Node<Complex> *n2c = new Node<Complex>(Complex(1.3, 1.3));
    Node<Complex> *n3c = new Node<Complex>(Complex(1.4, 1.4));
    Node<Complex> *n4c = new Node<Complex>(Complex(1.5, 1.5));
    Node<Complex> *n5c = new Node<Complex>(Complex(1.6, 1.6));

    Tree<Complex> treeComp; // Binary tree that contains complex.
    treeComp.add_root(root_nodeComp);
    treeComp.add_sub_node(root_nodeComp, n1c);
    treeComp.add_sub_node(root_nodeComp, n2c);
    treeComp.add_sub_node(n1c, n3c);
    treeComp.add_sub_node(n1c, n4c);
    treeComp.add_sub_node(n2c, n5c);

     for (auto node : treeComp){
        cout << node->getValue() << endl;
    } // same as BFS: 1.1, 1.2, 1.3, 1.4, 1.5, 1.6

    cout << treeComp;
    treeComp.myHeap();
    cout << treeComp;

    return 0;
}