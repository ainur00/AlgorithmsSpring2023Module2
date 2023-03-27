#include "Graph.hpp"

class MatrixGraph : public IGraph {
public:
    explicit MatrixGraph(uint64_t verticesCount);
    explicit MatrixGraph(const IGraph* otherGraph);
    void AddEdge(uint64_t fromVertex, uint64_t toVertex) override;
    uint64_t VerticesCount() const override;
    std::vector<uint64_t> GetAllAdjacentIn(uint64_t vertex) const override;
    std::vector<uint64_t> GetAllAdjacentOut(uint64_t vertex) const override;
private:
    std::vector<std::vector<bool>> matrix;
};

