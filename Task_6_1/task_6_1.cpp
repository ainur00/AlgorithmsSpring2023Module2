#include <algorithm>
#include <cstdint>
#include <iostream>
#include <map>
#include <set>
#include <unordered_set>
#include <utility>
#include <vector>

class Graph {
    public:
        Graph(uint16_t);
        void AddEdge(uint16_t, uint16_t, uint32_t);
        uint16_t GetVerticesCount() const;
        uint32_t GetEdgeWeight(uint16_t, uint16_t) const;
        std::vector<uint16_t> GetAllAdjacentVertices(uint16_t) const;
    private:
        uint16_t verticesCount;
        std::vector<std::unordered_set<uint16_t>> edges;
        std::map<std::pair<uint16_t, uint16_t>, uint32_t> edgesWeights;
};
Graph::Graph(uint16_t verticesCount) : verticesCount(verticesCount), edges(verticesCount) {
    for (uint16_t vertice = 0; vertice < verticesCount; ++vertice)
        edgesWeights[std::make_pair(vertice, vertice)] = 0;
}
void Graph::AddEdge(uint16_t vertice1, uint16_t vertice2, uint32_t edgeWeight) {
    if (vertice1 == vertice2)
        return;
    edges[vertice1].insert(vertice2);
    edges[vertice2].insert(vertice1);
    if (vertice1 > vertice2)
        std::swap(vertice1, vertice2);
    if (!edgesWeights.contains(std::make_pair(vertice1, vertice2)) || edgeWeight < edgesWeights[std::make_pair(vertice1, vertice2)])
        edgesWeights[std::make_pair(vertice1, vertice2)] = edgeWeight;
}
uint16_t Graph::GetVerticesCount() const {
    return verticesCount;
}
uint32_t Graph::GetEdgeWeight(uint16_t vertice1, uint16_t vertice2) const {
    if (vertice1 > vertice2)
        std::swap(vertice1, vertice2);
    return edgesWeights.find(std::make_pair(vertice1, vertice2))->second;
}
std::vector<uint16_t> Graph::GetAllAdjacentVertices(uint16_t vertice) const {
    return std::vector(edges[vertice].begin(), edges[vertice].end());
}


class PriorityQueue {
    public:
        bool Add(uint32_t, uint32_t, uint16_t);
        std::pair<uint32_t, uint16_t> ExtractMin();
        bool IsEmpty() const;
    private:
        std::set<std::pair<uint32_t, uint16_t>> priorityQueue;
};
bool PriorityQueue::Add(uint32_t prevDistanceToVertice, uint32_t distanceToVertice, uint16_t verticeIndex) {
    if (prevDistanceToVertice != UINT32_MAX) {
        if (prevDistanceToVertice <= distanceToVertice)
            return false;
        priorityQueue.extract(std::make_pair(prevDistanceToVertice, verticeIndex));
    }
    priorityQueue.insert(std::make_pair(distanceToVertice, verticeIndex));
    return true;
}
std::pair<uint32_t, uint16_t> PriorityQueue::ExtractMin() {
    std::pair<uint32_t, uint16_t> minElement = *priorityQueue.begin();
    priorityQueue.extract(std::make_pair(priorityQueue.begin()->first, priorityQueue.begin()->second));
    return minElement;
}
bool PriorityQueue::IsEmpty() const {
    return priorityQueue.empty();
}

uint64_t GetMinSpanningTreeWeight(const Graph& graph) {
    uint64_t minSpanningTreeWeight = 0;
    std::vector<uint32_t> verticesDistances(graph.GetVerticesCount(), UINT32_MAX);
    std::vector<uint16_t> visited(graph.GetVerticesCount());
    PriorityQueue spanningTreeBuilding;
    spanningTreeBuilding.Add(verticesDistances[0], 0, 0);
    verticesDistances[0] = 0;
    while (!spanningTreeBuilding.IsEmpty()) {
        std::pair<uint32_t, uint16_t> iSpanningTreeVertice = spanningTreeBuilding.ExtractMin();
        visited[iSpanningTreeVertice.second] = true;
        minSpanningTreeWeight += iSpanningTreeVertice.first;
        for (uint16_t iVerticeTo : graph.GetAllAdjacentVertices(iSpanningTreeVertice.second))
            if ((!visited[iVerticeTo]) && (spanningTreeBuilding.Add(verticesDistances[iVerticeTo], graph.GetEdgeWeight(iSpanningTreeVertice.second, iVerticeTo), iVerticeTo)))
                verticesDistances[iVerticeTo] = graph.GetEdgeWeight(iSpanningTreeVertice.second, iVerticeTo);
    }
    return minSpanningTreeWeight;
}

int32_t main() {
    uint16_t verticesCount = 0;
    uint32_t edgesCount = 0;
    std::cin >> verticesCount >> edgesCount;
    Graph graph(verticesCount);
    for (uint i = 0; i < edgesCount; ++i) {
        uint16_t vertice1 = 0;
        uint16_t vertice2 = 0;
        uint32_t edgeWeight = 0;
        std::cin >> vertice1 >> vertice2 >> edgeWeight;
        graph.AddEdge(vertice1 - 1, vertice2 - 1, edgeWeight);
    }
    std::cout << GetMinSpanningTreeWeight(graph) << std::endl;
    return 0;
}

