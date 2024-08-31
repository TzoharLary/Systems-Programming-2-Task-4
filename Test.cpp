// ID: 207492315
// Email: Tzohary1234@gmail.com
#include "Tree.hpp"
#include "Node.hpp"
#include "doctest.h"
#include "Complex.hpp"
#include <string>
using namespace std;

TEST_CASE("String")
{
    SUBCASE("k=2")
    {
        Node<string> root_node("a"); // k=2
        Tree<string> tree;           // Binary tree that contains strings.
        tree.add_root(root_node);
        Node<string> n_b("b");
        Node<string> n_c("c");
        Node<string> n_d("d");
        Node<string> n_e("e");
        Node<string> n_f("f");

        tree.add_sub_node(root_node, n_b);
        tree.add_sub_node(root_node, n_c);
        tree.add_sub_node(n_b, n_d);
        tree.add_sub_node(n_b, n_e);
        tree.add_sub_node(n_c, n_f);
        CHECK(tree.get_root()->getChildren().at(0)->getValue() == n_b.getValue());
        CHECK(tree.get_root()->getChildren().at(1)->getValue() == n_c.getValue());
        CHECK(n_b.getChildren().at(0)->getValue() == n_d.getValue());
        CHECK(n_b.getChildren().at(1)->getValue() == n_e.getValue());
        CHECK(n_c.getChildren().at(0)->getValue() == n_f.getValue());
        Node<string> n_g("g");
        CHECK_THROWS_WITH(tree.add_sub_node(n_b, n_g), "Cannot add more children or invalid parent/child.");

        SUBCASE("PreOrderIterator")
        {
            std::vector<string> expected = {"a", "b", "d", "e", "c", "f"};
            auto it = expected.begin();
            for (auto node = tree.begin_pre_order(); node != tree.end_pre_order(); ++node)
            {
                CHECK((*node)->getValue() == *it++);
            }
        }

        SUBCASE("PostOrderIterator")
        {
            std::vector<string> expected = {"d", "e", "b", "f", "c", "a"};
            auto it = expected.begin();
            for (auto node = tree.begin_post_order(); node != tree.end_post_order(); ++node)
            {
                CHECK((*node)->getValue() == *it++);
            }
        }

        SUBCASE("InOrderIterator")
        {
            std::vector<string> expected = {"d", "b", "e", "a", "f", "c"};
            auto it = expected.begin();
            for (auto node = tree.begin_in_order(); node != tree.end_in_order(); ++node)
            {
                CHECK((*node)->getValue() == *it++);
            }
        }

        SUBCASE("BFSIterator")
        {
            std::vector<string> expected = {"a", "b", "c", "d", "e", "f"};
            auto it = expected.begin();
            for (auto node = tree.begin_bfs_scan(); node != tree.end_bfs_scan(); ++node)
            {
                CHECK((*node)->getValue() == *it++);
            }
        }

        SUBCASE("DFSIterator")
        {
            std::vector<string> expected = {"a", "b", "d", "e", "c", "f"};
            auto it = expected.begin();
            for (auto node = tree.begin_dfs_scan(); node != tree.end_dfs_scan(); ++node)
            {
                CHECK((*node)->getValue() == *it++);
            }
        }

        SUBCASE("HeapIterator")
        {
            // Convert tree to heap and test the order
            tree.myHeap();
             std::vector<string> expected = {"a", "b", "c", "d", "e", "f"};
             auto it = expected.begin();
             auto node = tree.begin_heap();
            for (node = tree.begin_heap(); node != tree.end_heap(); ++node)
             {
                 CHECK((*node)->getValue() == *it++);
             }
        }

        SUBCASE("errors")
        {
            Tree<string> tree;
            auto it = tree.begin();
            CHECK_THROWS_WITH(*it, "out of range");
        }
    }

    SUBCASE("k=3")
    {
        Node<string> root_node("a"); // k=3
        Tree<string, 3> tree;        // 3-ary tree that contains strings.
        tree.add_root(root_node);
        Node<string> n_b("b");
        Node<string> n_c("c");
        Node<string> n_d("d");
        Node<string> n_e("e");
        Node<string> n_f("f");

        tree.add_sub_node(root_node, n_b);
        tree.add_sub_node(root_node, n_c);
        tree.add_sub_node(root_node, n_d);
        tree.add_sub_node(n_b, n_e);
        tree.add_sub_node(n_c, n_f);
        CHECK(tree.get_root()->getChildren().at(0)->getValue() == n_b.getValue());
        CHECK(tree.get_root()->getChildren().at(1)->getValue() == n_c.getValue());
        CHECK(tree.get_root()->getChildren().at(2)->getValue() == n_d.getValue());
        CHECK(n_b.getChildren().at(0)->getValue() == n_e.getValue());
        CHECK(n_c.getChildren().at(0)->getValue() == n_f.getValue());

        SUBCASE("PreOrderIterator")
        {
            std::vector<string> expected = {"a", "b", "e", "c", "f", "d"};
            auto it = expected.begin();
            for (auto node = tree.begin_pre_order(); node != tree.end_pre_order(); ++node)
            {
                CHECK((*node)->getValue() == *it++);
            }
        }

        SUBCASE("PostOrderIterator")
        {
            std::vector<string> expected = {"a", "b", "e", "c", "f", "d"};
            auto it = expected.begin();
            for (auto node = tree.begin_post_order(); node != tree.end_post_order(); ++node)
            {
                CHECK((*node)->getValue() == *it++);
            } // 1 2 5 3 6 4
            // a b  e c f  d
        }

        SUBCASE("InOrderIterator")
        {
            std::vector<string> expected = {"a", "b", "e", "c", "f", "d"};
            auto it = expected.begin();
            for (auto node = tree.begin_in_order(); node != tree.end_in_order(); ++node)
            {
                CHECK((*node)->getValue() == *it++);
            }
        }

        SUBCASE("BFSIterator")
        {
            std::vector<string> expected = {"a", "b", "c", "d", "e", "f"};
            auto it = expected.begin();
            for (auto node = tree.begin_bfs_scan(); node != tree.end_bfs_scan(); ++node)
            {
                CHECK((*node)->getValue() == *it++);
            }
        }

        SUBCASE("DFSIterator")
        {
            std::vector<string> expected = {"a", "b", "e", "c", "f", "d"};
            auto it = expected.begin();
            for (auto node = tree.begin_dfs_scan(); node != tree.end_dfs_scan(); ++node)
            {
                CHECK((*node)->getValue() == *it++);
            }
        }

        SUBCASE("HeapIterator")
        {

            CHECK_THROWS_WITH(tree.myHeap(), "not a binary tree");
        }

        SUBCASE("errors")
        {
            Tree<string> tree;
            auto it = tree.begin_bfs_scan();
            CHECK_THROWS_WITH(*it, "out of range");
        }
    }
}

