#pragma once

#include <algorithm>
#include <cstdint>
#include <unordered_set>
#include <vector>

struct IGraph {
    virtual ~IGraph() {}
    virtual void AddEdge(uint64_t from, uint64_t to) = 0;
    virtual uint64_t VerticesCount() const  = 0;
    virtual std::vector<uint64_t> GetAllAdjacentIn(uint64_t vertex) const = 0;
    virtual std::vector<uint64_t> GetAllAdjacentOut(uint64_t vertex) const = 0;
};

