#include "../Hpp/ListGraph.hpp"

ListGraph::ListGraph(uint64_t verticesCount) : inEdges(verticesCount), outEdges(verticesCount) {}
ListGraph::ListGraph(const IGraph* otherGraph) : ListGraph(otherGraph->VerticesCount()) {
    for (uint64_t i = 0; i < inEdges.size(); ++i) {
        inEdges[i] = otherGraph->GetAllAdjacentIn(i);
        outEdges[i] = otherGraph->GetAllAdjacentOut(i);
    }
}
void ListGraph::AddEdge(uint64_t fromVertex, uint64_t toVertex) {
    inEdges[toVertex].push_back(fromVertex);
    outEdges[fromVertex].push_back(toVertex);
}
uint64_t ListGraph::VerticesCount() const {
    return inEdges.size();
}
std::vector<uint64_t> ListGraph::GetAllAdjacentIn(uint64_t vertex) const {
    return inEdges[vertex];
}
std::vector<uint64_t> ListGraph::GetAllAdjacentOut(uint64_t vertex) const {
    return outEdges[vertex];
}

