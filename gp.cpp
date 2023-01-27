#include <iostream>
#include <fstream>
#include <sstream>
#include "defns.h"
#include "adjacencyList.h"
#include "sort.h"
#include "dfs.h"
#include "floyd.h"
#include "utility.h"

using namespace std;

int main(int argc, char** argv) {
	int edgeFileLine = countLines(argv[1]);
	int indexEdgesFile = 0;
	edges* edgesFile = new edges[edgeFileLine]();
	ifstream edgesFileRead;
	edgesFileRead.open(argv[1], ios::in);
	if (edgesFileRead.fail()) {
		cout << "edges.txt read error" << endl;
		edgesFileRead.close();
	}
	else {
		string str;
		while (getline(edgesFileRead, str)) {
			stringstream input(str);
			input >> edgesFile[indexEdgesFile].start;
			input >> edgesFile[indexEdgesFile].end;
			indexEdgesFile++;
		}
		edgesFileRead.close();
	}

	int dataFileLine = countLines(argv[2]);
	int indexDatasFile = 0;
	datas* datasFile = new datas[dataFileLine]();
	ifstream datasFileRead;
	datasFileRead.open(argv[2], ios::in);
	if (datasFileRead.fail()) {
		cout << "datas.txt read error" << endl;
		datasFileRead.close();
	}
	else {
		string str;
		while (getline(datasFileRead, str)) {
			stringstream input(str);
			input >> datasFile[indexDatasFile].index;
			input >> datasFile[indexDatasFile].year;
			indexDatasFile++;
		}
		datasFileRead.close();
	}

	string command[3];
	ifstream commandsFileRead;
	commandsFileRead.open(argv[3], ios::in);
	if (commandsFileRead.fail()) {
		cout << "commands.txt read error" << endl;
		commandsFileRead.close();
	}
	else {
		string str;
		int task = 0;
		getline(commandsFileRead, str);
		istringstream input(str);
		string output;
		int indexCommand = 0;
		while (input >> output) {
			command[indexCommand] = output;
			indexCommand++;
		}
		if (command[0] != "start-graph") {
			cout << "start error" << endl;
		}

		int vertexNum = 0;
		for (int i = 0; i < dataFileLine; i++) {
			if (datasFile[i].year >= stoi(command[1]) && datasFile[i].year <= stoi(command[2])) {
				vertexNum++;
			}
		}

		int* vertex = new int[vertexNum]();
		int indexVertex = 0;
		for (int i = 0; i < dataFileLine; i++) {
			if (datasFile[i].year >= stoi(command[1]) && datasFile[i].year <= stoi(command[2])) {
				vertex[indexVertex] = datasFile[i].index;
				indexVertex++;
			}
		}

		InsertionSort(vertex, vertexNum - 1);

		//Get data in range
		edges* tempEdgeStart = new edges[edgeFileLine]();
		int tempEdgeFirstNumF = 0;
		for (int i = 0; i < edgeFileLine; i++) {
			for (int n = 0; n < vertexNum; n++) {
				if (edgesFile[i].start == vertex[n]) {
					tempEdgeStart[tempEdgeFirstNumF].start = edgesFile[i].start;
					tempEdgeStart[tempEdgeFirstNumF].end = edgesFile[i].end;
					tempEdgeFirstNumF++;
				}
			}
		}
		edges* tempEdgeEnd = new edges[tempEdgeFirstNumF]();
		int edgeNum = 0;
		for (int i = 0; i < tempEdgeFirstNumF; i++) {
			for (int n = 0; n < vertexNum; n++) {
				if (tempEdgeStart[i].end == vertex[n]) {
					tempEdgeEnd[edgeNum].start = tempEdgeStart[i].start;
					tempEdgeEnd[edgeNum].end = tempEdgeStart[i].end;
					edgeNum++;
				}
			}
		}

		InsertionSortEdge(tempEdgeEnd, edgeNum);

		int** edge = new int* [edgeNum];
		for (int i = 0; i < edgeNum; i++) {
			edge[i] = new int[2];
		}

		int indexEdge = 0;
		for (int i = 0; i < edgeNum; i++) {
			edge[indexEdge][0] = tempEdgeEnd[i].start;
			edge[indexEdge][1] = tempEdgeEnd[i].end;
			indexEdge++;
		}
		delete[]tempEdgeStart;
		delete[]tempEdgeEnd;


		vexterNode* adjList = new vexterNode[vertexNum];
		for (int i = 0; i < vertexNum; i++) {
			adjList[i].data = vertex[i];
			adjList[i].firstEdge = NULL;
		}

		int startVertex = -1, endVertex = -1, posStartVertex = -1, posEndVertex = -1;
		adj(edgeNum, startVertex, endVertex, posStartVertex, posEndVertex, edge, vertexNum, adjList);

		cout << "Command: start-graph " << command[1] << " " << command[2] << '\n' << endl;
		cout << "The graph G for the years " << command[1] << " " << command[2] << " has:" << endl;
		cout << "\t|V| = " << vertexNum << " vertices" << endl;
		cout << "\t|E| = " << edgeNum << " edges" << '\n' << endl;

		string instr;
		while (getline(commandsFileRead, str)) {
			istringstream input(str);
			int indexCommand = 0;
			input >> instr;
			if (instr == "out-degree") {
				cout << "Command: out-degree" << '\n' << endl;
				task = 1;
			}
			else if (instr == "diameter") {
				cout << "Command: diameter" << '\n' << endl;
				task = 2;
			}
			else if (instr == "scc") {
				cout << "Command: scc" << '\n' << endl;
				task = 3;
			}
			else if (instr == "end-graph") {
				task = 4;
			}
			else {
				cout << "ERROR!" << endl;
			}

			switch (task) {
			case 1: {
				double avgOutDegree = (double)edgeNum / (double)vertexNum;
				string range = to_string(round(avgOutDegree, 2));
				if (range.substr(3, 1) == "0") {
					cout << "The graph G has average out-degree " << edgeNum << "/" << vertexNum << " = " << round(avgOutDegree, 2) << "0." << '\n' << endl;
				}
				else {
					cout << "The graph G has average out-degree " << edgeNum << "/" << vertexNum << " = " << round(avgOutDegree, 2) << "." << '\n' << endl;
				}

				int* outDegree = new int[vertexNum]();
				for (int i = 0; i < vertexNum; i++) {
					outDegree[i] = Length(adjList[i].firstEdge);
				}
				int count[1000];
				for (int i = 0; i < 1000; i++) {
					count[i] = 0;
				}
				for (int i = 0; i < vertexNum; i++) {
					int temp = outDegree[i];
					count[temp] = count[temp] + 1;
				}
				cout << "The out-degree distribution is:" << endl;
				cout << "\tOut-degree : Number of vertices" << endl;
				for (int i = 0; i < 1000; i++) {
					if (count[i] != 0) {
						cout << "\t" << i << " : " << count[i] << endl;
					}
				}
				cout << '\n';
				break; }
			case 2: {
				static int path[10000][10000] = { 0 };
				static int floy[10000][10000] = { 0 };
				floyd(path, floy, vertexNum, adjList);
				cout << "The graph G has diameter " << maxNum(floy, vertexNum) << ".\n" << endl;
				break; }
			case 3: {
				DFS(vertexNum, adjList);
				break; }
			case 4: {
				exit(0);
				break; }
			}
		}
		commandsFileRead.close();
	}

	system("pause");
	return 0;
}