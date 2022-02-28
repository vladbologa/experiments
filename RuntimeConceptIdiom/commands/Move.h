#pragma once

#include "../DrawableObject.h"
#include "Common.h"

#include <memory>

namespace commands {

using GetterFunc = std::function<DrawableObject&(const Id&)>;

/**
 * Command that moves objects to a new position
 */
class Move {
public:
    Move(const Id& id, const Position& position, const GetterFunc& getterFunc);
    Move(const Id& id, const Position& startPosition, const Position& oldPosition, const GetterFunc& getterFunc);

    Move(Move&&) = default;

    void execute() const;
    void undo() const;

private:
    Id m_id;
    Position m_newPosition;
    Position m_oldPosition;
    GetterFunc m_drawableObjectGetter;
};

} // namespace commands
