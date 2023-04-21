#include <algorithm>
#include <cstdint>
#include <iostream>
#include <unordered_set>
#include <vector>

class Graph {
public:
    Graph(uint16_t);
    void AddEdge(uint16_t, uint16_t);
    uint16_t GetVerticesCount() const;
    std::vector<uint16_t> GetAllAdjacentIn(uint16_t) const;
    std::vector<uint16_t> GetAllAdjacentOut(uint16_t) const;
private:
    std::vector<std::unordered_set<uint16_t>> inEdges;
    std::vector<std::unordered_set<uint16_t>> outEdges;
};
Graph::Graph(uint16_t verticesCount) : inEdges(verticesCount), outEdges(verticesCount) {}
void Graph::AddEdge(uint16_t fromVertex, uint16_t toVertex) {
    inEdges[toVertex].insert(fromVertex);
    outEdges[fromVertex].insert(toVertex);
}
uint16_t Graph::GetVerticesCount() const {
    return inEdges.size();
}
std::vector<uint16_t> Graph::GetAllAdjacentIn(uint16_t vertex) const {
    std::vector<uint16_t> allAdjacentIn(inEdges[vertex].size());
    std::copy(inEdges[vertex].begin(), inEdges[vertex].end(), allAdjacentIn.begin());
    return allAdjacentIn;
}
std::vector<uint16_t> Graph::GetAllAdjacentOut(uint16_t vertex) const {
    std::vector<uint16_t> allAdjacentOut(outEdges[vertex].size());
    std::copy(outEdges[vertex].begin(), outEdges[vertex].end(), allAdjacentOut.begin());
    return allAdjacentOut;
}

void GetLeaveTimeSortedVertices(const Graph& graph, const uint16_t& verticeFrom, std::vector<bool>& visited, std::vector<uint16_t>& leaveTimeSortedVertices) {
    visited[verticeFrom] = true;
    for (uint16_t verticeTo : graph.GetAllAdjacentIn(verticeFrom))
        if (!visited[verticeTo])
            GetLeaveTimeSortedVertices(graph, verticeTo, visited, leaveTimeSortedVertices);
    leaveTimeSortedVertices.push_back(verticeFrom);
}
std::vector<uint16_t> GetLeaveTimeSortedVertices(const Graph& graph) {
    std::vector<uint16_t> leaveTimeSortedVertices;
    std::vector<bool> visited(graph.GetVerticesCount());
    for (uint16_t verticeFrom = 0; verticeFrom < graph.GetVerticesCount(); ++verticeFrom)
        if (!visited[verticeFrom])
            GetLeaveTimeSortedVertices(graph, verticeFrom, visited, leaveTimeSortedVertices);
    std::reverse(leaveTimeSortedVertices.begin(), leaveTimeSortedVertices.end());
    return leaveTimeSortedVertices;
}
void GetVerticesStronglyConnectedComponents(const Graph& graph, const uint16_t& verticeFrom, std::vector<uint16_t>& visited, const uint16_t& iStronglyConnectedComponent, std::vector<uint16_t>& verticesStronglyConnectedComponents) {
    verticesStronglyConnectedComponents[verticeFrom] = iStronglyConnectedComponent;
    visited[verticeFrom] = true;
    for (uint16_t verticeTo : graph.GetAllAdjacentOut(verticeFrom)) {
        if (!visited[verticeTo])
            GetVerticesStronglyConnectedComponents(graph, verticeTo, visited, iStronglyConnectedComponent, verticesStronglyConnectedComponents);
    }
}
std::vector<uint16_t> GetVerticesStronglyConnectedComponents(const Graph& graph, const std::vector<uint16_t>& leaveTimeSortedVertices) {
    std::vector<uint16_t> verticesStronglyConnectedComponents(graph.GetVerticesCount());
    std::vector<uint16_t> visited(graph.GetVerticesCount());
    uint16_t iStronglyConnectedComponent = 0;
    for (uint16_t verticeFrom : leaveTimeSortedVertices)
        if (!visited[verticeFrom]) {
            GetVerticesStronglyConnectedComponents(graph, verticeFrom, visited, iStronglyConnectedComponent, verticesStronglyConnectedComponents);
            ++iStronglyConnectedComponent;
        }
    return verticesStronglyConnectedComponents;
}
Graph GetGraphCondense(const Graph& graph, const std::vector<uint16_t>& verticesStronglyConnectedComponents) {
    uint16_t maxStronglyConnectedComponentIndex = 0;
    for (uint16_t iVerticeStronglyConnectedComponent : verticesStronglyConnectedComponents)
        maxStronglyConnectedComponentIndex = std::max(iVerticeStronglyConnectedComponent, maxStronglyConnectedComponentIndex);
    Graph graphCondense(maxStronglyConnectedComponentIndex + 1);
    for (size_t verticeFrom = 0; verticeFrom < graph.GetVerticesCount(); ++verticeFrom) {
        for (size_t verticeTo : graph.GetAllAdjacentOut(verticeFrom))
            if (verticesStronglyConnectedComponents[verticeFrom] != verticesStronglyConnectedComponents[verticeTo])
                graphCondense.AddEdge(verticesStronglyConnectedComponents[verticeFrom], verticesStronglyConnectedComponents[verticeTo]);
    }
    return graphCondense;
}
uint16_t GetMinAddedEdgesCountToStronglyConnected(const Graph& graph) {
    std::vector<uint16_t> leaveTimeSortedVertices = GetLeaveTimeSortedVertices(graph);
    std::vector<uint16_t> verticesStronglyConnectedComponents = GetVerticesStronglyConnectedComponents(graph, leaveTimeSortedVertices);
    Graph graphCondense = GetGraphCondense(graph, verticesStronglyConnectedComponents);
    if (graphCondense.GetVerticesCount() == 1)
        return 0;
    uint16_t stockCount = 0;
    uint16_t sourceCount = 0;
    for (uint16_t vertice = 0; vertice < graphCondense.GetVerticesCount(); ++vertice) {
        if (graphCondense.GetAllAdjacentIn(vertice).size() == 0)
            ++sourceCount;
        if (graphCondense.GetAllAdjacentOut(vertice).size() == 0)
            ++stockCount;
    }
    return std::max(stockCount, sourceCount);
}

int32_t main() {
    uint16_t verticesCount = 0;
    uint16_t edgesCount = 0;
    std::cin >> verticesCount >> edgesCount;
    Graph graph(verticesCount);
    for (uint16_t i = 0; i < edgesCount; ++i) {
        uint16_t verticeFrom = 0;
        uint16_t verticeTo = 0;
        std::cin >> verticeFrom >> verticeTo;
        graph.AddEdge(verticeFrom - 1, verticeTo - 1);
    }
    std::cout << GetMinAddedEdgesCountToStronglyConnected(graph) << std::endl;
    return 0;
}
