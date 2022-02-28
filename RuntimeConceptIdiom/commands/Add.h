#pragma once

#include "Common.h"

#include "../DrawableObject.h"
#include "../Id.h"

#include <functional>

/**
 * Command that adds objects to the scene
 */
namespace commands {

class Add {
public:
    Add(const DrawableObject& DrawableObject, const InserterFunc& inserter, const RemoverFunc& remover);
    Add(Add&&) = default;

    void execute() const;
    void undo() const;

private:
    DrawableObject m_drawableObject;
    InserterFunc m_inserter;
    RemoverFunc m_remover;
};

} // namespace commands
