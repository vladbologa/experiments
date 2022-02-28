#pragma once

#include <functional>

class DrawableObject;
struct Id;

using InserterFunc = std::function<void(const DrawableObject&)>;
using RemoverFunc = std::function<void(const Id&)>;
using GetterFunc = std::function<DrawableObject&(const Id&)>;
