#include <iostream>
#include <stack>
#include "defns.h"

using namespace std;

int tiMe = 1, group_index = 0;
int* subNum = new int[10000]();
stack<int> s;

void recursionDFS(int i, int* visited, vexterNode* adjList, int* dfn, int* low) {
	dfn[i] = low[i] = tiMe++;
	visited[i] = 1;
	s.push(i);

	edgeNode* node = adjList[i].firstEdge;
	while (node != NULL) {
		if (!dfn[node->indexVex]) {
			recursionDFS(node->indexVex, visited, adjList, dfn, low);
			low[i] = min(low[node->indexVex], low[i]);
		}
		else if (visited[node->indexVex] == 1) {
			low[i] = min(low[node->indexVex], low[i]);
		}
		node = node->nextEdge;
	}

	if (dfn[i] == low[i]) {
		int v;
		group_index++;
		do {
			v = s.top();
			subNum[group_index] += 1;
			visited[v] = 0;
			s.pop();
		} while (v != i);
	}
}

void DFS(int vertexNum, vexterNode* adjList) {
	int* visited = new int[10000]();
	int* dfn = new int[10000]();
	int* low = new int[10000]();

	for (int i = 0; i < vertexNum; i++) {
		if (!dfn[i]) {
			recursionDFS(i, visited, adjList, dfn, low);
		}
	}
	cout << "The graph G has " << group_index << " strongly connected components:" << endl;
	cout << "\tSize : Number" << endl;
	int* sccResult = new int[group_index + 1]();

	for (int i = 1; i <= group_index; i++) {
		sccResult[subNum[i]]++;
	}
	for (int i = 0; i <= group_index; i++) {
		if (sccResult[i] != 0) {
			cout << "\t" << i << " : " << sccResult[i] << endl;
		}
	}
}