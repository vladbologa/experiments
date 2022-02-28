#pragma once

#include "Id.h"
#include "Position.h"

/**
 * Simple DrawableObject class
 */
class DrawableObject {
public:
    DrawableObject();
    DrawableObject(const Id& id, const Position& position);

    void setPosition(const Position& position);
    Position getPosition() const;

    Id getId() const;

    // TODO: Implement
    void draw() const { }

private:
    Id m_id;
    Position m_position;
};
