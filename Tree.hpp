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


// We define a te
template <typename T, int K = 2>
class Tree {
private:
    Node<T> *root_;

    void drawTree(sf::RenderWindow &window, Node<T> *node, sf::Font &font, float x, float y, float offset, int depth, int maxDepth) {
        if (!node){
            return;
        }

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

        for (size_t i = 0; i < children.size(); ++i){
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

    int calculateMaxDepth(Node<T> *node) {
        if (!node){ 
            return 0;
        }
        int maxDepth = 0;
        for (Node<T> *child : node->getChildren()) {
            int depth = calculateMaxDepth(child);
            if (depth > maxDepth){
                maxDepth = depth;
            }
        }
        return maxDepth + 1;
    }

public:
    Tree() : root_(nullptr) {}
    ~Tree() {}
    void add_root(Node<T> &node) {
        root_ = &node;
    }
    void add_sub_node(Node<T> &parent, Node<T> &child) {
        if (parent.getCurrentChildrenNum() < K) { // check if the current children children less then k
        
            parent.addChild(&child); // Now correctly adds the new node
        }
        else {
            throw std::invalid_argument("Cannot add more children or invalid parent/child.");
        }
    }
    Node<T> *get_root() const {
        return root_;
    }
   

    //*************************************pre order iterator*****************************************************************//
    class PreOrderIterator {
        private:
            std::stack<Node<T> *> stack_; // stack to track the order

        public:
            PreOrderIterator(Node<T> *root){
                // current left right
                if (root){
                    stack_.push(root);
                }
            }

            bool operator!=(const PreOrderIterator &other) const {
                return !(*this == other);
            }

            bool operator==(const PreOrderIterator &other) const {
                return stack_ == other.stack_;
            }

            /* Explanation of the ++ operator, and how it will traverse the tree in pre order:
            *  1. The operator is defined in such a way that if we run it on an empty stack, 
            *     it returns the iterator as is, since there are no more nodes to visit.
            *  2. If the stack is not empty, it pops the top node (which is the current node to visit) 
            *     from the stack and stores it in a variable `current`.
            *  3. It then pushes the children of the current node onto the stack in reverse order (because we want the left children first).
            *     This is done so that when the next iteration happens, the first child of the current node 
            *     (according to pre-order traversal) is on the top of the stack and will be visited next.
            *  4. The iterator then returns itself, now pointing to the next node in the pre-order sequence.
            *  5. The oprator * that we define after this ++ oprator, will return the node that is on the top of the stack, because that's is how we define it.
            * 
            *  In summary, each time the `++` operator is invoked, the iterator moves to the next node
            *  in the tree according to the pre-order traversal, updating the stack accordingly to ensure
            *  the correct traversal order is maintained.
            * 
            *  Comments: 1. we use const to make sure that the iterator is not modified from the outside.
            *            2. We use a reference to the iterator to avoid copying the iterator object, which can be expensive in terms of performance and memory.
            *            3. We use the const to the left because we don't want that the iterator is will change from user that used this operator from outside
            */  
            const PreOrderIterator &operator++() {
                if (stack_.empty()) {
                    return *this;
                }

                Node<T> *current = stack_.top();
                stack_.pop();
                // Push children to the stack in reverse order for correct traversal
                for (auto it = current->getChildren().rbegin(); it != current->getChildren().rend(); ++it) {
                    stack_.push(*it);
                }
                return *this;
            }

            /* Explanation of the * operator, and what it will return, and why:
            *  1. The operator is defined to return the node that is on the top of the stack.
            *  2. This is because we want to return the top node of the stack, which is the current node to visit.
            *  3. If the stack is empty, it throws an exception to indicate that there are no more nodes to visit.
            *  
            *  Comments: 1. We use const to make sure that the iterator is not modified in the process.
            *            2. We return a pointer to the node to avoid copying the node object, which can be expensive in terms of performance and memory.
            *            3. We used the const to the right because we don't want to change the stack during the dereference operation.
            */        
            Node<T> *operator*() const {
                if (stack_.empty()) {
                    throw std::invalid_argument("out of range");
                }
                return stack_.top();
            }
    };
  
    // Method to begin Pre-Order traversal based on K value
    auto begin_pre_order() const {
        if constexpr (K == 2) { // only a binary tree has pre order iterator

            return PreOrderIterator(root_);
        }
        else {
            return DFSIterator(root_); // if not binary return dfs iterator
        }
    }

    // Method to end Pre-Order traversal based on K value
    auto end_pre_order() const{
        if constexpr (K == 2) { // only a binary tree has pre order iterator

            return PreOrderIterator(nullptr);
        }
        else {
            return DFSIterator(nullptr); // if not binary return dfs iterator
        }
    }

    //*************************************post order iterator*****************************************************************//
    class PostOrderIterator {
    // left right current
    private:
        std::stack<Node<T> *> traversalStack_; // Stack to manage traversal order
        std::stack<Node<T> *> outputStack_;    // Stack to hold nodes in post-order

    public:
        /* Explains the constructor of the PostOrderIterator, and how it will traverse the tree in post order:
        *  1. The constructor initializes the iterator with the root node.
        *  2. It first checks if the root node is not null, and if it is not null, it pushes the root node onto the traversal stack.
        *  3. Now the implementation will be little bit different from the pre order iterator, because we need to print it in post order - left right current
        *  4. because the stack is LIFO, we will full the output stack in the opposite order, so we will get the correct order.
        *  5. The oposite order, will be visit, right, left, and that to get the correct order in the output stack.
        * 
        */ 
        PostOrderIterator(Node<T> *root) {
            if (root) {
                traversalStack_.push(root);
                // Traverse the tree and fill the output stack with nodes in post-order
                while (!traversalStack_.empty()) {
                    Node<T> *node = traversalStack_.top();
                    traversalStack_.pop();
                    outputStack_.push(node);
                    // Push all children of the current node to the traversal stack
                    const auto &children = node->getChildren();
                    for (Node<T> *child : children) {
                        traversalStack_.push(child);
                    }
                }
            }
        }

        // Comparison operator to check if iterators are not equal
        bool operator!=(const PostOrderIterator &other) const {
            return !outputStack_.empty();
        }

        /* Explanation of the ++ operator, and how it will traverse the tree in post order:
        *  1. The operator is defined in such a way that if the output stack is not empty, it pops the top node from the stack.
        *  2. This is because the top node of the output stack is the next node to visit in post-order traversal.
        *  3. This is because the output stack was filled with nodes in post-order during the construction of the iterator.
        * 
        *  Comments: 1. We use const to the left because we don't want the iterator to be modified from the outside.
        *            2. We use a reference to the iterator to avoid copying the iterator object, which can be expensive in terms of performance and memory.
        */
        const PostOrderIterator &operator++() {
            if (!outputStack_.empty()) {
                outputStack_.pop();
            }
            return *this;
        }

        /* Explanation of the * operator, and what it will return, and why:
        *  1. The operator is defined to return the node that is on the top of the output stack.
        *  2. This is because the top node of the output stack is the node that in the we to print because we defined it in the constructor.
        * 
        * Comments: 1. We use const to the right make sure that the iterator is not modified in the process.
        *           2. We return a pointer to the node to avoid copying the node object, which can be expensive in terms of performance and memory.
        */
        Node<T> *operator*() const {
            if (outputStack_.empty()) {
                throw std::invalid_argument("out of range");
            }
            return outputStack_.top();
        }
    };

    // Method to begin Post-Order traversal based on K value
    auto begin_post_order() const {
        if constexpr (K == 2) {
            return PostOrderIterator(root_);
        }
        else {
            return DFSIterator(root_);
        }
    }

    // Method to end Post-Order traversal based on K value
    auto end_post_order() const {
        if constexpr (K == 2) {
            return PostOrderIterator(nullptr);
        }
        else {
            return DFSIterator(nullptr);
        }
    }
   
    //*************************************in order iterator*****************************************************************//

    class InOrderIterator {
    private:
        std::stack<Node<T> *> nodeStack_; // Stack to manage traversal
        Node<T> *currentNode_;            // Current node in the traversal

        /* Explanation of the pushLeftmost method, and how it will traverse the tree in in order:
        *  1. The purpose of this method is to push the leftmost node and its descendants onto the stack.
        *  2. The method takes a node as input and pushes the node and all its leftmost descendants onto the stack.
        *  3. It does this by visit the first node that the method received, get the children of the node, and push the first child of the node to the stack.
        *  4. It then continues this process until it reaches a node that has no children, at which point it stops.
        *  5. Hence, if we starting from the root, the nodeStack_ will push the root first to the stack, then the leftmost child of the root, and so on.
        * 
        * 
        */
        void pushLeftmost(Node<T> *node) {
            while (node) {
                nodeStack_.push(node);
                if (!node->getChildren().empty()) {
                    node = node->getChildren().front(); // Push all the way down to the leftmost child
                }
                else {
                    break;
                }
            }
        }

    public:
        // Constructor initializes the iterator with the root node
        InOrderIterator(Node<T> *root) : currentNode_(root){
            pushLeftmost(root);
        }

        // Comparison operator to check if iterators are not equal
        bool operator!=(const InOrderIterator &other) const {
            return !nodeStack_.empty();
        }

        /* Explanation of the ++ operator, and how it will traverse the tree in in order:
        *  Commnet: the built of the nodeStack_ already happened in the constructor, so we don't need to do it again, we just use the stack.
        *  1. The operator is defined in such a way that if the stack is not empty, it pops the top node from the stack.
        *  2. Now, because the In - order traversal is left, visit, right, after we push the leftmost node, we will push the father of the leftmost node, and then the right child of the father.
        *  3. The implementation work in that way:
        *  3. a. We will push the leftmost node
        *  3. b. We will pop the leftmost node to update the nodeStack_ to enable that the next node will be the father of the leftmost node.
        *  3. c. We will look now for the leftmost node of the right child of the father of the leftmost node, and push it to the stack.
        *  4. When we finish push all the leftmost nodes of the right child of the father of the leftmost node, the opertaor will return the update iterator.
        * 
        *  Comments: 1. We use const to the left because we don't want the iterator to be modified from the outside.
        *            2. We use a reference to the iterator to avoid copying the iterator object, which can be expensive in terms of performance and memory.
        */
        const InOrderIterator &operator++() {
            if (!nodeStack_.empty()) {
                Node<T> *topNode = nodeStack_.top();
                nodeStack_.pop();
                const auto &children = topNode->getChildren();
                // For k-ary, push the second child and its leftmost descendants
                if (children.size() > 1) {
                    pushLeftmost(children[1]);
                }
            }
            return *this;
        }

        // Dereference operator to access the current node
        Node<T> *operator*() const {
            if (nodeStack_.empty()) {
                throw std::invalid_argument("out of range");
            }
            return nodeStack_.top();
        }
    };

    // Method to begin In-Order traversal based on K value
    auto begin_in_order() const {
        if constexpr (K == 2) {
            return InOrderIterator(root_);
        }
        else {
            return DFSIterator(root_);
        }
    }

    // Method to end In-Order traversal based on K value
    auto end_in_order() const {
        if constexpr (K == 2){
            return InOrderIterator(nullptr); // End iterator with empty stack
        }
        else {
            return DFSIterator(nullptr);
        }
    }

    //*************************************BFS iterator*****************************************************************//

    class BFSIterator {
    private:
        // Unlike the other classes, this class will work with a queue and not with a stack
        std::queue<Node<T> *> nodeQueue; // Queue to manage BFS traversal order

    public:
        /* Explanation of the constructor of the BFSIterator:
        *  1. The constructor initializes the iterator with the root node.
        */
        BFSIterator(Node<T> *root) {
            if (root) {
                nodeQueue.push(root);
            }
        }

        // Comparison operator to check if iterators are not equal
        bool operator!=(const BFSIterator &other) const {
            return !nodeQueue.empty();
        }

        /* Explanation of the ++ operator, and how it will traverse the tree in BFS order:
        *  1. The operator is defined in such a way that if the queue is not empty, it dequeues the front node from the queue.
        *  2. We will push all the children of the current node to the queue
        *  3. In this way, the next node to visit will be or the node that next to the current node to the right, or the node that is the child of the current node.
        *  4. 
        */
        const BFSIterator &operator++() {
            if (!nodeQueue.empty()) {
                Node<T> *current = nodeQueue.front();
                nodeQueue.pop();
                // Enqueue all children of the current node
                for (Node<T> *child : current->getChildren()) {
                    nodeQueue.push(child);
                }
            }
            return *this;
        }

        // Dereference operator to access the current node
        Node<T> *operator*() const {
            if (nodeQueue.empty()) {
                throw std::invalid_argument("out of range");
            }
            return nodeQueue.front();
        }
    };

    // Method to begin BFS traversal - we use that in the built heap
    BFSIterator begin() const {
        return begin_bfs_scan();
    }

    // Method to end BFS traversal - we use that in the built heap
    BFSIterator end() const {
        return end_bfs_scan();
    }
   
    // Method to begin BFS traversal
    BFSIterator begin_bfs_scan() const {
        return BFSIterator(root_);
    }
   
    // Method to end BFS traversal
    BFSIterator end_bfs_scan() const {
        return BFSIterator(nullptr); // End iterator with empty queue
    }

    //*************************************DFS iterator*****************************************************************//
    class DFSIterator {
    private:
        std::stack<Node<T> *> nodeStack_; // Stack to manage DFS traversal order

    public:
        // Constructor initializes the iterator with the root node
        // we will use the pre order traversal to implement this DFS iterator
        DFSIterator(Node<T> *root) {
            if (root) {
                nodeStack_.push(root);
            }
        }

        // Comparison operator to check if iterators are not equal
        bool operator!=(const DFSIterator &other) const {
            return !nodeStack_.empty();
        }

        /* Explanation of the ++ operator, and how it will traverse the tree in DFS order:
        *  1. The operator is defined in such a way that if the stack is not empty, it pops the top node from the stack.
        *  2. It then pushes the children of the current node onto the stack in reverse order, for correct DFS traversal - because we want to visit the left child first.
        *  3. This is done so that when the next iteration happens, the first child of the current node (according to DFS traversal) is on the top of the stack and will be visited next.
        */
        const DFSIterator &operator++() {
            if (!nodeStack_.empty()) {
                Node<T> *current = nodeStack_.top();
                nodeStack_.pop();
                // Push children of the current node onto the stack in reverse order
                for (auto it = current->getChildren().rbegin(); it != current->getChildren().rend(); ++it) {
                    nodeStack_.push(*it);
                }
            }
            return *this;
        }

        // Dereference operator to access the current node
        Node<T> *operator*() const
        {
            if (nodeStack_.empty()) {
                throw std::invalid_argument("out of range");
            }
            return nodeStack_.top();
        }
    };

    // Method to begin DFS traversal
    DFSIterator begin_dfs_scan() const {
        return DFSIterator(root_);
    }

    // Method to end DFS traversal
    DFSIterator end_dfs_scan() const {
        return DFSIterator(nullptr); // End iterator with empty stack
    }

    //*************************************heap iterator*****************************************************************//
    class HeapIterator{
    private:
        std::vector<Node<T> *> heap_;
        size_t currentIndex_;

    public:
        // Constructor initializes the iterator with the root node
        HeapIterator(Node<T> *root) : currentIndex_(0) {
            if (root) {
                buildHeap(root);
            }
        }
        // Helper function to build a min-heap from the tree
        void buildHeap(Node<T> *root) {
            std::queue<Node<T> *> nodeQueue;
            if (root) {
                nodeQueue.push(root);
            }
            while (!nodeQueue.empty()) {
                Node<T> *current = nodeQueue.front();
                nodeQueue.pop();
                heap_.push_back(current);
                for (Node<T> *child : current->getChildren()) {
                    nodeQueue.push(child);
                }
            }
            // Use std::make_heap to build the min-heap based on node values
            std::make_heap(heap_.begin(), heap_.end(), [](Node<T> *a, Node<T> *b) {
                return a->getValue() > b->getValue();
            });
        }
        // Comparison operator to check if iterators are not equal
        bool operator!=(const HeapIterator &other) const {
        return currentIndex_ != other.currentIndex_;
    }
        // Method to get the size of the heap
        int getSize() {
            return heap_.size();
        }
        // Method to set the current index of the iterator
        void setCurrentIndex(int index) {
            currentIndex_ = index;
        }
 
        // Pre-increment operator to move to the next node in heap order
        const HeapIterator &operator++() {
            if (currentIndex_ < heap_.size()) {
                ++currentIndex_;
            }
        return *this;
        }
        // Dereference operator to access the current node
        Node<T> *operator*() const {
        if (heap_.empty() || currentIndex_ >= heap_.size()) {
            throw std::invalid_argument("out of range");
        }
        return heap_[currentIndex_];
    }
    };

    // Method to begin Heap traversal
    HeapIterator myHeap() {
        if (K == 2) {
            if (!root_) {
                throw std::logic_error("no nodes in tree");
            }

            std::vector<Node<T> *> nodes;
            std::queue<Node<T> *> q;
            q.push(root_);

            // Traverse the tree and store nodes in a vector
            while (!q.empty()) {
                Node<T> *current = q.front();
                q.pop();
                nodes.push_back(current);

                // Enqueue all children of the current node
                for (Node<T> *child : current->getChildren()) {
                    q.push(child);
                }
            }

            // Transform the vector into a min-heap based on node values
            std::make_heap(nodes.begin(), nodes.end(), [](Node<T> *a, Node<T> *b) {
                return a->getValue() > b->getValue();
            });

            // Rebuild the tree structure based on the heap
            for (size_t i = 0; i < nodes.size(); ++i) {
                size_t leftChildIndex = 2 * i + 1;
                size_t rightChildIndex = 2 * i + 2;

                nodes[i]->clearChildren();
                if (leftChildIndex < nodes.size()) {
                    nodes[i]->addChild(nodes[leftChildIndex]);
                }
                if (rightChildIndex < nodes.size()) {
                    nodes[i]->addChild(nodes[rightChildIndex]);
                }
            }

            root_ = nodes.empty() ? nullptr : nodes.front();
        }
        else {
            throw std::logic_error("not a binary tree");
        }
        return HeapIterator(root_);
    }

    HeapIterator begin_heap() {
        return HeapIterator(root_);
    }

    HeapIterator end_heap() {
        HeapIterator it(root_);
        it.setCurrentIndex(it.getSize()); // Set to the size of the heap to indicate end
        return it;
    }



    /* Explanation of why I chose to implement the visualize method in the Tree.hpp file and not as a separate class:
    *  1. It can access the private members of the tree class, without the need to define the tree class as a friend class, 
    *     which makes calling the function easier and prevents possible errors.
    *  2. In cases where the tree template might change (e.g., when implementing a different type of tree), 
    *     the visualize function remains naturally tied to the tree class and does not depend on a different template, 
    *     allowing it to be implemented in a customized way for each different tree.
    *  3. The simplicity of calling the function:
    *     Calling the function from within the class itself, like myTree.visualize(), is simpler and clearer, 
    *     making the code more convenient to use and maintain.
    */


    void visualize() {
        sf::RenderWindow window(sf::VideoMode(1200, 800), "Tree Visualization");
        sf::Font font;

        // Load the font from a file
        if (!font.loadFromFile("Arimo-Italic-VariableFont_wght.ttf")) {
            std::cerr << "Error loading font" << std::endl;
            return;
        }

        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed){
                    window.close();
                }
            }

            window.clear(sf::Color::White);
            int maxDepth = calculateMaxDepth(root_);
            drawTree(window, root_, font, window.getSize().x / 2, 20, window.getSize().x / 4, 0, maxDepth);
            window.display();
        }
    }


};




#endif