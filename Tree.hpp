// ID: 207492315
// Email: Tzohary1234@gmail.com
#ifndef TREE_HPP
#define TREE_HPP
#include "Node.hpp"
#include <vector>
#include <queue>
#include <stack>
#include <utility>
#include <iostream>
#include "Node.hpp"
#include <SFML/Graphics.hpp>
#include <algorithm>
#include <sstream>

template <typename T, int K = 2>
class Tree
{
private:
    Node<T> *root_;

    void drawTree(sf::RenderWindow &window, Node<T> *node, sf::Font &font, float x, float y, float offset, int depth, int maxDepth)
    {
        if (!node)
            return;

        // Draw the node (circle)
        sf::CircleShape circle(20);
        circle.setFillColor(sf::Color::Cyan);
        circle.setPosition(x, y);

        std::stringstream ss;
        ss.precision(2);
        ss << std::fixed << node->getValue();
        std::string valueStr = ss.str();

        // Draw the node value (text)
        sf::Text text;
        text.setFont(font);
        text.setString(valueStr);
        text.setCharacterSize(15);
        text.setFillColor(sf::Color::Black);
        sf::FloatRect textRect = text.getLocalBounds();
        text.setOrigin(textRect.left + textRect.width / 2.0f,
                       textRect.top + textRect.height / 2.0f);
        text.setPosition(x + circle.getRadius(), y + circle.getRadius());

        window.draw(circle);
        window.draw(text);

        // Draw lines and recursively draw children
        const std::vector<Node<T> *> &children = node->getChildren();
        float childOffset = offset / 2;
        float verticalSpacing = 600.0 / (maxDepth + 1);

        for (size_t i = 0; i < children.size(); ++i)
        {
            float childX = x + (i - (children.size() - 1) / 2.0) * offset;
            float childY = y + verticalSpacing;

            sf::Vertex line[] =
                {
                    sf::Vertex(sf::Vector2f(x + 20, y + 20), sf::Color::Cyan),
                    sf::Vertex(sf::Vector2f(childX + 20, childY), sf::Color::Cyan)};

            window.draw(line, 2, sf::Lines);
            drawTree(window, children[i], font, childX, childY, childOffset, depth + 1, maxDepth);
        }
    }

    int calculateMaxDepth(Node<T> *node)
    {
        if (!node)
            return 0;
        int maxDepth = 0;
        for (Node<T> *child : node->getChildren())
        {
            int depth = calculateMaxDepth(child);
            if (depth > maxDepth)
                maxDepth = depth;
        }
        return maxDepth + 1;
    }

public:
    Tree() : root_(nullptr) {}
    ~Tree() {}
    void add_root(Node<T> &node)
    {
        root_ = &node;
    }
    void add_sub_node(Node<T> &parent, Node<T> &child)
    {
        if (parent.getCurrentChildrenNum() < K) // check if the current children children less then k
        {
            parent.addChild(&child); // Now correctly adds the new node
        }
        else
        {
            throw std::invalid_argument("Cannot add more children or invalid parent/child.");
        }
    }
    Node<T> *get_root() const
    {
        return root_;
    }
    // void print()
    // {
    //     root_->print();
    // }

    //*************************************pre order iterator*****************************************************************//
    class PreOrderIterator
    {
    private:
        std::stack<Node<T> *> stack_; // stack to track the order

    public:
        PreOrderIterator(Node<T> *root)
        // current left right
        {
            if (root)
                stack_.push(root);
        }

        bool operator!=(const PreOrderIterator &other) const
        {
            return !(*this == other);
        }

        bool operator==(const PreOrderIterator &other) const
        {
            return stack_ == other.stack_;
        }

        const PreOrderIterator &operator++()
        {
            if (stack_.empty())
            {
                return *this;
            }

            Node<T> *current = stack_.top();
            stack_.pop();
            // Push children to the stack in reverse order for correct traversal
            for (auto it = current->getChildren().rbegin(); it != current->getChildren().rend(); ++it)
            {
                stack_.push(*it);
            }
            return *this;
        }

