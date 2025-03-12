#include "dijkstras.h"

vector<int> dijkstra_shortest_path(const Graph& graph, int src, vector<int>& prev) {
	vector<int> dist(graph.numVertices, INF);
	vector<bool> visited(graph.numVertices, false);
	dist[src] = 0;
	auto cmp = [&](auto& a, auto& b) {
		return dist[a] < dist[b];
	};
	priority_queue<int, vector<int>, decltype(cmp)> q(cmp);
	q.push(src);
	while(!q.empty()) {
		int curr = q.top();
		q.pop();
		if(!visited[curr]) {
			visited[curr] = true;
			for(const Edge& e : graph[curr]) {
				int d = dist[curr] + e.weight;
				if(d < dist[e.dst]) {
					dist[e.dst] = d;
					prev[e.dst] = curr;
					q.push(e.dst);
				}
			}
		}
	}
	return dist;
}

vector<int> extract_shortest_path(const vector<int>&, const vector<int>& prev, int dst) {
	vector<int> path;
	while(prev[dst] != -1) {
		path.push_back(dst);
		dst = prev[dst];
	}
	path.push_back(dst);
	return path;
}

void print_path(const vector<int>& v, int total) {
	for(int i : v) cout << i << ' ';
	cout << endl;
	cout << "Total cost is " << total << endl;
}
