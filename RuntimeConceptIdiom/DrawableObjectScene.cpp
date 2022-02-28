#include "DrawableObjectScene.h"

#include "commands/Add.h"
#include "commands/Move.h"
#include "commands/Remove.h"

#include <stdexcept>

DrawableObjectScene::DrawableObjectScene()
    : dawableObjectsInserter_ { [this](const DrawableObject& DrawableObject) {
        auto res = this->drawableObjects_.emplace(DrawableObject.getId(), DrawableObject);
        if (!res.second) {
            throw std::runtime_error("An object with the given ID already exists.");
        }
    } }
    , drawableObjectsRemover_ {
        [this](const Id& id) {
            auto erasedCount = this->drawableObjects_.erase(id);
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
    commandSequence_.commit();
    lastChangePositionId_ = std::nullopt;

    commands::Add command(DrawableObject, dawableObjectsInserter_, drawableObjectsRemover_);
    commandSequence_.add(std::move(command));
    commandSequence_.commit();
}

void DrawableObjectScene::remove(const Id& id)
{
    // commit any unsaved state
    commandSequence_.commit();
    lastChangePositionId_ = std::nullopt;

    commands::Remove command(drawableObjects_.at(id), dawableObjectsInserter_, drawableObjectsRemover_);
    commandSequence_.add(std::move(command));
    commandSequence_.commit();
}

void DrawableObjectScene::changePosition(const Id& id, const Position& position)
{
    // commit unsaved changes, if needed
    if (lastChangePositionId_.has_value() && lastChangePositionId_.value() != id) {
        commandSequence_.commit();
    }

    commands::Move command(
        id, position, [this](const Id& id) -> DrawableObject& {
            return drawableObjects_.at(id);
        });
    commandSequence_.add(std::move(command));
    lastChangePositionId_ = id;
}

void DrawableObjectScene::undo()
{
    lastChangePositionId_ = std::nullopt;
    commandSequence_.undo();
}

void DrawableObjectScene::redo()
{
    lastChangePositionId_ = std::nullopt;
    commandSequence_.redo();
}

DrawableObject&
DrawableObjectScene::getDrawableObject(const Id& id)
{
    return drawableObjects_.at(id);
}

const DrawableObject&
DrawableObjectScene::getDrawableObject(const Id& id) const
{
    return drawableObjects_.at(id);
}
