#include "DrawableObjectScene.h"

#include "commands/Add.h"
#include "commands/Move.h"
#include "commands/Remove.h"

#include <stdexcept>

DrawableObjectScene::DrawableObjectScene()
    : m_dawableObjectsInserter { [this](const DrawableObject& DrawableObject) {
        auto res = this->m_drawableObjects.emplace(DrawableObject.getId(), DrawableObject);
        if (!res.second) {
            throw std::runtime_error("An object with the given ID already exists.");
        }
    } }
    , m_drawableObjectsRemover {
        [this](const Id& id) {
            auto erasedCount = this->m_drawableObjects.erase(id);
            if (erasedCount == 0) {
                throw std::runtime_error("An object with the given ID does not exist.");
            } }
    }
{
}

DrawableObjectScene::~DrawableObjectScene() noexcept = default;

void DrawableObjectScene::add(const DrawableObject& DrawableObject)
{
    // commit any unsaved state
    m_commandSequence.commit();
    m_lastChangePositionId = std::nullopt;

    commands::Add command(DrawableObject, m_dawableObjectsInserter, m_drawableObjectsRemover);
    m_commandSequence.add(std::move(command));
    m_commandSequence.commit();
}

void DrawableObjectScene::remove(const Id& id)
{
    // commit any unsaved state
    m_commandSequence.commit();
    m_lastChangePositionId = std::nullopt;

    commands::Remove command(m_drawableObjects.at(id), m_dawableObjectsInserter, m_drawableObjectsRemover);
    m_commandSequence.add(std::move(command));
    m_commandSequence.commit();
}

void DrawableObjectScene::changePosition(const Id& id, const Position& position)
{
    // commit unsaved changes, if needed
    if (m_lastChangePositionId.has_value() && m_lastChangePositionId.value() != id) {
        m_commandSequence.commit();
    }

    commands::Move command(
        id, position, [this](const Id& id) -> DrawableObject& {
            return m_drawableObjects.at(id);
        });
    m_commandSequence.add(std::move(command));
    m_lastChangePositionId = id;
}

void DrawableObjectScene::undo()
{
    m_lastChangePositionId = std::nullopt;
    m_commandSequence.undo();
}

void DrawableObjectScene::redo()
{
    m_lastChangePositionId = std::nullopt;
    m_commandSequence.redo();
}

DrawableObject&
DrawableObjectScene::getDrawableObject(const Id& id)
{
    return m_drawableObjects.at(id);
}

const DrawableObject&
DrawableObjectScene::getDrawableObject(const Id& id) const
{
    return m_drawableObjects.at(id);
}
