struct edges {
	int start;
	int end;
};

struct datas {
	int index;
	int year;
};

struct edgeNode {
	int indexVex;
	int weight;
	edgeNode* nextEdge;
};

struct vexterNode {
	int data;
	edgeNode* firstEdge;
};