#include "Composite.h"

namespace commands {

Composite::Composite(std::vector<Command>&& commands)
    : commands_(std::move(commands))
{
}
void Composite::execute() const
{
    for (const auto& command : commands_) {
        command.execute();
    }
}

void Composite::undo() const
{
    for (auto it = rbegin(commands_); it != rend(commands_); ++it) {
        (*it).undo();
    }
}

} // namespace commands
