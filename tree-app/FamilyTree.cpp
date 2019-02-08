#include "FamilyTree.h"

void FamilyTree::draw(Drawer& drawer)
{
    draw(root_, drawer);
}

// Helpers
void FamilyTree::draw(const NodePtr& root, Drawer& drawer)
{
    if(root == nullptr)
        return;

    root->getValue().draw(drawer);

    root->doWithChildren([this, &drawer](const auto& child)
    {
        draw(child, drawer);
    });
}

