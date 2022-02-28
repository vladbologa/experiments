#include "Move.h"

namespace commands {

Move::Move(const Id& id, const Position& position, const GetterFunc& getterFunc)
    : id_(id)
    , m_newPosition(position)
    , m_drawableObjectGetter(getterFunc)
{
    m_oldPosition = m_drawableObjectGetter(id).getPosition();
}

Move::Move(const Id& id, const Position& oldPosition, const Position& newPosition, const GetterFunc& getterFunc)
    : id_(id)
    , m_oldPosition(oldPosition)
    , m_newPosition(newPosition)
    , m_drawableObjectGetter(getterFunc)
{
}

void Move::execute() const
{
    m_drawableObjectGetter(id_).setPosition(m_newPosition);
}

void Move::undo() const
{
    m_drawableObjectGetter(id_).setPosition(m_oldPosition);
}

} // namespace commands
