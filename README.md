# Tree Data Structure with Iterators

## Overview

This project implements a generic k-ary tree container that supports various types of keys, such as numbers, strings, and custom classes. The default configuration is a binary tree (k = 2), but the number of children per node can be specified during the creation of the tree. The tree supports the following iterators:

- Pre-Order Iterator
- Post-Order Iterator
- In-Order Iterator
- BFS (Breadth-First Search) Iterator
- DFS (Depth-First Search) Iterator
- Heap Iterator

## Features

- **add_root:** Adds a root node to the tree.
- **add_sub_node:** Adds a child node to a given parent node.
- **begin_pre_order / end_pre_order:** Returns iterators for pre-order traversal.
- **begin_post_order / end_post_order:** Returns iterators for post-order traversal.
- **begin_in_order / end_in_order:** Returns iterators for in-order traversal.
- **begin_bfs_scan / end_bfs_scan:** Returns iterators for BFS traversal.
- **begin_dfs_scan / end_dfs_scan:** Returns iterators for DFS traversal.
- **myHeap:** Converts the tree into a binary heap and returns iterators for the heap.
- **Print Function:** Displays the tree structure on the screen using a GUI.

## Class Structure

### Node Class

Represents a node in the tree. Each node can hold a value of any specified type and have up to k children.

### Tree Class

Represents the k-ary tree container with methods to add nodes and traverse the tree using various iterators.

### Iterators

- **PreOrderIterator:** Traverses the tree in pre-order.
- **PostOrderIterator:** Traverses the tree in post-order.
- **InOrderIterator:** Traverses the tree in in-order.
- **BFSIterator:** Traverses the tree in BFS order.
- **DFSIterator:** Traverses the tree in DFS order.
- **HeapIterator:** Traverses the tree as a binary heap.

## Dependencies

- **SFML:** Used for graphical representation of the tree.
- **C++17:** Standard for compiling the code.



