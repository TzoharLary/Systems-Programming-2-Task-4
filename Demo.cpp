// ID: 207492315
// Email: Tzohary1234@gmail.com
#include <iostream>
#include <string>
#include "Node.hpp"
#include "Tree.hpp"
#include "Complex.hpp"
using namespace std;

int main()
{

    Node<int> root_node(0);
    Tree<int> tree; // Binary tree that contains doubles.
    tree.add_root(root_node);
    Node<int> n1(1);
    Node<int> n2(2);
    Node<int> n3 (3);
    Node<int> n4(4);
    Node<int> n5(5);
    
 

    tree.add_sub_node(root_node, n1);
    tree.add_sub_node(root_node, n2);
    tree.add_sub_node(n1, n3);
    tree.add_sub_node(n2, n4);
    tree.add_sub_node(n2, n5);
    

    // The tree should look like:
    /**
     *       root = 1.1
     *     /       \
     *    1.2      1.3
     *   /  \      /
     *  1.4  1.5  1.6
     */

    for (auto node = tree.begin_pre_order(); node != tree.end_pre_order(); ++node)
    {
        cout << (*node)->getValue() << " ";
    } // prints: 1.1, 1.2, 1.4, 1.5, 1.3, 1.6
    cout << endl;
    for (auto node = tree.begin_post_order(); node != tree.end_post_order(); ++node)
    {
        cout << (*node)->getValue() << " ";
    } // prints: 1.4, 1.5, 1.2, 1.6, 1.3, 1.1
    cout << endl;
    for (auto node = tree.begin_in_order(); node != tree.end_in_order(); ++node)
    {
        cout << (*node)->getValue() << " ";
    } // prints: 1.4, 1.2, 1.5, 1.1, 1.6, 1.3
    cout << endl;
    for (auto node = tree.begin_bfs_scan(); node != tree.end_bfs_scan(); ++node)
    {
        cout << (*node)->getValue() << " ";
    } // prints: 1.1, 1.2, 1.3, 1.4, 1.5, 1.6
    cout << endl;
    for (auto node = tree.begin_dfs_scan(); node != tree.end_dfs_scan(); ++node)
    {
        cout << (*node)->getValue() << " ";
    } // prints: 1.1, 1.2, 1.4, 1.5, 1.3, 1.6
    cout << endl;
    for (auto node : tree)
    {
        cout << node->getValue() << " ";
    } // same as BFS: 1.1, 1.2, 1.3, 1.4, 1.5, 1.6
    cout << endl;
    tree.myHeap();
    cout << "Heap" << endl;
    for (auto node = tree.begin_heap(); node != tree.end_heap(); ++node)
    {
        std::cout << (*node)->getValue() << " ";
    }
    std::cout <<std::endl;

   tree.visualize();
//     Node<double> root_node2(1.1);
//     Tree<double, 3> tree2; // Binary tree that contains doubles.
//     tree2.add_root(root_node2);

//     Node<double> n22(1.2);
//     Node<double> n23(1.3);
//     Node<double> n24(1.4);
//     Node<double> n25(1.5);
//     Node<double> n26(1.6);
//     Node<double> n27(1.7);
//     Node<double> n28(1.8);
//     Node<double> n29(1.9);
    // Node<double> n30(2.0);
    // Node<double> n31(2.1);
    // Node<double> n32(2.2);
    // Node<double> n33(1.8);
    // Node<double> n34(1.9);
    // Node<double> n35(2.0);
    // Node<double> n36(2.1);
    // Node<double> n37(2.2);

    // tree2.add_sub_node(root_node2, n22);
    // tree2.add_sub_node(root_node2, n23);
    // tree2.add_sub_node(root_node2, n24);
    // tree2.add_sub_node(n22, n25);
    // tree2.add_sub_node(n22, n26);
    // tree2.add_sub_node(n22, n27);
    // tree2.add_sub_node(n23, n28);
    // tree2.add_sub_node(n24, n29);
    // tree2.add_sub_node(n25, n30);
    // tree2.add_sub_node(n25, n31);
    // tree2.add_sub_node(n25, n32);
    // tree2.add_sub_node(n32, n33);
    // tree2.add_sub_node(n32, n34);
    // tree2.add_sub_node(n32, n35);
    // tree2.add_sub_node(n35, n36);
    // tree2.add_sub_node(n35, n37);

//     // Pre-order traversal
//     std::cout << "Pre-order: \n";
//     for (auto node = tree2.begin_pre_order(); node != tree2.end_pre_order(); ++node)
//     {
//         std::cout << (*node)->getValue() << " ";
//     }
//     std::cout << std::endl;

//     // Post-order traversal
//     std::cout << "Post-order: \n";
//     for (auto node = tree2.begin_post_order(); node != tree2.end_post_order(); ++node)
//     {
//         std::cout << (*node)->getValue() << " ";
//     }
//     std::cout << std::endl;

//     // In-order traversal
//     std::cout << "In-order: \n";
//     for (auto node = tree2.begin_in_order(); node != tree2.end_in_order(); ++node)
//     {
//         std::cout << (*node)->getValue() << " ";
//     }
//     std::cout << std::endl;

//     // BFS traversal
//     std::cout << "BFS: \n";
//     for (auto node = tree2.begin_bfs_scan(); node != tree2.end_bfs_scan(); ++node)
//     {
//         std::cout << (*node)->getValue() << " ";
//     }
//     std::cout << std::endl;

//     // DFS traversal
//     std::cout << "DFS: \n";
//     for (auto node = tree2.begin_dfs_scan(); node != tree2.end_dfs_scan(); ++node)
//     {
//         std::cout << (*node)->getValue() << " ";
//     }
//     std::cout << std::endl;

//     // Default traversal (if implemented)
//     std::cout << "Default: \n";
//     for (auto node : tree2)
//     {
//         std::cout << node->getValue() << " ";
//     }
//     std::cout << std::endl;

//     // Heap traversal (if implemented)
//     std::cout << "Heap: \n";
//     for (auto node = tree2.begin_heap(); node != tree2.end_heap(); ++node)
//     {
//         std::cout << (*node)->getValue() << " ";
//     }
//     std::cout << std::endl;
//     tree2.visualize();
    // The tree should look like:
    /**
     *       root = 1.1
     *     /      |     \
     *    1.2    1.3    1.4
     *   /        |
     *  1.5      1.6
     */
}