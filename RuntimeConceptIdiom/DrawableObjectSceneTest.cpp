#include <gtest/gtest.h>

#include "DrawableObject.h"
#include "DrawableObjectScene.h "

TEST(DrawableObjectSceneTest, IntegrationTest)
{
    DrawableObjectScene scene;

    Position positionA { 1.0f, 2.0f, 3.0f };
    Position positionB { 3.0f, 2.0f, 1.0f };
    Position positionC { 4.0f, 4.0f, 4.0f };
    Position positionD { 4.0f, 5.0f, 6.0f };
    Position positionE { 10.0f, 11.0f, 12.0f };
    Position positionF { 7.0f, 7.0f, 7.0f };
    Position positionG { 6.0f, 7.0f, 1.0f };

    scene.add(DrawableObject { Id { 1 }, positionA });
    scene.add(DrawableObject { Id { 2 }, positionB });

    EXPECT_EQ(positionA, scene.getDrawableObject(Id { 1 }).getPosition());
    EXPECT_EQ(positionB, scene.getDrawableObject(Id { 2 }).getPosition());

    scene.changePosition(Id { 1 }, positionC);
    EXPECT_EQ(positionC, scene.getDrawableObject(Id { 1 }).getPosition());

    scene.add(DrawableObject { Id { 3 }, positionD });
    scene.changePosition(Id { 2 }, positionE);
    scene.remove(Id { 1 });
    scene.changePosition(Id { 3 }, positionF);
    scene.changePosition(Id { 3 }, positionG);
    scene.undo();
    scene.undo();

    // This tests the conditions from the assignment description
    EXPECT_EQ(positionC, scene.getDrawableObject(Id { 1 }).getPosition());
    EXPECT_EQ(positionE, scene.getDrawableObject(Id { 2 }).getPosition());
    EXPECT_EQ(positionD, scene.getDrawableObject(Id { 3 }).getPosition());

    scene.redo();
    EXPECT_THROW(scene.getDrawableObject(Id { 1 }), std::out_of_range);
    EXPECT_EQ(positionE, scene.getDrawableObject(Id { 2 }).getPosition());
    EXPECT_EQ(positionD, scene.getDrawableObject(Id { 3 }).getPosition());
    scene.redo();
    EXPECT_THROW(scene.getDrawableObject(Id { 1 }), std::out_of_range);
    EXPECT_EQ(positionE, scene.getDrawableObject(Id { 2 }).getPosition());
    EXPECT_EQ(positionG, scene.getDrawableObject(Id { 3 }).getPosition());

    const int totalCommands = 7;
    for (int i = 0; i < totalCommands; i++) {
        scene.undo();
    }

    EXPECT_THROW(scene.getDrawableObject(Id { 1 }), std::out_of_range);
    EXPECT_THROW(scene.getDrawableObject(Id { 2 }), std::out_of_range);
    EXPECT_THROW(scene.getDrawableObject(Id { 3 }), std::out_of_range);

    for (int i = 0; i < totalCommands; i++) {
        scene.redo();
    }

    EXPECT_THROW(scene.getDrawableObject(Id { 1 }).getPosition(), std::out_of_range);
    EXPECT_EQ(positionE, scene.getDrawableObject(Id { 2 }).getPosition());
    EXPECT_EQ(positionG, scene.getDrawableObject(Id { 3 }).getPosition());

    scene.changePosition(Id { 3 }, positionA);
    scene.changePosition(Id { 3 }, positionB);
    scene.changePosition(Id { 2 }, positionA);
    scene.undo();
    scene.undo();
    EXPECT_THROW(scene.getDrawableObject(Id { 1 }).getPosition(), std::out_of_range);
    EXPECT_EQ(positionE, scene.getDrawableObject(Id { 2 }).getPosition());
    EXPECT_EQ(positionG, scene.getDrawableObject(Id { 3 }).getPosition());
}

TEST(DrawableObjectSceneTest, EmptyLookUpTest)
{
    DrawableObjectScene scene;
    EXPECT_THROW(scene.getDrawableObject(Id { 0 }), std::out_of_range);
    EXPECT_THROW(scene.remove(Id { 0 }), std::out_of_range);
    EXPECT_THROW(scene.changePosition(Id { 0 }, Position { 1.0f, 2.0f, 3.0f }), std::out_of_range);
}

TEST(DrawableObjectSceneTest, AddSameIdTwice)
{
    DrawableObjectScene scene;
    scene.add(DrawableObject { Id { 1 }, {} });
    EXPECT_THROW(scene.add(DrawableObject { Id { 1 }, {} }), std::runtime_error);
}
