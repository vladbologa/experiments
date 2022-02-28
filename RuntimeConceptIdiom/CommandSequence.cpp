#include "CommandSequence.h"

#include "commands/Command.h"
#include "commands/Composite.h"

void CommandSequence::add(commands::Command&& command)
{
    command.execute();
    redoCommands_.clear();
    uncommitedCommands_.emplace_back(std::move(command));
}

void CommandSequence::commit()
{
    if (!uncommitedCommands_.empty()) {
        if (uncommitedCommands_.size() == 1) {
            commands_.emplace_back(std::move(uncommitedCommands_.back()));
        } else {
            commands_.emplace_back(commands::Composite(std::move(uncommitedCommands_)));
        }
        uncommitedCommands_.clear();
    }
}

void CommandSequence::undo()
{
    commit();
    if (canUndo()) {
        commands_.back().undo();
        redoCommands_.emplace_back(std::move(commands_.back()));
        commands_.pop_back();
    }
}

bool CommandSequence::canUndo() const noexcept
{
    return !(uncommitedCommands_.empty() && commands_.empty());
}

void CommandSequence::redo()
{
    if (canRedo()) {
        redoCommands_.back().execute();
        commands_.emplace_back(std::move(redoCommands_.back()));
        redoCommands_.pop_back();
    }
}

bool CommandSequence::canRedo() const noexcept
{
    return !redoCommands_.empty();
}
