#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "CommandSequence.h"

#include "commands/Command.h"

using testing::_;
using testing::InSequence;
using testing::MockFunction;
using testing::ReturnRef;

class MockCommand {
public:
    void execute() const {};
    void undo() const {};
};

TEST(CommandSequenceTest, CommandSequence)
{
    CommandSequence cs;

    MockCommand mockCommand;
    EXPECT_FALSE(cs.canUndo());
    EXPECT_FALSE(cs.canRedo());

    cs.add(std::move(mockCommand));
    cs.commit();
    EXPECT_TRUE(cs.canUndo());
    EXPECT_FALSE(cs.canRedo());

    cs.undo();
    EXPECT_FALSE(cs.canUndo());
    EXPECT_TRUE(cs.canRedo());

    cs.redo();
    EXPECT_TRUE(cs.canUndo());
    EXPECT_FALSE(cs.canRedo());

    cs.undo();
    EXPECT_FALSE(cs.canUndo());
    EXPECT_TRUE(cs.canRedo());

    // add another command -> should invalidate redo
    MockCommand mockCommand2;
    cs.add(std::move(mockCommand2));
    cs.commit();
    EXPECT_TRUE(cs.canUndo());
    EXPECT_FALSE(cs.canRedo());
}

TEST(CommandSequenceTest, CommandSequenceNoCommit)
{
    CommandSequence cs;
    MockCommand mockCommand;

    EXPECT_FALSE(cs.canUndo());
    EXPECT_FALSE(cs.canRedo());

    cs.add(std::move(mockCommand));
    EXPECT_TRUE(cs.canUndo());
    EXPECT_FALSE(cs.canRedo());

    cs.undo();
    EXPECT_FALSE(cs.canUndo());
    EXPECT_TRUE(cs.canRedo());

    cs.redo();
    EXPECT_TRUE(cs.canUndo());
    EXPECT_FALSE(cs.canRedo());

    cs.undo();
    EXPECT_FALSE(cs.canUndo());
    EXPECT_TRUE(cs.canRedo());

    // add another command -> should invalidate redo
    MockCommand mockCommand2;
    cs.add(std::move(mockCommand2));
    EXPECT_TRUE(cs.canUndo());
    EXPECT_FALSE(cs.canRedo());
}
