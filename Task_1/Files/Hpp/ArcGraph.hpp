#include "Graph.hpp"

class ArcGraph : public IGraph {
public:
    explicit ArcGraph(uint64_t verticesCount);
    explicit ArcGraph(const IGraph* otherGraph);
    void AddEdge(uint64_t fromVertex, uint64_t toVertex) override;
    uint64_t VerticesCount() const override;
    std::vector<uint64_t> GetAllAdjacentIn(uint64_t vertex) const override;
    std::vector<uint64_t> GetAllAdjacentOut(uint64_t vertex) const override;
private:
    std::vector<std::pair<uint64_t, uint64_t>> arcs;
    const uint64_t verticesCount;
};

