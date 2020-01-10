#include "EditController.h"

void EditController::addCommand(const CommandPtr& command, bool execute)
{
    undo_stack_.push(command);
    std::stack<CommandPtr>().swap(redo_stack_);
    if(execute)
        undo_stack_.top()->redo();
}

void EditController::undo()
{
    if(undo_stack_.empty())
        return;

    auto& command = undo_stack_.top();
    command->undo();
    redo_stack_.push(command);
    undo_stack_.pop();
}

void EditController::redo()
{
    if(redo_stack_.empty())
        return;

    auto& command = redo_stack_.top();
    command->redo();
    undo_stack_.push(command);
    redo_stack_.pop();
}
