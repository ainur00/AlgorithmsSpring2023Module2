#include <cstdint>
#include <iostream>
#include <queue>
#include <vector>

class Graph {
    public:
        Graph(uint16_t);
        void AddEdge(uint16_t, uint16_t);
        uint16_t GetVerticesCount() const;
        std::vector<uint16_t> GetAllAdjacentVertices(uint16_t) const;
    private:
        uint16_t verticesCount;
        std::vector<std::vector<uint16_t>> edges;
};
Graph::Graph(uint16_t verticesCount) : verticesCount(verticesCount), edges(verticesCount) {}
void Graph::AddEdge(uint16_t vertice1, uint16_t vertice2) {
    edges[vertice1].push_back(vertice2);
    edges[vertice2].push_back(vertice1);
}
uint16_t Graph::GetVerticesCount() const {
    return verticesCount;
}
std::vector<uint16_t> Graph::GetAllAdjacentVertices(uint16_t verticeFrom) const {
    return edges[verticeFrom];
}

uint16_t GetShortestWaysCount(const Graph& graph, uint16_t verticeFrom, uint16_t verticeTo) {
    std::vector<uint16_t> shortestWays(graph.GetVerticesCount(), UINT16_MAX);
    std::vector<uint16_t> shortestWaysCounts(graph.GetVerticesCount(), 0);
    std::queue<uint16_t> waysCounting;
    shortestWays[verticeFrom] = 0;
    shortestWaysCounts[verticeFrom] = 1;
    waysCounting.push(verticeFrom);
    while (!waysCounting.empty()) {
        uint16_t iVerticeFrom = waysCounting.front();
        waysCounting.pop();
        if (iVerticeFrom == verticeTo)
            break;
        for (uint16_t iVerticeTo : graph.GetAllAdjacentVertices(iVerticeFrom)) {
            if (shortestWays[iVerticeTo] == UINT16_MAX) {
                shortestWays[iVerticeTo] = shortestWays[iVerticeFrom] + 1;
                waysCounting.push(iVerticeTo);
            }
            if (shortestWays[iVerticeTo] == shortestWays[iVerticeFrom] + 1)
                shortestWaysCounts[iVerticeTo] += shortestWaysCounts[iVerticeFrom];
        }
    }
    return shortestWaysCounts[verticeTo];
}

int32_t main() {
    uint16_t verticesCount = 0;
    uint32_t edgesCount = 0;
    std::cin >> verticesCount >> edgesCount;
    Graph graph(verticesCount);
    for (uint32_t i = 0; i < edgesCount; ++i) {
        uint16_t vertice1 = 0;
        uint16_t vertice2 = 0;
        std::cin >> vertice1 >> vertice2;
        graph.AddEdge(vertice1, vertice2);
    }
    uint16_t verticeFrom = 0;
    uint16_t verticeTo = 0;
    std::cin >> verticeFrom >> verticeTo;
    std::cout << GetShortestWaysCount(graph, verticeFrom, verticeTo) << std::endl;
    return 0;
}

