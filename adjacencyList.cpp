#include "defns.h"

using namespace std;

int getPosition(int paperNum, vexterNode* adjList, int vertexNum) {
	int i;
	for (i = 0; i < vertexNum; i++) {
		if (adjList[i].data == paperNum) {
			return i;
		}
	}
	return -1;
}

void linkLast(edgeNode* list, edgeNode* node) {
	edgeNode* p = list;
	while (p->nextEdge) {
		p = p->nextEdge;
	}
	p->nextEdge = node;
}

int Length(edgeNode* head) {
	int c = 0;
	if (head == nullptr) {
		return 0;
	}
	else {
		edgeNode* S = head;
		while (S != nullptr) {
			c++;
			S = S->nextEdge;
		}
		return c;
	}
}

void adj(int edgeNum, int startVertex, int endVertex, int posStartVertex, int posEndVertex, int** edge, int vertexNum, vexterNode* adjList) {
	for (int i = 0; i < edgeNum; i++) {
		startVertex = edge[i][0];
		endVertex = edge[i][1];
		posStartVertex = getPosition(startVertex, adjList, vertexNum);
		posEndVertex = getPosition(endVertex, adjList, vertexNum);

		edgeNode* chainNode = new edgeNode();
		chainNode->indexVex = posEndVertex;
		chainNode->weight = 1;

		if (adjList[posStartVertex].firstEdge == nullptr) {
			adjList[posStartVertex].firstEdge = chainNode;
		}
		else {
			linkLast(adjList[posStartVertex].firstEdge, chainNode);
		}
	}
}