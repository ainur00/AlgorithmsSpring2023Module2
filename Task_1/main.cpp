#include <iostream>

#include "Files/Hpp/Graph.hpp"
#include "Files/Hpp/ListGraph.hpp"
#include "Files/Hpp/MatrixGraph.hpp"
#include "Files/Hpp/SetGraph.hpp"
#include "Files/Hpp/ArcGraph.hpp"

struct GraphVertexDegreeInfo {
    uint64_t minimum = UINT64_MAX;
    uint64_t average = 0;
    uint64_t maximum = 0;
};
std::ostream& operator<<(std::ostream& os, const GraphVertexDegreeInfo& graphVertexDegreeInfo) {
    os << "{minimum: " << graphVertexDegreeInfo.minimum << "; maximum: " << graphVertexDegreeInfo.maximum << "; average: " << graphVertexDegreeInfo.average << "}";
    return os;
}

GraphVertexDegreeInfo GetVertexDegreeInfo(const IGraph* graph) {
    GraphVertexDegreeInfo graphVertexDegreeInfo;
    for (uint64_t v = 0; v < graph->VerticesCount(); ++v) {
        uint64_t vDegree = graph->GetAllAdjacentIn(v).size() + graph->GetAllAdjacentOut(v).size();
        graphVertexDegreeInfo.minimum = std::min(graphVertexDegreeInfo.minimum, vDegree);
        graphVertexDegreeInfo.maximum = std::max(graphVertexDegreeInfo.maximum, vDegree);
        graphVertexDegreeInfo.average += vDegree;
    }
    graphVertexDegreeInfo.average /= graph->VerticesCount();
    return graphVertexDegreeInfo;
}

void AddArcs(IGraph* graph, uint64_t verticesCount) {
    for (uint64_t u = 0; u < verticesCount; ++u)
        for (uint64_t v = 0; v < verticesCount; ++v)
            if (std::rand() % 4 == 0)
                graph->AddEdge(u, v);
}

int32_t main() {
    uint64_t verticesCount = 1000;
    
    // ListGraph
    ListGraph listGraph0(verticesCount);
    AddArcs(&listGraph0, verticesCount);
    ListGraph listGraphFromListGraph(&listGraph0);
    MatrixGraph matrixGraphFromListGraph(&listGraph0);
    SetGraph setGraphFromListGraph(&listGraph0);
    ArcGraph arcGraphFromListGraph(&listGraph0);
    
    // MatrixGraph
    MatrixGraph matrixGraph0(verticesCount);
    AddArcs(&matrixGraph0, verticesCount);
    ListGraph listGraphFromMatrixGraph(&matrixGraph0);
    MatrixGraph matrixGraphFromMatrixGraph(&matrixGraph0);
    SetGraph setGraphFromMatrixGraph(&matrixGraph0);
    ArcGraph arcGraphFromMatrixGraph(&matrixGraph0);
    
    // SetGraph
    SetGraph setGraph0(verticesCount);
    AddArcs(&setGraph0, verticesCount);
    ListGraph listGraphFromSetGraph(&setGraph0);
    MatrixGraph matrixGraphFromSetGraph(&setGraph0);
    SetGraph setGraphFromSetGraph(&setGraph0);
    ArcGraph arcGraphFromSetGraph(&setGraph0);
    
    // ArcGraph
    ArcGraph arcGraph0(verticesCount);
    AddArcs(&arcGraph0, verticesCount);
    ListGraph listGraphFromArcGraph(&arcGraph0);
    MatrixGraph matrixGraphFromArcGraph(&arcGraph0);
    SetGraph setGraphFromArcGraph(&arcGraph0);
    ArcGraph arcGraphFromArcGraph(&arcGraph0);

    // ListGraphOut
    std::cout << "ListGraphInfo" << std::endl;
    std::cout << "listGraph0:                 " << GetVertexDegreeInfo(&listGraph0) << std::endl;
	std::cout << "listGraphFromListGraph:     " << GetVertexDegreeInfo(&listGraphFromListGraph) << std::endl;
	std::cout << "matrixGraphFromListGraph:   " << GetVertexDegreeInfo(&matrixGraphFromListGraph) << std::endl;
	std::cout << "setGraphFromListGraph:      " << GetVertexDegreeInfo(&setGraphFromListGraph) << std::endl;
	std::cout << "arcGraphFromListGraph:      " << GetVertexDegreeInfo(&arcGraphFromListGraph) << std::endl;
	std::cout << std::endl;

	// MatrixGraphOut
    std::cout << "MatrixGraphInfo" << std::endl;
    std::cout << "matrixGraph0:               " << GetVertexDegreeInfo(&matrixGraph0) << std::endl;
	std::cout << "listGraphFromMatrixGraph:   " << GetVertexDegreeInfo(&listGraphFromMatrixGraph) << std::endl;
	std::cout << "matrixGraphFromMatrixGraph: " << GetVertexDegreeInfo(&matrixGraphFromMatrixGraph) << std::endl;
	std::cout << "setGraphFromMatrixGraph:    " << GetVertexDegreeInfo(&setGraphFromMatrixGraph) << std::endl;
	std::cout << "arcGraphFromMatrixGraph:    " << GetVertexDegreeInfo(&arcGraphFromMatrixGraph) << std::endl;
	std::cout << std::endl;

	// SetGraphOut
    std::cout << "SetGraphInfo" << std::endl;
    std::cout << "setGraph0:                  " << GetVertexDegreeInfo(&setGraph0) << std::endl;
	std::cout << "listGraphFromSetGraph:      " << GetVertexDegreeInfo(&listGraphFromSetGraph) << std::endl;
	std::cout << "matrixGraphFromSetGraph:    " << GetVertexDegreeInfo(&matrixGraphFromSetGraph) << std::endl;
	std::cout << "setGraphFromSetGraph        " << GetVertexDegreeInfo(&setGraphFromSetGraph) << std::endl;
	std::cout << "arcGraphFromSetGraph:       " << GetVertexDegreeInfo(&arcGraphFromSetGraph) << std::endl;
	std::cout << std::endl;

	// ArcGraph
    std::cout << "ArcGraphInfo" << std::endl;
    std::cout << "arcGraph0:                  " << GetVertexDegreeInfo(&arcGraph0) << std::endl;
	std::cout << "listGraphFromArcGraph:      " << GetVertexDegreeInfo(&listGraphFromArcGraph) << std::endl;
	std::cout << "matrixGraphFromArcGraph:    " << GetVertexDegreeInfo(&matrixGraphFromArcGraph) << std::endl;
	std::cout << "setGraphFromArcGraph        " << GetVertexDegreeInfo(&setGraphFromArcGraph) << std::endl;
	std::cout << "arcGraphFromArcGraph:       " << GetVertexDegreeInfo(&arcGraphFromArcGraph) << std::endl;

    return 0;
}

