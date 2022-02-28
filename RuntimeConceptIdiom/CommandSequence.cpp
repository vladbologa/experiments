#include "CommandSequence.h"

#include "commands/Composite.h"
#include "commands/Command.h"

void CommandSequence::add(commands::Command&& command)
{
    command.execute();
    m_redoCommands.clear();
    m_uncommitedCommands.emplace_back(std::move(command));
}

void CommandSequence::commit()
{
    if (!m_uncommitedCommands.empty()) {
        if (m_uncommitedCommands.size() == 1) {
            m_commands.emplace_back(std::move(m_uncommitedCommands.back()));
        } else {
            m_commands.emplace_back(commands::Composite(std::move(m_uncommitedCommands)));
        }
        m_uncommitedCommands.clear();
    }
}

void CommandSequence::undo()
{
    commit();
    if (canUndo()) {
        m_commands.back().undo();
        m_redoCommands.emplace_back(std::move(m_commands.back()));
        m_commands.pop_back();
    }
}

bool CommandSequence::canUndo() const noexcept
{
    return !(m_uncommitedCommands.empty() && m_commands.empty());
}

void CommandSequence::redo()
{
    if (canRedo()) {
        m_redoCommands.back().execute();
        m_commands.emplace_back(std::move(m_redoCommands.back()));
        m_redoCommands.pop_back();
    }
}

bool CommandSequence::canRedo() const noexcept
{
    return !m_redoCommands.empty();
}
