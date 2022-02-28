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
    DrawableObject drawableObject_; //< stores a copy of the object, to be able to recreate it, if needed
    InserterFunc inserter_;
    RemoverFunc remover_;
};

} // namespace commands
