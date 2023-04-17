#include "../Hpp/MatrixGraph.hpp"

MatrixGraph::MatrixGraph(uint64_t verticesCount) : matrix(verticesCount, std::vector<bool>(verticesCount)) {}
MatrixGraph::MatrixGraph(const IGraph* otherGraph) : MatrixGraph(otherGraph->VerticesCount()) {
    for (uint64_t u = 0; u < matrix.size(); ++u)
        for (uint64_t v : otherGraph->GetAllAdjacentOut(u))
            matrix[u][v] = true;
}
void MatrixGraph::AddEdge(uint64_t fromVertex, uint64_t toVertex) {
    matrix[fromVertex][toVertex] = true;
}
uint64_t MatrixGraph::VerticesCount() const {
    return matrix.size();
}
std::vector<uint64_t> MatrixGraph::GetAllAdjacentIn(uint64_t vertex) const {
    std::vector<uint64_t> allAdjacentIn;
    for (uint64_t u = 0; u < matrix.size(); ++u)
        if (matrix[u][vertex])
            allAdjacentIn.push_back(u);
    return allAdjacentIn;
}
std::vector<uint64_t> MatrixGraph::GetAllAdjacentOut(uint64_t vertex) const {
    std::vector<uint64_t> allAdjacentOut;
    for (uint64_t u = 0; u < matrix.size(); ++u)
        if (matrix[vertex][u])
            allAdjacentOut.push_back(u);
    return allAdjacentOut;
}

