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
    DrawableObject drawableObject_;
    InserterFunc inserter_;
    RemoverFunc remover_;
};

} // namespace commands
