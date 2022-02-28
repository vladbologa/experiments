#pragma once

struct Position {
    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;
};

inline bool operator==(const Position& lhs, const Position& rhs)
{
    // TODO: use epsilon for floating point comparison
    return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z;
}

inline bool operator!=(const Position& lhs, const Position& rhs)
{
    return !(lhs == rhs);
}
