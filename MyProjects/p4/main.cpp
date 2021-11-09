#include <iostream>
#include <vector>
#include <sstream>
#include <limits>
#include <list>
#include <queue>

using namespace std;

struct Edge {
	size_t startnode, endnode, weight;
	explicit Edge(size_t startnode, size_t endnode, size_t weight) : startnode(startnode), endnode(endnode), weight(weight) {}
};

struct Node {
	size_t idx, degree, cost;
	bool visited, MSTvisited;
	vector<Edge*> pre, next;
	explicit Node(size_t idx, size_t degree, size_t cost, bool visited, bool MSTvisited) : idx(idx), degree(degree), cost(cost), visited(visited), MSTvisited(MSTvisited) {}
	~Node() {
		for (auto& e : next) {
			delete e;
		}
	}
};

struct Graph {
	size_t nodenum, srcidx, destidx;
	vector<Edge*> edge;
	vector<Node*> node;
	explicit Graph(size_t nodenum, size_t srcidx, size_t destidx) : nodenum(nodenum), srcidx(srcidx), destidx(destidx) {}
	~Graph() {
		for (auto& n : node) {
			delete n;
		}
	}
};

struct compMST {
	bool operator()(Edge* a, Edge* b) {
		return a->weight > b->weight;
	}
};

int main() {
	size_t nodenum, srcidx, destidx, startnode, endnode, weight;
	string str;
	stringstream ss;
	cin >> nodenum >> srcidx >> destidx;
	Graph graph{ nodenum, srcidx, destidx };
	graph.node.resize(nodenum);
	for (size_t i = 0; i < nodenum; ++i) {
		graph.node[i] = new Node{ i, 0, (numeric_limits<size_t>::max)(), false, false };
	}
	while (!cin.eof()) {
		getline(cin, str);
		if (str.empty()) {
			continue;
		}
		ss.clear();
		ss.str(str);
		ss >> startnode >> endnode >> weight;
		Edge* edge = new Edge{ startnode, endnode, weight };
		graph.node[startnode]->next.emplace_back(edge);
		graph.node[endnode]->pre.emplace_back(edge);
		graph.edge.emplace_back(edge);
		graph.node[endnode]->degree++;
	}

	// Shortest path
	priority_queue<pair<size_t, size_t>, vector<pair<size_t, size_t>>, greater<pair<size_t, size_t>>> priority;
	vector<size_t> distance(graph.nodenum, (numeric_limits<size_t>::max)());
	priority.emplace(make_pair(0, graph.srcidx));
	distance[graph.srcidx] = 0;
	while (!priority.empty()) {
		size_t temp = priority.top().second;
		priority.pop();
		for (Edge* edge : graph.node[temp]->next) {
			if (distance[edge->endnode] > distance[temp] + edge->weight) {
				distance[edge->endnode] = distance[temp] + edge->weight;
				priority.emplace(make_pair(distance[edge->endnode], edge->endnode));
			}
		}
	}
	if (distance[graph.destidx] != (numeric_limits<size_t>::max)()) {
		cout << "Shortest path length is " << distance[graph.destidx] << endl;
	}
	else {
		cout << "No path exists!" << endl;
	}

	// DAG
	vector<Node*> zero_indegree;
	size_t count = 0;
	for (size_t i = 0; i < graph.node.size(); ++i) {
		if (graph.node[i]->degree == 0) {
			graph.node[i]->visited = true;
			zero_indegree.push_back(graph.node[i]);
		}
	}
	while (!zero_indegree.empty()) {
		Node* temp = zero_indegree.back();
		zero_indegree.pop_back();
		count++;
		for (auto& e : temp->next) {
			graph.node[e->endnode]->degree--;
			if (graph.node[e->endnode]->degree == 0 && !graph.node[e->endnode]->visited) {
				graph.node[e->endnode]->visited = true;
				zero_indegree.push_back(graph.node[e->endnode]);
			}
		}
	}
	if (count == graph.nodenum) {
		cout << "The graph is a DAG" << endl;
	}
	else {
		cout << "The graph is not a DAG" << endl;
	}

	// MST
	size_t MSTweight = 0;
	priority_queue<Edge*, vector<Edge*>, compMST> pMST;
	auto t = graph.node[0];
	count = 1;
	while (true) {
		t->MSTvisited = true;
		for (auto& i : t->pre) {
			if (!graph.node[i->startnode]->MSTvisited) {
				pMST.push(i);
			}
		}
		for (auto& i : t->next) {
			if (!graph.node[i->endnode]->MSTvisited) {
				pMST.push(i);
			}
		}
		if (pMST.empty()) {
			break;
		}
		if (graph.node[pMST.top()->startnode]->MSTvisited && graph.node[pMST.top()->endnode]->MSTvisited) {
			pMST.pop();
			continue;
		}
		else if (graph.node[pMST.top()->endnode]->MSTvisited) {
			t = graph.node[pMST.top()->startnode];
			graph.node[pMST.top()->startnode]->MSTvisited = true;
			count++;
		}
		else {
			t = graph.node[pMST.top()->endnode];
			graph.node[pMST.top()->endnode]->MSTvisited = true;
			count++;
		}
		MSTweight += pMST.top()->weight;
		pMST.pop();
	}
	if (count == graph.nodenum) {
		cout << "The total weight of MST is " << MSTweight << endl;
	}
	else {
		cout << "No MST exists!" << endl;
	}

	return 0;
}