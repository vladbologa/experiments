#pragma once

#include "DrawableObject.h"
#include "commands/Common.h"
#include "commands/Command.h"

#include <memory>
#include <vector>

using Commands = std::vector<commands::Command>;

/**
 * Stores a sequence of commands, that can be undone and redone
 *
 * An undo point is created by calling commit(). To make every
 * command undoable, commit() must be called after every add().
 */
class CommandSequence {
public:
    // Adds a command to the sequence and executes it.
    void add(commands::Command&& command);

    // Commits any unsaved state changes (i.e., commands)
    // Does nothing if there are no pending commands
    void commit();

    // Undoes commands, until the previous commit point
    void undo();

    // Returns true if undo() can be called
    bool canUndo() const noexcept;

    // Redoes the most recently undone command group
    void redo();

    // Returns true if redo() can be called
    bool canRedo() const noexcept;

private:
    Commands m_uncommitedCommands;
    Commands m_commands;
    Commands m_redoCommands;
};
