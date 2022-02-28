#pragma once

#include "Command.h"

#include <memory>
#include <vector>

namespace commands {

/**
 * Comand that can execute / undo several other commands, of any type.
 */
class Composite {
public:
    Composite(std::vector<Command>&& commands);

    void execute() const;
    void undo() const;

private:
    std::vector<Command> m_commands;
};

} // namespace commands
