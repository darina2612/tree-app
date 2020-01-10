#include "DeleteCommand.h"

#include <cassert>

DeleteCommand::DeleteCommand(FamilyTreePtr tree,
                             const PositionInfo<FamilyTreeIdType>& positionInfo) :
    tree_(std::move(tree)), positionInfo_(positionInfo)
{

}

void DeleteCommand::undo()
{
    tree_->addSubtree(subtreeCopy_, positionInfo_);
    subtreeCopy_.reset();
}

void DeleteCommand::redo()
{
    if(tree_ == nullptr)
    {
        assert(false);
        return;
    }

    const auto& parentNode = positionInfo_.parentId_ == -1 ? tree_->getRoot() : tree_->getNode(positionInfo_.parentId_);

    FamilyTree::NodePtr node;

    if(positionInfo_.parentId_ != -1)
    {
        const auto& children = parentNode->getChildren();

        if(positionInfo_.prevElementId_ == -1)
        {
            node = children.front();
        }
        else
        {
            auto it = std::find_if(children.begin(), children.end(),
                                   [this](const auto& child)
            {
                return child->getId() == positionInfo_.prevElementId_;
            });

            if(it != children.end())
                node = *(++it);
            else
                assert(false);
        }
    }
    else
    {
        node = parentNode;
    }

    subtreeCopy_ = node->getPtr();

    tree_->removeNodeWithId(node->getId());
}
