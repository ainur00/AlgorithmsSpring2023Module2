#include "../Hpp/SetGraph.hpp"

SetGraph::SetGraph(uint64_t verticesCount) : inEdges(verticesCount), outEdges(verticesCount) {}
SetGraph::SetGraph(const IGraph* otherGraph) : SetGraph(otherGraph->VerticesCount()) {
    for (uint64_t v = 0; v < inEdges.size(); ++v) {
        for (uint64_t u : otherGraph->GetAllAdjacentIn(v))
            inEdges[v].insert(u);
        for (uint64_t u : otherGraph->GetAllAdjacentOut(v))
            outEdges[v].insert(u);
    }
}
void SetGraph::AddEdge(uint64_t fromVertex, uint64_t toVertex) {
    inEdges[toVertex].insert(fromVertex);
    outEdges[fromVertex].insert(toVertex);
}
uint64_t SetGraph::VerticesCount() const {
    return inEdges.size();
}
std::vector<uint64_t> SetGraph::GetAllAdjacentIn(uint64_t vertex) const {
    std::vector<uint64_t> allAdjacentIn(inEdges[vertex].size());
    std::copy(inEdges[vertex].begin(), inEdges[vertex].end(), allAdjacentIn.begin());
    return allAdjacentIn;
}
std::vector<uint64_t> SetGraph::GetAllAdjacentOut(uint64_t vertex) const {
    std::vector<uint64_t> allAdjacentOut(outEdges[vertex].size());
    std::copy(outEdges[vertex].begin(), outEdges[vertex].end(), allAdjacentOut.begin());
    return allAdjacentOut;
}

