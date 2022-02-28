#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "../DrawableObject.h"
#include "Add.h"
#include "Move.h"
#include "Remove.h"

using namespace commands;
using testing::_;
using testing::InSequence;
using testing::MockFunction;
using testing::ReturnRef;

using InserterFunc = std::function<void(const DrawableObject&)>;
using RemoverFunc = std::function<void(const Id&)>;
using GetterFunc = std::function<DrawableObject&(const Id&)>;

TEST(CommandTest, AddTest)
{
    DrawableObject drawableObject { Id { 5 }, {} };

    MockFunction<void(const DrawableObject&)> mockInserter;
    MockFunction<void(const Id&)> mockRemover;

    Add command(drawableObject, mockInserter.AsStdFunction(), mockRemover.AsStdFunction());

    {
        InSequence s;
        EXPECT_CALL(mockInserter, Call(_));
        EXPECT_CALL(mockRemover, Call(Id { 5 }));
    }

    command.execute();
    command.undo();
}

TEST(CommandTest, RemoveTest)
{
    DrawableObject drawableObject { Id { 6 }, {} };

    MockFunction<void(const DrawableObject&)> mockInserter;
    MockFunction<void(const Id&)> mockRemover;

    Remove command(drawableObject, mockInserter.AsStdFunction(), mockRemover.AsStdFunction());

    {
        InSequence s;
        EXPECT_CALL(mockRemover, Call(Id { 6 }));
        EXPECT_CALL(mockInserter, Call(_));
    }

    command.execute();
    command.undo();
}

TEST(CommandTest, ChangePositionCommandTest)
{
    Id id { 7 };
    DrawableObject drawableObject { id, {} };
    MockFunction<DrawableObject&(const Id&)> mockGetter;

    EXPECT_CALL(mockGetter, Call(Id { 7 })).WillRepeatedly(ReturnRef(drawableObject));

    Move command(id, {}, mockGetter.AsStdFunction());
    command.execute();
    command.undo();
}
