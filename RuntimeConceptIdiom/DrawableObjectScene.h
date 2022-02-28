#pragma once

#include "CommandSequence.h"
#include "DrawableObject.h"
#include "commands/Common.h"

#include <memory>
#include <optional>
#include <unordered_map>
#include <vector>

class Command;

/**
 * Represent a scene containing drawable objects
 *
 * Objects can be added to, and removed from the scene, and
 * their positions can be changed. These actions can be undone
 * and redone.
 */
class DrawableObjectScene {
public:
    DrawableObjectScene();
    ~DrawableObjectScene() noexcept;

    // Adds a new object
    void add(const DrawableObject& object);
    
    // Removes the object with the given id
    void remove(const Id& id);

    // Moves the object with the specified Id to a new position
    // Note that several moves of the same object are stored as one single action.
    void changePosition(const Id& id, const Position& position);

    // Undoes the last action
    void undo();

    // Redoes the previously undone action
    void redo();

    // Getter for the object with the given ID
    DrawableObject& getDrawableObject(const Id& id);
    const DrawableObject& getDrawableObject(const Id& id) const;

private:
    std::unordered_map<Id, DrawableObject> m_drawableObjects;
    CommandSequence m_commandSequence;

    InserterFunc m_dawableObjectsInserter;
    RemoverFunc m_drawableObjectsRemover;
    std::optional<Id> m_lastChangePositionId;
};
