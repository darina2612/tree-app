#pragma once

#include <vector>
#include <memory>

template <typename T>
class Tree
{
public:

    class Node
    {
    public:
        Node() = default;
        Node(const T& value);

        void addChild(const T& value);

    protected:
        T value_;
        std::vector<std::shared_ptr<Node>> childern_;
    };

    using NodePtr = std::shared_ptr<Node>;

    Tree() = default;
    Tree(const T& rootVal);

    void addValue(const T& val);
    //void addValue(const NodePtr& parent, const T& val);

protected:
    NodePtr root_;
};

// Node
template <typename T>
Tree<T>::Node::Node(const T& value) : value_(value)
{
}

template <typename T>
void Tree<T>::Node::addChild(const T& value)
{
    childern_.emplace_back(value);
}

//Tree

template <typename T>
Tree<T>::Tree(const T& rootVal) : root_(rootVal)
{
}

template <typename T>
void Tree<T>::addValue(const T& val)
{
    if(root_ == nullptr)
        root_ = {val};
}

