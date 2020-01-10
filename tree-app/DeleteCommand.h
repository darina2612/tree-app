#pragma once

#include "Command.h"
#include "FamilyTree.h"
#include "PositionInfo.h"

class DeleteCommand : public Command
{
public:
    DeleteCommand(FamilyTreePtr tree, const PositionInfo<FamilyTreeIdType>& positionInfo);

    void undo() override;
    void redo() override;

private:
    FamilyTreePtr tree_;
    PositionInfo<FamilyTreeIdType> positionInfo_;
    FamilyTree::NodePtr subtreeCopy_;
};

