#pragma once
#include <string>
#include <vector>
#include "SmartPtr.h"

struct Node
{
    std::string name;
    std::vector<SharedPtr<Node>> children;
    WeakPtr<Node> parent;
    ~Node() {}
};