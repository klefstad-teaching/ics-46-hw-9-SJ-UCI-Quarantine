#include "dijkstras.h"

vector<int> dijkstra_shortest_path(const Graph& graph, int src, vector<int>& prev) {
	vector<int> dist(graph.numVertices, INF);
	vector<bool> visited(graph.numVertices, false);
	auto cmp = [&](auto& a, auto& b) {
		return a.second > b.second;
	};
	priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(cmp)> q(cmp);
	dist[src] = 0;
	q.push({src, 0});
	while(!q.empty()) {
		int curr = q.top().first;
		q.pop();
		if(!visited[curr]) {
			visited[curr] = true;
			for(const Edge& e : graph[curr]) {
				if(!visited[e.dst]) {
					int d = dist[curr] + e.weight;
					if(d < dist[e.dst]) {
						dist[e.dst] = d;
						prev[e.dst] = curr;
						q.push({e.dst, d});
					}
				}
			}
		}
	}
	return dist;
}

vector<int> extract_shortest_path(const vector<int>& dist, const vector<int>& prev, int dst) {
	if(dist[dst] == INF) return {};
	vector<int> path;
	while(prev[dst] != -1) {
		path.push_back(dst);
		dst = prev[dst];
	}
	path.push_back(dst);
	int n = path.size(), half = n / 2;
	for(int i = 0; i < half; ++i) {
		int t = path[i];
		path[i] = path[n - 1 - i];
		path[n - 1 - i] = t;
	}
	return path;
}

void print_path(const vector<int>& v, int total) {
	for(int i : v) cout << i << ' ';
	cout << endl;
	cout << "Total cost is " << total << endl;
}
