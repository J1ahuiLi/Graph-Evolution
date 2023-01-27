#include "defns.h"
#define INF (~(0x1<<31))

using namespace std;

int getWeight(int start, int end, vexterNode* adjList) {
	if (start == end) {
		return 0;
	}
	edgeNode* node = adjList[start].firstEdge;
	while (node != nullptr) {
		if (end == node->indexVex) {
			return node->weight;
		}
		node = node->nextEdge;
	}
	return INF;
}

void floyd(int path[][10000], int floy[][10000], int vertexNum, vexterNode* adjList) {
	int i, j, k;
	int tmp;

	for (i = 0; i < vertexNum; i++) {
		for (j = 0; j < vertexNum; j++) {
			floy[i][j] = getWeight(i, j, adjList);
			path[i][j] = j;
		}
	}

	for (k = 0; k < vertexNum; k++) {
		for (i = 0; i < vertexNum; i++) {
			for (j = 0; j < vertexNum; j++) {
				tmp = (floy[i][k] == INF || floy[k][j] == INF) ? INF : (floy[i][k] + floy[k][j]);
				if (floy[i][j] > tmp) {
					floy[i][j] = tmp;
					path[i][j] = path[i][k];
				}
			}
		}
	}
}