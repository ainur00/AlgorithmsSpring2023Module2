#include <algorithm>
#include <iostream>
#include <map>
#include <set>
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
        std::vector<std::vector<uint16_t>> edges;
        std::map<std::pair<uint16_t, uint16_t>, uint32_t> edgesWeights;
};
Graph::Graph(uint16_t verticesCount) : verticesCount(verticesCount), edges(verticesCount) {
    for (uint16_t vertice = 0; vertice < verticesCount; ++vertice)
        edgesWeights[std::make_pair(vertice, vertice)] = 0;
}
void Graph::AddEdge(uint16_t vertice1, uint16_t vertice2, uint32_t edgeWeight) {
    if (vertice1 == vertice2)
        return;
    if (vertice1 > vertice2)
        std::swap(vertice1, vertice2);
    if (!edgesWeights.contains(std::make_pair(vertice1, vertice2))) {
        edges[vertice1].push_back(vertice2);
        edges[vertice2].push_back(vertice1);
        edgesWeights[std::make_pair(vertice1, vertice2)] = edgeWeight;
        return;
    }
    if (edgeWeight < edgesWeights[std::make_pair(vertice1, vertice2)])
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
    return edges[vertice];
}

class PriorityQueue {
    public:
        void Add(uint32_t, uint16_t);
        void DecreaseKey(uint32_t, uint32_t, uint16_t);
        std::pair<uint32_t, uint16_t> ExtractMin();
        bool IsEmpty() const;
    private:
        std::set<std::pair<uint32_t, uint16_t>> priorityQueue;
};
void PriorityQueue::Add(uint32_t distanceToVertice, uint16_t verticeIndex) {
    priorityQueue.insert(std::make_pair(distanceToVertice, verticeIndex));
}
void PriorityQueue::DecreaseKey(uint32_t prevDistanceToVertice, uint32_t distanceToVertice, uint16_t verticeIndex) {
    priorityQueue.extract(std::make_pair(prevDistanceToVertice, verticeIndex));
    priorityQueue.insert(std::make_pair(distanceToVertice, verticeIndex));
}
std::pair<uint32_t, uint16_t> PriorityQueue::ExtractMin() {
    std::pair<uint32_t, uint16_t> minElement = *priorityQueue.begin();
    priorityQueue.extract(std::make_pair(priorityQueue.begin()->first, priorityQueue.begin()->second));
    return minElement;
}
bool PriorityQueue::IsEmpty() const {
    return priorityQueue.empty();
}

bool IsDistanceUpdated(const Graph& graph, std::vector<uint32_t>& shortestWays, uint16_t verticeFrom, uint16_t verticeTo) {
    if (shortestWays[verticeTo] > shortestWays[verticeFrom] + graph.GetEdgeWeight(verticeFrom, verticeTo)) {
        shortestWays[verticeTo] = shortestWays[verticeFrom] + graph.GetEdgeWeight(verticeFrom, verticeTo);
        return true;
    }
    return false;
}
uint32_t GetShortestWay(const Graph& graph, uint16_t verticeFrom, uint16_t verticeTo) {
    std::vector<uint32_t> shortestWays(graph.GetVerticesCount(), UINT32_MAX);
    shortestWays[verticeFrom] = 0;
    PriorityQueue shortestWaysCounting;
    shortestWaysCounting.Add(shortestWays[verticeFrom], verticeFrom);
    while (!shortestWaysCounting.IsEmpty()) {
        std::pair<uint32_t, uint16_t> iVerticeFromInfo = shortestWaysCounting.ExtractMin();
        if (iVerticeFromInfo.second == verticeTo)
            return shortestWays[verticeTo];
        for (uint16_t iVerticeTo : graph.GetAllAdjacentVertices(iVerticeFromInfo.second)) {
            uint32_t shortestWayToIVerticeToCopy = shortestWays[iVerticeTo];
            if (shortestWayToIVerticeToCopy == UINT32_MAX) {
                shortestWays[iVerticeTo] = shortestWays[iVerticeFromInfo.second] + graph.GetEdgeWeight(iVerticeFromInfo.second, iVerticeTo);
                shortestWaysCounting.Add(shortestWays[iVerticeTo], iVerticeTo);
            }
            else if (IsDistanceUpdated(graph, shortestWays, iVerticeFromInfo.second, iVerticeTo))
                shortestWaysCounting.DecreaseKey(shortestWayToIVerticeToCopy, shortestWays[iVerticeTo], iVerticeTo);
        }
    }
    return shortestWays[verticeTo];
}

int32_t main() {
    uint16_t settlementsCount = 0;
    uint32_t roadsCount = 0;
    std::cin >> settlementsCount >> roadsCount;
    Graph map(settlementsCount);
    for (uint32_t i = 0; i < roadsCount; ++i) {
        uint16_t settlementFrom = 0;
        uint16_t settlementTo = 0;
        uint32_t distanceBetweenTwoSettlements = 0;
        std::cin >> settlementFrom >> settlementTo >> distanceBetweenTwoSettlements;
        map.AddEdge(settlementFrom, settlementTo, distanceBetweenTwoSettlements);
    }
    uint16_t settlementFrom = 0;
    uint16_t settlementTo = 0;
    std::cin >> settlementFrom >> settlementTo;
    std::cout << GetShortestWay(map, settlementFrom, settlementTo) << std::endl;
    return 0;
}