        Node<T> *operator*() const
        {
            if (stack_.empty())
            {
                throw std::invalid_argument("out of range");
            }
            return stack_.top();
        }
    };
    auto begin_pre_order() const
    {
        if constexpr (K == 2) // only a binary tree has pre order iterator
        {
            return PreOrderIterator(root_);
        }
        else
        {
            return DFSIterator(root_); // if not binary return dfs iterator
        }
    }

//Method to end Pre-Order traversal based on K value
    auto end_pre_order() const
    {
        if constexpr (K == 2) // only a binary tree has pre order iterator
        {
            return PreOrderIterator(nullptr);
        }
        else
        {
            return DFSIterator(nullptr); // if not binary return dfs iterator
        }
    }

    //*************************************post order iterator*****************************************************************//
    class PostOrderIterator
    {
        // left right current
    private:
        std::stack<Node<T> *> traversalStack_; // Stack to manage traversal order
        std::stack<Node<T> *> outputStack_;    // Stack to hold nodes in post-order

    public:
        // Constructor initializes the iterator with the root node
        PostOrderIterator(Node<T> *root)
        {
            if (root)
            {
                traversalStack_.push(root);
                // Traverse the tree and fill the output stack with nodes in post-order
                while (!traversalStack_.empty())
                {
                    Node<T> *node = traversalStack_.top();
                    traversalStack_.pop();
                    outputStack_.push(node);
                    // Push all children of the current node to the traversal stack
                    const auto &children = node->getChildren();
                    for (Node<T> *child : children)
                    {
                        traversalStack_.push(child);
                    }
                }
            }
        }

        // Comparison operator to check if iterators are not equal
        bool operator!=(const PostOrderIterator &other) const
        {
            return !outputStack_.empty();
        }

        // Pre-increment operator to move to the next node in post-order
        const PostOrderIterator &operator++()
        {
            if (!outputStack_.empty())
            {
                outputStack_.pop();
            }
            return *this;
        }

        // Dereference operator to access the current node
        Node<T> *operator*() const
        {
            if (outputStack_.empty())
            {
                throw std::invalid_argument("out of range");
            }
            return outputStack_.top();
        }
    };

    // Method to begin Post-Order traversal based on K value
    auto begin_post_order() const
    {
        if constexpr (K == 2)
        {
            return PostOrderIterator(root_);
        }
        else
        {
            return DFSIterator(root_);
        }
    }

    // Method to end Post-Order traversal based on K value
    auto end_post_order() const
    {
        if constexpr (K == 2)
        {
            return PostOrderIterator(nullptr);
        }
        else
        {
            return DFSIterator(nullptr);
        }
    }
    //*************************************in order iterator*****************************************************************//

    class InOrderIterator
    {
    private:
        std::stack<Node<T> *> nodeStack_; // Stack to manage traversal
        Node<T> *currentNode_;            // Current node in the traversal

        // Helper function to push the leftmost nodes of the subtree
        void pushLeftmost(Node<T> *node)
        {
            while (node)
            {
                nodeStack_.push(node);
                if (!node->getChildren().empty())
                {
                    node = node->getChildren().front(); // Push all the way down to the leftmost child
                }
                else
                {
                    break;
                }
            }
        }

    public:
        // Constructor initializes the iterator with the root node
        InOrderIterator(Node<T> *root) : currentNode_(root)
        {
            pushLeftmost(root);
        }

        // Comparison operator to check if iterators are not equal
        bool operator!=(const InOrderIterator &other) const
        {
            return !nodeStack_.empty();
        }

        // Pre-increment operator to move to the next node in in-order
        const InOrderIterator &operator++()
        {
            if (!nodeStack_.empty())
            {
                Node<T> *topNode = nodeStack_.top();
                nodeStack_.pop();
                const auto &children = topNode->getChildren();
                // For k-ary, push the second child and its leftmost descendants
                if (children.size() > 1)
                {
                    pushLeftmost(children[1]);
                }
            }
            return *this;
        }

