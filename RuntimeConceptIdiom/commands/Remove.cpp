#include "Remove.h"

namespace commands {

Remove::Remove(const DrawableObject& drawableObject, const InserterFunc& inserter, const RemoverFunc& remover)
    : drawableObject_(drawableObject)
    , inserter_(inserter)
    , remover_(remover)
{
}

void Remove::execute() const
{
    remover_(drawableObject_.getId());
}

void Remove::undo() const
{
    inserter_(drawableObject_);
}

} // namespace commands
