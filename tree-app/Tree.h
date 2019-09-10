#pragma once

#include <vector>
#include <memory>
#include <iostream>
#include <algorithm>
#include "SerializationUtils.h"

class NodeChangeObserver
{
public:
    virtual void nodeChanged() = 0;
    virtual ~NodeChangeObserver() = default;
};

template<typename T>
class NodeIdProvider
{
public:
    virtual T getNextId() = 0;
    virtual ~NodeIdProvider() = default;
};

template <typename ValueType, typename ElementIdType>
class Tree : public NodeChangeObserver, public NodeIdProvider<ElementIdType>
{
public:

    class Node
    {
    public:
        Node() = default;
        Node(const ValueType& value);

        void addChild(const ValueType& value);

        const std::vector<std::shared_ptr<Node>>& getChildren() const;
        std::vector<std::shared_ptr<Node>>& getChildren();

        const ValueType& getValue() const;
        ValueType& getValue();

        void doWithChildren(const std::function<void (const std::shared_ptr<Node>&)> f) const;
        void doWithChildren(const std::function<void (std::shared_ptr<Node>&)> f);

        bool removeChild(const std::function<bool (const std::shared_ptr<Node>&)> pred);

        void setObserver(NodeChangeObserver* observer);
        void setIdProvider(NodeIdProvider<ElementIdType>* idProvider);

        ElementIdType getId() const;
        void setId(ElementIdType id);

        void serialize(std::ostream& os) const;
        void deserialize(std::istream& is);

    protected:

        void notifyForChange();

        ElementIdType id_;
        ValueType value_;
        std::vector<std::shared_ptr<Node>> children_;

        NodeChangeObserver* changeObserver_;
        NodeIdProvider<ElementIdType>* idProvider_;
    };

    using NodePtr = std::shared_ptr<Node>;
    using NodesList = std::vector<NodePtr>;

    Tree() = default;
    Tree(const ValueType& rootVal);

    void addValue(const ValueType& val);
    //void addValue(const NodePtr& parent, const T& val);

    size_t height() const;

    void getNodesAtLevel(NodesList& nodes, size_t level) const;

    NodePtr getRoot();

    void nodeChanged() override;

    virtual void serialize(std::ostream& os) const;
    virtual void deserialize(std::istream& is);

protected:

    size_t height(const NodePtr& root) const;

    void getNodesAtLevel(const NodePtr& root, NodesList& nodes, size_t level) const;

    NodePtr root_;
};

// Node
template <typename ValueType, typename ElementIdType>
Tree<ValueType, ElementIdType>::Node::Node(const ValueType& value) : value_(value)
{
}

template <typename ValueType, typename ElementIdType>
void Tree<ValueType, ElementIdType>::Node::addChild(const ValueType& value)
{
    children_.emplace_back(std::make_shared<Node>(value));
    children_.back()->setObserver(changeObserver_);
    children_.back()->setIdProvider(idProvider_);
    if(idProvider_ != nullptr)
        children_.back()->setId(idProvider_->getNextId());
    notifyForChange();
}

template <typename ValueType, typename ElementIdType>
const std::vector<typename Tree<ValueType, ElementIdType>::NodePtr>& Tree<ValueType, ElementIdType>::Node::getChildren() const
{
    return children_;
}

template <typename ValueType, typename ElementIdType>
std::vector<typename Tree<ValueType, ElementIdType>::NodePtr>& Tree<ValueType, ElementIdType>::Node::getChildren()
{
    return children_;
}


template <typename ValueType, typename ElementIdType>

const ValueType& Tree<ValueType, ElementIdType>::Node::getValue() const
{
    return value_;
}

template <typename ValueType, typename ElementIdType>
ValueType& Tree<ValueType, ElementIdType>::Node::getValue()
{
    return value_;
}

template <typename ValueType, typename ElementIdType>
void Tree<ValueType, ElementIdType>::Node::doWithChildren(const std::function<void (const std::shared_ptr<Node>&)> f) const
{
    for(const auto& child : children_)
    {
        f(child);
    }
}