TEST_CASE("double")
{
    SUBCASE("k=2")
    {
        Node<double> root_node(1.1); // k=2
        Tree<double> tree;           // Binary tree that contains doubles.
        tree.add_root(root_node);
        Node<double> n_b(1.2);
        Node<double> n_c(1.3);
        Node<double> n_d(1.4);
        Node<double> n_e(1.5);
        Node<double> n_f(1.6);
        tree.add_sub_node(root_node, n_b);
        tree.add_sub_node(root_node, n_c);
        tree.add_sub_node(n_b, n_d);
        tree.add_sub_node(n_b, n_e);
        tree.add_sub_node(n_c, n_f);
        CHECK(tree.get_root()->getChildren().at(0)->getValue() == n_b.getValue());
        CHECK(tree.get_root()->getChildren().at(1)->getValue() == n_c.getValue());
        CHECK(n_b.getChildren().at(0)->getValue() == n_d.getValue());
        CHECK(n_b.getChildren().at(1)->getValue() == n_e.getValue());
        CHECK(n_c.getChildren().at(0)->getValue() == n_f.getValue());
        Node<double> n_g(1.7);
        CHECK_THROWS_WITH(tree.add_sub_node(n_b, n_g), "Cannot add more children or invalid parent/child.");

        SUBCASE("PreOrderIterator")
        {
            std::vector<double> expected = {1.1, 1.2, 1.4, 1.5, 1.3, 1.6};
            auto it = expected.begin();
            for (auto node = tree.begin_pre_order(); node != tree.end_pre_order(); ++node)
            {
                CHECK((*node)->getValue() == *it++);
            }
        }

        SUBCASE("PostOrderIterator")
        {
            std::vector<double> expected = {1.4, 1.5, 1.2, 1.6, 1.3, 1.1};
            auto it = expected.begin();
            for (auto node = tree.begin_post_order(); node != tree.end_post_order(); ++node)
            {
                CHECK((*node)->getValue() == *it++);
            }
        }

        SUBCASE("InOrderIterator")
        {
            std::vector<double> expected = {1.4, 1.2, 1.5, 1.1, 1.6, 1.3};
            auto it = expected.begin();
            for (auto node = tree.begin_in_order(); node != tree.end_in_order(); ++node)
            {
                CHECK((*node)->getValue() == *it++);
            }
        }

        SUBCASE("BFSIterator")
        {
            std::vector<double> expected = {1.1, 1.2, 1.3, 1.4, 1.5, 1.6};
            auto it = expected.begin();
            for (auto node = tree.begin_bfs_scan(); node != tree.end_bfs_scan(); ++node)
            {
                CHECK((*node)->getValue() == *it++);
            }
        }

        SUBCASE("DFSIterator")
        {
            std::vector<double> expected = {1.1, 1.2, 1.4, 1.5, 1.3, 1.6};
            auto it = expected.begin();
            for (auto node = tree.begin_dfs_scan(); node != tree.end_dfs_scan(); ++node)
            {
                CHECK((*node)->getValue() == *it++);
            }
        }

        SUBCASE("HeapIterator")
        {
            // Convert tree to heap and test the order
            tree.myHeap();
            std::vector<double> expected = {1.1, 1.2, 1.3, 1.4, 1.5, 1.6};
            auto it = expected.begin();
            for (auto node = tree.begin_heap(); node != tree.end_heap(); ++node)
            {
                CHECK((*node)->getValue() == *it++);
            }
        }

        SUBCASE("errors")
        {
            Tree<string> tree;
            auto it = tree.begin_dfs_scan();
            CHECK_THROWS_WITH(*it, "out of range");
        }
    }

    SUBCASE("k=3")
    {
        Node<double> root_node(1.1); // k=3
        Tree<double, 3> tree;        // 3-ary tree that contains doubles.
        tree.add_root(root_node);
        Node<double> n_b(1.2);
        Node<double> n_c(1.3);
        Node<double> n_d(1.4);
        Node<double> n_e(1.5);
        Node<double> n_f(1.6);

        tree.add_sub_node(root_node, n_b);
        tree.add_sub_node(root_node, n_c);
        tree.add_sub_node(root_node, n_d);
        tree.add_sub_node(n_b, n_e);
        tree.add_sub_node(n_c, n_f);
        CHECK(tree.get_root()->getChildren().at(0)->getValue() == n_b.getValue());
        CHECK(tree.get_root()->getChildren().at(1)->getValue() == n_c.getValue());
        CHECK(tree.get_root()->getChildren().at(2)->getValue() == n_d.getValue());
        CHECK(n_b.getChildren().at(0)->getValue() == n_e.getValue());
        CHECK(n_c.getChildren().at(0)->getValue() == n_f.getValue());

        SUBCASE("PreOrderIterator")
        {
            std::vector<double> expected = {1.1, 1.2, 1.5, 1.3, 1.6, 1.4};
            auto it = expected.begin();
            for (auto node = tree.begin_pre_order(); node != tree.end_pre_order(); ++node)
            {
                CHECK((*node)->getValue() == *it++);
            }
        }

        SUBCASE("PostOrderIterator")
        {
            std::vector<double> expected = {1.1, 1.2, 1.5, 1.3, 1.6, 1.4};
            auto it = expected.begin();
            for (auto node = tree.begin_post_order(); node != tree.end_post_order(); ++node)
            {
                CHECK((*node)->getValue() == *it++);
            }
        }

        SUBCASE("InOrderIterator")
        {
            std::vector<double> expected = {1.1, 1.2, 1.5, 1.3, 1.6, 1.4};
            auto it = expected.begin();
            for (auto node = tree.begin_in_order(); node != tree.end_in_order(); ++node)
            {
                CHECK((*node)->getValue() == *it++);
            }
        }

        SUBCASE("BFSIterator")
        {
            std::vector<double> expected = {1.1, 1.2, 1.3, 1.4, 1.5, 1.6};
            auto it = expected.begin();
            for (auto node = tree.begin_bfs_scan(); node != tree.end_bfs_scan(); ++node)
            {
                CHECK((*node)->getValue() == *it++);
            }
        }

        SUBCASE("DFSIterator")
        {
            std::vector<double> expected = {1.1, 1.2, 1.5, 1.3, 1.6, 1.4};
            auto it = expected.begin();
            for (auto node = tree.begin_dfs_scan(); node != tree.end_dfs_scan(); ++node)
            {
                CHECK((*node)->getValue() == *it++);
            }
        }

        SUBCASE("HeapIterator")
        {
            CHECK_THROWS_WITH(tree.myHeap(), "not a binary tree");
        }

        SUBCASE("errors")
        {
            Tree<string> tree;
            auto it = tree.begin_heap();
            CHECK_THROWS_WITH(*it, "out of range");
        }
    }
}

