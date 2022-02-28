#pragma once

#include <memory>

namespace commands {

// Concept that must be implemented by the types that
// are used together with the Command class
template <typename T>
concept CommandConcept = requires(T c)
{
    c.execute();
    c.undo();
};

/**
 * Undoable / readoable command
 *
 * Uses the runtime concept idiom to implement the command
 * design pattern
 *
 * Types passed to the constructor of Command *must* implement
 * the CommandConcept defined above.
 */
class Command {
public:
    template <typename T>
    Command(T x)
        : self_(std::make_unique<CommandWrapper<T>>(std::move(x)))
    {
    }

    Command(Command&&) noexcept = default;
    Command& operator=(Command&&) noexcept = default;

    void execute() const
    {
        self_->execute_();
    }

    void undo() const
    {
        self_->undo_();
    }

private:
    struct ConceptT {
        virtual ~ConceptT() = default;
        virtual void execute_() const = 0;
        virtual void undo_() const = 0;
    };

    template <CommandConcept T>
    struct CommandWrapper final : ConceptT {
        CommandWrapper(T x)
            : command_(std::move(x))
        {
        }
        void execute_() const override { command_.execute(); }
        void undo_() const override { command_.undo(); }
        T command_;
    };

    std::unique_ptr<ConceptT> self_;
};

} // namespace commands