template <typename ValueType, typename ElementIdType>
void Tree<ValueType, ElementIdType>::Node::doWithChildren(const std::function<void (std::shared_ptr<Node>&)> f)
{
    for(auto& child : children_)
    {
        f(child);
    }
}

template <typename ValueType, typename ElementIdType>
bool Tree<ValueType, ElementIdType>::Node::removeChild(const std::function<bool (const std::shared_ptr<Node>&)> pred)
{
    auto it = std::find_if(children_.begin(), children_.end(), pred);

    if(it != children_.end())
    {
        children_.erase(it);
        return true;
    }
    return false;
}

template <typename ValueType, typename ElementIdType>
void Tree<ValueType, ElementIdType>::Node::setObserver(NodeChangeObserver* observer)
{
    changeObserver_ = observer;
}

template <typename ValueType, typename ElementIdType>
void Tree<ValueType, ElementIdType>::Node::setIdProvider(NodeIdProvider<ElementIdType>* idProvider)
{
    idProvider_ = idProvider;
}

template <typename ValueType, typename ElementIdType>
ElementIdType Tree<ValueType, ElementIdType>::Node::getId() const
{
    return id_;
}

template <typename ValueType, typename ElementIdType>
void Tree<ValueType, ElementIdType>::Node::setId(ElementIdType id)
{
    id_ = id;
}

template <typename ValueType, typename ElementIdType>
void Tree<ValueType, ElementIdType>::Node::serialize(std::ostream& os) const
{
    Serialization::serialize(os, id_);
    Serialization::serialize(os, value_);
    Serialization::serialize(os, children_);
}

template <typename ValueType, typename ElementIdType>
void Tree<ValueType, ElementIdType>::Node::deserialize(std::istream& is)
{
    Deserialization::deserialize(is, id_);
    Deserialization::deserialize(is, value_);
    Deserialization::deserialize(is, children_);
}

template <typename ValueType, typename ElementIdType>
void Tree<ValueType, ElementIdType>::Node::notifyForChange()
{
    if(changeObserver_ != nullptr)
        changeObserver_->nodeChanged();
}


//Tree
template <typename ValueType, typename ElementIdType>
Tree<ValueType, ElementIdType>::Tree(const ValueType& rootVal) : root_(std::make_shared<Node>(rootVal))
{
    root_->setObserver(this);
    root_->setIdProvider(this);
}

template <typename ValueType, typename ElementIdType>
void Tree<ValueType, ElementIdType>::addValue(const ValueType& val)
{
    if(root_ == nullptr)
    {
        root_ = std::make_shared<Tree<ValueType, ElementIdType>::Node>(val);
        root_->setObserver(this);
    }
}

template <typename ValueType, typename ElementIdType>
size_t Tree<ValueType, ElementIdType>::height() const
{
    return height(root_);
}

template <typename ValueType, typename ElementIdType>
void Tree<ValueType, ElementIdType>::getNodesAtLevel(Tree<ValueType, ElementIdType>::NodesList& nodes, size_t level) const
{
    getNodesAtLevel(root_, nodes, level);
}

template <typename ValueType, typename ElementIdType>
typename Tree<ValueType, ElementIdType>::NodePtr Tree<ValueType, ElementIdType>::getRoot()
{
    return root_;
}

template <typename ValueType, typename ElementIdType>
void Tree<ValueType, ElementIdType>::nodeChanged()
{
}

template <typename ValueType, typename ElementIdType>
void Tree<ValueType, ElementIdType>::serialize(std::ostream& os) const
{
    Serialization::serialize(os, root_);
}

template <typename ValueType, typename ElementIdType>
void Tree<ValueType, ElementIdType>::deserialize(std::istream& is)
{
    Deserialization::deserialize(is, root_);
}

//Tree - Helpers
template <typename ValueType, typename ElementIdType>
size_t Tree<ValueType, ElementIdType>::height(const Tree<ValueType, ElementIdType>::NodePtr& root) const
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

template <typename ValueType, typename ElementIdType>
void Tree<ValueType, ElementIdType>::getNodesAtLevel(const Tree<ValueType, ElementIdType>::NodePtr& root,
                                                     Tree<ValueType, ElementIdType>::NodesList& nodes,
                                                     size_t level) const
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