        // Dereference operator to access the current node
        Node<T> *operator*() const
        {
            if (nodeStack_.empty())
            {
                throw std::invalid_argument("out of range");
            }
            return nodeStack_.top();
        }
    };

    // Method to begin In-Order traversal based on K value
    auto begin_in_order() const
    {
        if constexpr (K == 2)
        {
            return InOrderIterator(root_);
        }
        else
        {
            return DFSIterator(root_);
        }
    }

    // Method to end In-Order traversal based on K value
    auto end_in_order() const
    {
        if constexpr (K == 2)
        {
            return InOrderIterator(nullptr); // End iterator with empty stack
        }
        else
        {
            return DFSIterator(nullptr);
        }
    }

    //*************************************BFS iterator*****************************************************************//

    class BFSIterator
    {
    private:
        std::queue<Node<T> *> nodeQueue; // Queue to manage BFS traversal order

    public:
        // Constructor initializes the iterator with the root node
        BFSIterator(Node<T> *root)
        {
            if (root)
            {
                nodeQueue.push(root);
            }
        }

        // Comparison operator to check if iterators are not equal
        bool operator!=(const BFSIterator &other) const
        {
            return !nodeQueue.empty();
        }

        // Pre-increment operator to move to the next node in BFS order
        const BFSIterator &operator++()
        {
            if (!nodeQueue.empty())
            {
                Node<T> *current = nodeQueue.front();
                nodeQueue.pop();
                // Enqueue all children of the current node
                for (Node<T> *child : current->getChildren())
                {
                    nodeQueue.push(child);
                }
            }
            return *this;
        }

        // Dereference operator to access the current node
        Node<T> *operator*() const
        {
            if (nodeQueue.empty())
            {
                throw std::invalid_argument("out of range");
            }
            return nodeQueue.front();
        }
    };

    // Method to begin BFS traversal
    BFSIterator begin() const
    {
        return begin_bfs_scan();
    }

    // Method to end BFS traversal
    BFSIterator end() const
    {
        return end_bfs_scan();
    }
    BFSIterator begin_bfs_scan() const
    {
        return BFSIterator(root_);
    }

    BFSIterator end_bfs_scan() const
    {
        return BFSIterator(nullptr); // End iterator with empty queue
    }

    //*************************************DFS iterator*****************************************************************//
    class DFSIterator
    {
    private:
        std::stack<Node<T> *> nodeStack_; // Stack to manage DFS traversal order

    public:
        // Constructor initializes the iterator with the root node
        DFSIterator(Node<T> *root)
        {
            if (root)
            {
                nodeStack_.push(root);
            }
        }

        // Comparison operator to check if iterators are not equal
        bool operator!=(const DFSIterator &other) const
        {
            return !nodeStack_.empty();
        }

        // Pre-increment operator to move to the next node in DFS order
        const DFSIterator &operator++()
        {
            if (!nodeStack_.empty())
            {
                Node<T> *current = nodeStack_.top();
                nodeStack_.pop();
                // Push children of the current node onto the stack in reverse order
                for (auto it = current->getChildren().rbegin(); it != current->getChildren().rend(); ++it)
                {
                    nodeStack_.push(*it);
                }
            }
            return *this;
        }

        // Dereference operator to access the current node
        Node<T> *operator*() const
        {
            if (nodeStack_.empty())
            {
                throw std::invalid_argument("out of range");
            }
            return nodeStack_.top();
        }
    };

    // Method to begin DFS traversal
    DFSIterator begin_dfs_scan() const
    {
        return DFSIterator(root_);
    }

    // Method to end DFS traversal
    DFSIterator end_dfs_scan() const
    {
        return DFSIterator(nullptr); // End iterator with empty stack
    }

