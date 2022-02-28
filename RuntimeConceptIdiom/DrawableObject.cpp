#include "DrawableObject.h"

DrawableObject::DrawableObject()
    : m_id {}
{
}

DrawableObject::DrawableObject(const Id& id, const Position& position)
    : m_id(id)
    , m_position(position)
{
}

void DrawableObject::setPosition(const Position& position)
{
    m_position = position;
}

Position DrawableObject::getPosition() const
{
    return m_position;
}

Id DrawableObject::getId() const
{
    return m_id;
}
