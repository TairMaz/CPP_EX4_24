# CPP_EX4_24

tairmazriv@gmail.com

id: 209188382

# Project Structure:

## 1. node.hpp: Single Node Representation
   
Purpose: Represents a single node in the tree, which holds a value and pointers to its child nodes.

### Key Components:

Data Members: Stores the value of the node and a list of pointers to its children.

Functions: Provides methods to get and set the value of the node, and to manage its children (e.g., adding a child node).

## 2. tree.hpp: k-ary Tree Implementation
Purpose: Implements a generic k-ary tree structure, where each node can have up to k children. The tree can handle different types of data, as specified by the template parameter.

### Key Components:

Data Members: Contains a pointer to the root node and the maximum number of children (k) allowed per node.

Functions:

add_root: Sets the root node of the tree.

add_sub_node: Adds a child node to a specified parent node, ensuring the parent exists and that the number of children does not exceed k.

Iterator Functions: Provides methods to create different iterators (pre-order, post-order, in-order, BFS, DFS) to traverse the tree.

## 3. iterators.hpp: Various Iterators
   
Purpose: Provides iterator classes for different tree traversal methods.

### Key Components:

PreOrderIter: Traverses the tree in pre-order (root, left, right).

PostOrderIter: Traverses the tree in post-order (left, right, root).

InOrderIter: Traverses the tree in in-order (left, root, right) for binary trees.

BFSIter: Performs breadth-first traversal, visiting nodes level by level.

DFSIter: Performs depth-first traversal, similar to pre-order but specifically implemented for DFS.

HeapIter: Used for traversing a binary tree as if it were a binary heap.

## 4. treeGUI.hpp: GUI-Based Tree Rendering
   
Purpose: Handles the visualization of the tree using a graphical user interface (GUI).

### Key Components:

Rendering Functions:

renderNode: Recursively renders each node and its connections to its children.

renderTree: Initializes the SDL environment and starts the rendering process, displaying the tree in a window.

SDL and TTF Libraries: Used for rendering the tree. SDL handles the graphical rendering, while TTF is used for rendering text (node values).

## 5. Complex.hpp: Representation of Complex Numbers

Purpose: Represents and operates on complex numbers with real and imaginary components. 

### Key Components:

Data Members:

real: The real part of the complex number.

imag: The imaginary part of the complex number.

Functions:

Equality Operator (==): Compares two complex numbers for equality.

Magnitude Calculation (magnitude): Computes the magnitude (or modulus) of the complex number.

Comparison Operator (<): Compares the magnitude of two complex numbers.

Output Operator (<<): Allows complex numbers to be printed in the form a + bi.

## 6. Demo.cpp: Code Execution Examples
    
Purpose: Provides a demonstration of how the tree and its iterators work, including a GUI rendering example.

### Key Components:

Tree Creation: Demonstrates creating and populating different trees (binary and ternary).

Iterator Usage: Shows how to use different iterators to traverse and display tree values.

GUI Visualization: Includes an example of how to visualize the tree using the TreeGUI class.

## 7. Tests.cpp: Comprehensive Code Testing

Purpose: Contains unit tests and test cases to verify the correctness and functionality of the tree implementation and its iterators.

### Key Components:

Test Cases: Various test cases for different tree operations, including adding nodes, traversing trees using iterators, and ensuring constraints (like limiting the number of children per node) are respected.

# Libraries Used
### Standard Library:
 Provides basic functionalities such as data structures (std::stack, std::queue, etc.) and I/O operations (iostream).

### SDL2:
 A powerful library for handling graphical output, used here to create a window and render shapes and text.

### SDL2_ttf:
 An SDL extension for rendering text using TrueType fonts, crucial for displaying node values in the GUI.

This structure ensures a clear separation of concerns, with each component handling a specific aspect of the tree's functionality, from basic data representation to advanced GUI visualization and testing.
