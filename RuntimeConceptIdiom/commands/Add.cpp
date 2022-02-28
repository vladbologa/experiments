#include "Add.h"

namespace commands {

Add::Add(const DrawableObject& DrawableObject, const InserterFunc& inserter, const RemoverFunc& remover)
    : drawableObject_(DrawableObject)
    , inserter_(inserter)
    , remover_(remover)
{
}

void Add::execute() const
{
    inserter_(drawableObject_);
}

void Add::undo() const
{
    remover_(drawableObject_.getId());
}

} // namespace rci
