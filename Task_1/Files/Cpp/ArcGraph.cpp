#include "../Hpp/ArcGraph.hpp"

ArcGraph::ArcGraph(uint64_t verticesCount) : verticesCount(verticesCount) {}
ArcGraph::ArcGraph(const IGraph* otherGraph) : ArcGraph(otherGraph->VerticesCount()) {
    for (uint64_t u = 0; u < verticesCount; ++u)
        for (uint64_t v : otherGraph->GetAllAdjacentOut(u))
            arcs.push_back(std::make_pair(u, v));
}
void ArcGraph::AddEdge(uint64_t fromVertex, uint64_t toVertex) {
    arcs.push_back(std::make_pair(fromVertex, toVertex));
}
uint64_t ArcGraph::VerticesCount() const {
    return verticesCount;
}
std::vector<uint64_t> ArcGraph::GetAllAdjacentIn(uint64_t vertex) const {
    std::vector<uint64_t> allAdjacentIn;
    for (std::pair<uint64_t, uint64_t> arc : arcs)
        if (arc.second == vertex)
            allAdjacentIn.push_back(arc.first);
    return allAdjacentIn;
}
std::vector<uint64_t> ArcGraph::GetAllAdjacentOut(uint64_t vertex) const {
    std::vector<uint64_t> allAdjacentOut;
    for (std::pair<uint64_t, uint64_t> arc : arcs)
        if (arc.first == vertex)
            allAdjacentOut.push_back(arc.second);
    return allAdjacentOut;
}

