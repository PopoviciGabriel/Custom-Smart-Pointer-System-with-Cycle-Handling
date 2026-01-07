#include "Node.h"
#include <iostream>

int main() {
    SharedPtr<Node> root(new Node());
    SharedPtr<Node> child1(new Node());
    SharedPtr<Node> child2(new Node());

    root->children.push_back(child1);
    child1->parent = root;

    child1->children.push_back(child2);
    child2->parent = child1;

    std::cout << root.use_count() << std::endl;
    std::cout << child1.use_count() << std::endl;
}