    //*************************************heap iterator*****************************************************************//
    class HeapIterator
{
private:
    std::vector<Node<T> *> heap_;
    size_t currentIndex_;

public:
    HeapIterator(Node<T> *root) : currentIndex_(0)
    {
        if (root)
        {
            buildHeap(root);
        }
    }
    void buildHeap(Node<T> *root)
    {
        std::queue<Node<T> *> nodeQueue;
        if (root)
        {
            nodeQueue.push(root);
        }
        while (!nodeQueue.empty())
        {
            Node<T> *current = nodeQueue.front();
            nodeQueue.pop();
            heap_.push_back(current);
            for (Node<T> *child : current->getChildren())
            {
                nodeQueue.push(child);
            }
        }
        // Use std::less to create a min-heap
        std::make_heap(heap_.begin(), heap_.end(), [](Node<T> *a, Node<T> *b) {
            return a->getValue() > b->getValue();
        });
    }

   bool operator!=(const HeapIterator &other) const
{
    return currentIndex_ != other.currentIndex_;
}

    int getSize()
    {
        return heap_.size();
    }

    void setCurrentIndex(int index)
    {
        currentIndex_ = index;
    }

// const HeapIterator &operator++()
// {
//     if (currentIndex_ < heap_.size())
//     {
//         std::pop_heap(heap_.begin(), heap_.end() - currentIndex_, [](Node<T> *a, Node<T> *b) {
//             return a->getValue() > b->getValue();
//         });
//         ++currentIndex_;
//     }
//     return *this;
// }

    const HeapIterator &operator++()
    {
        if (currentIndex_ < heap_.size())
        {
            ++currentIndex_;
        }
    return *this;
    }

Node<T> *operator*() const
{
    if (heap_.empty() || currentIndex_ >= heap_.size())
    {
        throw std::invalid_argument("out of range");
    }
    return heap_[currentIndex_];
}
};



HeapIterator myHeap()
{
    if (K == 2)
    {
        if (!root_)
        {
            throw std::logic_error("no nodes in tree");
        }

        std::vector<Node<T> *> nodes;
        std::queue<Node<T> *> q;
        q.push(root_);

        // Traverse the tree and store nodes in a vector
        while (!q.empty())
        {
            Node<T> *current = q.front();
            q.pop();
            nodes.push_back(current);

            // Enqueue all children of the current node
            for (Node<T> *child : current->getChildren())
            {
                q.push(child);
            }
        }

        // Transform the vector into a min-heap based on node values
        std::make_heap(nodes.begin(), nodes.end(), [](Node<T> *a, Node<T> *b) {
            return a->getValue() > b->getValue();
        });

        // Rebuild the tree structure based on the heap
        for (size_t i = 0; i < nodes.size(); ++i)
        {
            size_t leftChildIndex = 2 * i + 1;
            size_t rightChildIndex = 2 * i + 2;

            nodes[i]->clearChildren();
            if (leftChildIndex < nodes.size())
            {
                nodes[i]->addChild(nodes[leftChildIndex]);
            }
            if (rightChildIndex < nodes.size())
            {
                nodes[i]->addChild(nodes[rightChildIndex]);
            }
        }

        root_ = nodes.empty() ? nullptr : nodes.front();
    }
    else
    {
        throw std::logic_error("not a binary tree");
    }
    return HeapIterator(root_);
}

    HeapIterator begin_heap()
    {
        return HeapIterator(root_);
    }

HeapIterator end_heap()
{
    HeapIterator it(root_);
    it.setCurrentIndex(it.getSize()); // Set to the size of the heap to indicate end
    return it;
}


    // Default iterator for range-based for loops (BFS)

    void visualize()
    {
        sf::RenderWindow window(sf::VideoMode(1200, 800), "Tree Visualization");
        sf::Font font;

        // Load the font from a file
        if (!font.loadFromFile("Arimo-Italic-VariableFont_wght.ttf"))
        {
            std::cerr << "Error loading font" << std::endl;
            return;
        }

        while (window.isOpen())
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
            }

            window.clear(sf::Color::White);
            int maxDepth = calculateMaxDepth(root_);
            drawTree(window, root_, font, window.getSize().x / 2, 20, window.getSize().x / 4, 0, maxDepth);
            window.display();
        }
    }
};

#endif