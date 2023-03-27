#include "Graph.hpp"

class SetGraph : public IGraph {
public:
    explicit SetGraph(uint64_t verticesCount);
    explicit SetGraph(const IGraph* otherGraph);
    void AddEdge(uint64_t fromVertex, uint64_t toVertex) override;
    uint64_t VerticesCount() const override;
    std::vector<uint64_t> GetAllAdjacentIn(uint64_t vertex) const override;
    std::vector<uint64_t> GetAllAdjacentOut(uint64_t vertex) const override;
private:
    std::vector<std::unordered_set<uint64_t>> inEdges;
    std::vector<std::unordered_set<uint64_t>> outEdges;
};

