#pragma once

#include <cstdint>
#include <functional>

// TODO: add support for unique IDs
struct Id {
    uint32_t uuid;

    bool operator==(const Id& other) const
    {
        return uuid == other.uuid;
    }

    bool operator!=(const Id& other) const
    {
        return !(uuid == other.uuid);
    }
};

namespace std {
template <>
struct hash<Id> {
    size_t operator()(const Id& id) const
    {
        return hash<uint32_t>()(id.uuid);
    }
};

} // namespace std
