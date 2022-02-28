cmake_minimum_required (VERSION 3.15)

project ("RuntimeConceptIdiom")

set(CMAKE_CXX_STANDARD 20)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(HEADERS
    DrawableObject.h
    DrawableObjectScene.h
    CommandSequence.h
    commands/Add.h
    commands/Command.h
    commands/Composite.h
    commands/Common.h
    commands/Move.h
    commands/Remove.h
    Id.h
    Position.h
)
set(SRCS
    DrawableObject.cpp
    DrawableObjectScene.cpp
    DrawableObjectSceneTest.cpp
    CommandSequence.cpp
    CommandSequenceTest.cpp
    commands/Add.cpp
    commands/Composite.cpp
    commands/Move.cpp
    commands/Remove.cpp
    commands/Tests.cpp
)

add_executable(RuntimeConceptIdiomTest  ${HEADERS} ${SRCS})
target_compile_features(RuntimeConceptIdiomTest PUBLIC cxx_std_20)

include(CTest)
include(cmake/AddGoogleTest.cmake)
include(GoogleTest)
gtest_discover_tests(RuntimeConceptIdiomTest
                TEST_PREFIX "RuntimeConceptIdiomTest."
                PROPERTIES FOLDER "Tests")

target_link_libraries(RuntimeConceptIdiomTest
	PRIVATE gtest gmock gtest_main)
