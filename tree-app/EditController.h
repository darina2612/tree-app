#pragma once

#include <stack>
#include <Command.h>

class EditController
{
public:
    EditController() = default;

    void addCommand(const CommandPtr& command, bool execute = true);

    void undo();
    void redo();

private:
    std::stack<CommandPtr> undo_stack_;
    std::stack<CommandPtr> redo_stack_;
};
