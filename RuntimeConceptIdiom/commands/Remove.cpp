#include "Remove.h"

namespace commands {

Remove::Remove(const DrawableObject& drawableObject, const InserterFunc& inserter, const RemoverFunc& remover)
    : m_drawableObject(drawableObject)
    , m_inserter(inserter)
    , m_remover(remover)
{
}

void Remove::execute() const
{
    m_remover(m_drawableObject.getId());
}

void Remove::undo() const
{
    m_inserter(m_drawableObject);
}

} // namespace commands
