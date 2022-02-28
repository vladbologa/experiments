#include "Composite.h"

namespace commands {

Composite::Composite(std::vector<Command>&& commands)
    : m_commands(std::move(commands))
{
}
void Composite::execute() const
{
    for (const auto& command : m_commands) {
        command.execute();
    }
}

void Composite::undo() const
{
    for (auto it = rbegin(m_commands); it != rend(m_commands); ++it) {
        (*it).undo();
    }
}

} // namespace commands
