#include "dijkstras.h"

int main() {
	Graph g;
	file_to_graph("src/largest.txt", g);
	vector<int> p(g.numVertices, -1);
	vector<int> v = dijkstra_shortest_path(g, 0, p);
	for(int i : v) cout << i << ' ';
	cout << endl;
	vector<int> v2 = extract_shortest_path(v, p, 10);
	for(int i : v2) cout << i << ' ';
	cout << endl;
}
