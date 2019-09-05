#pragma once

#include <memory>

class Command
{
public:
    virtual void undo() = 0;
    virtual void redo() = 0;
};

using CommandPtr = std::shared_ptr<Command>;
