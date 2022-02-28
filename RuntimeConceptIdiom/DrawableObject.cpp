#include "DrawableObject.h"

DrawableObject::DrawableObject()
    : id_ {}
{
}

DrawableObject::DrawableObject(const Id& id, const Position& position)
    : id_(id)
    , position_(position)
{
}

void DrawableObject::setPosition(const Position& position)
{
    position_ = position;
}

Position DrawableObject::getPosition() const
{
    return position_;
}

Id DrawableObject::getId() const
{
    return id_;
}