TEST_CASE("Complex")
{
    SUBCASE("k=2")
    {
        Node<Complex> root_node(Complex(1, 1)); // k=2
        Tree<Complex> tree;                     // Binary tree that contains Complex numbers.
        tree.add_root(root_node);
        Node<Complex> n_b(Complex(2, 2));
        Node<Complex> n_c(Complex(3, 3));
        Node<Complex> n_d(Complex(4, 4));
        Node<Complex> n_e(Complex(5, 5));
        Node<Complex> n_f(Complex(6, 6));

        tree.add_sub_node(root_node, n_b);
        tree.add_sub_node(root_node, n_c);
        tree.add_sub_node(n_b, n_d);
        tree.add_sub_node(n_b, n_e);
        tree.add_sub_node(n_c, n_f);
        CHECK(tree.get_root()->getChildren().at(0)->getValue() == n_b.getValue());
        CHECK(tree.get_root()->getChildren().at(1)->getValue() == n_c.getValue());
        CHECK(n_b.getChildren().at(0)->getValue() == n_d.getValue());
        CHECK(n_b.getChildren().at(1)->getValue() == n_e.getValue());
        CHECK(n_c.getChildren().at(0)->getValue() == n_f.getValue());

        SUBCASE("PreOrderIterator")
        {
            std::vector<Complex> expected = {Complex(1, 1), Complex(2, 2), Complex(4, 4), Complex(5, 5), Complex(3, 3), Complex(6, 6)};
            auto it = expected.begin();
            for (auto node = tree.begin_pre_order(); node != tree.end_pre_order(); ++node)
            {
                CHECK((*node)->getValue() == *it++);
            }
        }

        SUBCASE("PostOrderIterator")
        {
            std::vector<Complex> expected = {Complex(4, 4), Complex(5, 5), Complex(2, 2), Complex(6, 6), Complex(3, 3), Complex(1, 1)};
            auto it = expected.begin();
            for (auto node = tree.begin_post_order(); node != tree.end_post_order(); ++node)
            {
                CHECK((*node)->getValue() == *it++);
            }
        }

        SUBCASE("InOrderIterator")
        {
            std::vector<Complex> expected = {Complex(4, 4), Complex(2, 2), Complex(5, 5), Complex(1, 1), Complex(6, 6), Complex(3, 3)};
            auto it = expected.begin();
            for (auto node = tree.begin_in_order(); node != tree.end_in_order(); ++node)
            {
                CHECK((*node)->getValue() == *it++);
            }
        }

        SUBCASE("BFSIterator")
        {
            std::vector<Complex> expected = {Complex(1, 1), Complex(2, 2), Complex(3, 3), Complex(4, 4), Complex(5, 5), Complex(6, 6)};
            auto it = expected.begin();
            for (auto node = tree.begin_bfs_scan(); node != tree.end_bfs_scan(); ++node)
            {
                CHECK((*node)->getValue() == *it++);
            }
        }

        SUBCASE("DFSIterator")
        {
            std::vector<Complex> expected = {Complex(1, 1), Complex(2, 2), Complex(4, 4), Complex(5, 5), Complex(3, 3), Complex(6, 6)};
            auto it = expected.begin();
            for (auto node = tree.begin_dfs_scan(); node != tree.end_dfs_scan(); ++node)
            {
                CHECK((*node)->getValue() == *it++);
            }
        }

        SUBCASE("HeapIterator")
        {
            // Convert tree to heap and test the order
            tree.myHeap();
            std::vector<Complex> expected = {Complex(1, 1), Complex(2, 2), Complex(3, 3), Complex(4, 4), Complex(5, 5), Complex(6, 6)};
            auto it = expected.begin();
            for (auto node = tree.begin_heap(); node != tree.end_heap(); ++node)
            {
                CHECK((*node)->getValue() == *it++);
            }
        }

        SUBCASE("errors")
        {
            Tree<string> tree;
            auto it = tree.begin_post_order();
            CHECK_THROWS_WITH(*it, "out of range");
        }
    }

    SUBCASE("k=3")
    {
        Node<Complex> root_node(Complex(1, 1)); // k=3
        Tree<Complex, 3> tree;                  // 3-ary tree that contains Complex numbers.
        tree.add_root(root_node);
        Node<Complex> n_b(Complex(2, 2));
        Node<Complex> n_c(Complex(3, 3));
        Node<Complex> n_d(Complex(4, 4));
        Node<Complex> n_e(Complex(5, 5));
        Node<Complex> n_f(Complex(6, 6));

        tree.add_sub_node(root_node, n_b);
        tree.add_sub_node(root_node, n_c);
        tree.add_sub_node(root_node, n_d);
        tree.add_sub_node(n_b, n_e);
        tree.add_sub_node(n_c, n_f);
        CHECK(tree.get_root()->getChildren().at(0)->getValue() == n_b.getValue());
        CHECK(tree.get_root()->getChildren().at(1)->getValue() == n_c.getValue());
        CHECK(tree.get_root()->getChildren().at(2)->getValue() == n_d.getValue());
        CHECK(n_b.getChildren().at(0)->getValue() == n_e.getValue());
        CHECK(n_c.getChildren().at(0)->getValue() == n_f.getValue());

        SUBCASE("PreOrderIterator")
        {
            std::vector<Complex> expected = {Complex(1, 1), Complex(2, 2), Complex(5, 5), Complex(3, 3), Complex(6, 6), Complex(4, 4)};
            auto it = expected.begin();
            for (auto node = tree.begin_pre_order(); node != tree.end_pre_order(); ++node)
            {
                CHECK((*node)->getValue() == *it++);
            }
        }

        SUBCASE("PostOrderIterator")
        {
            std::vector<Complex> expected = {Complex(1, 1), Complex(2, 2), Complex(5, 5), Complex(3, 3), Complex(6, 6), Complex(4, 4)};
            auto it = expected.begin();
            for (auto node = tree.begin_post_order(); node != tree.end_post_order(); ++node)
            {
                CHECK((*node)->getValue() == *it++);
            }
        }

        SUBCASE("InOrderIterator")
        {
            std::vector<Complex> expected = {Complex(1, 1), Complex(2, 2), Complex(5, 5), Complex(3, 3), Complex(6, 6), Complex(4, 4)};
            auto it = expected.begin();
            for (auto node = tree.begin_in_order(); node != tree.end_in_order(); ++node)
            {
                CHECK((*node)->getValue() == *it++);
            }
        }

        SUBCASE("BFSIterator")
        {
            std::vector<Complex> expected = {Complex(1, 1), Complex(2, 2), Complex(3, 3), Complex(4, 4), Complex(5, 5), Complex(6, 6)};
            auto it = expected.begin();
            for (auto node = tree.begin_bfs_scan(); node != tree.end_bfs_scan(); ++node)
            {
                CHECK((*node)->getValue() == *it++);
            }
        }

        SUBCASE("DFSIterator")
        {
            std::vector<Complex> expected = {Complex(1, 1), Complex(2, 2), Complex(5, 5), Complex(3, 3), Complex(6, 6), Complex(4, 4)};
            auto it = expected.begin();
            for (auto node = tree.begin_dfs_scan(); node != tree.end_dfs_scan(); ++node)
            {
                CHECK((*node)->getValue() == *it++);
            }
        }

        SUBCASE("HeapIterator")
        {
            CHECK_THROWS_WITH(tree.myHeap(), "not a binary tree");
        }

        SUBCASE("errors")
        {
            Tree<string> tree;
            auto it = tree.begin_pre_order();
            CHECK_THROWS_WITH(*it, "out of range");
        }
    }
}
