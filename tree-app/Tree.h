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

        const std::vector<std::shared_ptr<Node>>& getChildren() const;

        const T& getValue() const;
        T& getValue();

//        void doWithChildren(const std::function<void (const std::shared_ptr<Node>&, ...)> f);

//        void doWithChildren(const std::function<void (std::shared_ptr<Node>&, ...)> f);

    protected:
        T value_;
        std::vector<std::shared_ptr<Node>> children_;
    };

    using NodePtr = std::shared_ptr<Node>;
    using NodesList = std::vector<NodePtr>;

    Tree() = default;
    Tree(const T& rootVal);

    void addValue(const T& val);
    //void addValue(const NodePtr& parent, const T& val);

    size_t height() const;

    void getNodesAtLevel(NodesList& nodes, size_t level) const;

protected:

    size_t height(const NodePtr& root) const;

    void getNodesAtLevel(const NodePtr& root, NodesList& nodes, size_t level) const;

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
    children_.emplace_back(value);
}

template <typename T>
const std::vector<typename Tree<T>::NodePtr>& Tree<T>::Node::getChildren() const
{
    return children_;
}

template <typename T>

const T& Tree<T>::Node::getValue() const
{
    return value_;
}

template <typename T>
T& Tree<T>::Node::getValue()
{
    return value_;
}

// TODO : Implement correctly when the knowledge for that is gathered
//template <typename T>
//void Tree<T>::Node::doWithChildren(const std::function<void (const Tree<T>::NodePtr&, ...)> f)
//{
//    for(const auto& child : children_)
//    {
//        f(child, ...);
//    }
//}

//template <typename T>
//void Tree<T>::Node::doWithChildren(const std::function<void (Tree<T>::NodePtr&, ...)> f)
//{
//    for(const auto& child : children)
//    {
//        f(child, ...);
//    }
//}

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

template <typename T>
size_t Tree<T>::height() const
{
    return height(root_);
}

template <typename T>
void Tree<T>::getNodesAtLevel(Tree<T>::NodesList& nodes, size_t level) const
{
    getNodesAtLevel(root_, nodes, level);
}

//Tree - Helpers
template <typename T>
size_t Tree<T>::height(const Tree<T>::NodePtr& root) const
{
    if(root == nullptr)
        return 0;

    size_t maxSubtreeHeight{};

    auto children = root->getChildren();

    for(const auto& child : children)
    {
        maxSubtreeHeight = std::max(maxSubtreeHeight, height(child));
    }

    return  1 + maxSubtreeHeight;
}

template <typename T>
void Tree<T>::getNodesAtLevel(const Tree<T>::NodePtr& root, Tree<T>::NodesList& nodes, size_t level) const
{
    if(root == nullptr)
        return;

    if(level == 0)
    {
        nodes.push_back(root);
        return;
    }

    auto children = root->getChildren();

    for(const auto& child : children)
    {
        getNodesAtLevel(child, nodes, level - 1);
    }
}
