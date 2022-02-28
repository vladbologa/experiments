#pragma once

#include "../DrawableObject.h"
#include "Common.h"

namespace commands {

/**
 * Command that removes object from the scene
 */
class Remove {
public:
    Remove(const DrawableObject& drawableObject, const InserterFunc& inserter, const RemoverFunc& remover);

    Remove(Remove&&) = default;

    void execute() const;
    void undo() const;

private:
    DrawableObject m_drawableObject; //< stores a copy of the object, to be able to recreate it, if needed
    InserterFunc m_inserter;
    RemoverFunc m_remover;
};

} // namespace commands
