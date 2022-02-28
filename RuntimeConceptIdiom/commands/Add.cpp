#include "Add.h"

namespace commands {

Add::Add(const DrawableObject& DrawableObject, const InserterFunc& inserter, const RemoverFunc& remover)
    : m_drawableObject(DrawableObject)
    , m_inserter(inserter)
    , m_remover(remover)
{
}

void Add::execute() const
{
    m_inserter(m_drawableObject);
}

void Add::undo() const
{
    m_remover(m_drawableObject.getId());
}

} // namespace rci
