#pragma once

#include <vector>
#include <memory>
#include <algorithm>

class NodeChangeObserver
{
public:
    virtual void nodeChanged() = 0;
    virtual ~NodeChangeObserver() = default;
};

template <typename T>
class Tree : public NodeChangeObserver
{
public:

    class Node
    {
    public:
        Node() = default;
        Node(const T& value);

        void addChild(const T& value);

        const std::vector<std::shared_ptr<Node>>& getChildren() const;
        std::vector<std::shared_ptr<Node>>& getChildren();

        const T& getValue() const;
        T& getValue();

        void doWithChildren(const std::function<void (const std::shared_ptr<Node>&)> f) const;
        void doWithChildren(const std::function<void (std::shared_ptr<Node>&)> f);

        bool removeChild(const std::function<bool (const std::shared_ptr<Node>&)> pred);

        void setObserver(NodeChangeObserver* observer);

    protected:

        void notifyForChange();

        T value_;
        std::vector<std::shared_ptr<Node>> children_;

        NodeChangeObserver* changeObserver_;
    };

    using NodePtr = std::shared_ptr<Node>;
    using NodesList = std::vector<NodePtr>;

    Tree() = default;
    Tree(const T& rootVal);

    void addValue(const T& val);
    //void addValue(const NodePtr& parent, const T& val);

    size_t height() const;

    void getNodesAtLevel(NodesList& nodes, size_t level) const;

    NodePtr getRoot();

    void nodeChanged() override;

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
    children_.emplace_back(std::make_shared<Node>(value));
    children_.back()->setObserver(changeObserver_);
    notifyForChange();
}

template <typename T>
const std::vector<typename Tree<T>::NodePtr>& Tree<T>::Node::getChildren() const
{
    return children_;
}

template <typename T>
std::vector<typename Tree<T>::NodePtr>& Tree<T>::Node::getChildren()
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

template <typename T>
void Tree<T>::Node::doWithChildren(const std::function<void (const std::shared_ptr<Node>&)> f) const
{
    for(const auto& child : children_)
    {
        f(child);
    }
}

template <typename T>
void Tree<T>::Node::doWithChildren(const std::function<void (std::shared_ptr<Node>&)> f)
{
    for(auto& child : children_)
    {
        f(child);
    }
}

template <typename T>
bool Tree<T>::Node::removeChild(const std::function<bool (const std::shared_ptr<Node>&)> pred)
{
    auto it = std::find_if(children_.begin(), children_.end(), pred);

    if(it != children_.end())
    {
        children_.erase(it);
        return true;
    }
    return false;
}

template <typename T>
void Tree<T>::Node::setObserver(NodeChangeObserver* observer)
{
    changeObserver_ = observer;
}

template <typename T>
void Tree<T>::Node::notifyForChange()
{
    if(changeObserver_ != nullptr)
        changeObserver_->nodeChanged();
}


//Tree
template <typename T>
Tree<T>::Tree(const T& rootVal) : root_(std::make_shared<Node>(rootVal))
{
    root_->setObserver(this);
}

template <typename T>
void Tree<T>::addValue(const T& val)
{
    if(root_ == nullptr)
    {
        root_ = std::make_shared<Tree<T>::Node>(val);
        root_->setObserver(this);
    }
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

template <typename T>
typename Tree<T>::NodePtr Tree<T>::getRoot()
{
    return root_;
}

template <typename T>
void Tree<T>::nodeChanged()
{
}

//Tree - Helpers
template <typename T>
size_t Tree<T>::height(const Tree<T>::NodePtr& root) const
{
    if(root == nullptr)
        return 0;

    size_t maxSubtreeHeight{};

    root->doWithChildren([&maxSubtreeHeight, this](const auto& child)
    {
        maxSubtreeHeight = std::max(maxSubtreeHeight, height(child));
    });

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

    root->doWithChildren([&nodes, level, this](const auto& child)
    {
        getNodesAtLevel(child, nodes, level - 1);
    });
}
