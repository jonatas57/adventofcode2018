#include <iostream>
#include <vector>
#include <list>
#include <set>
#include <algorithm>

using namespace std;

struct grafo {
	int n;
	vector<list<int>> adj;

	grafo(int n) : n(n) {
		adj.resize(n);
	}
	void addEdge(int u, int v) {
		adj[u].push_back(v);
	}
	auto& operator[](int c) {
		return adj[c];
	}
	void print() {
		for (int i = 0;i < n;i++) {
			cout << (char)(i + 'A');
			for (auto& j : adj[i]) {
				cout << " -> " << (char)(j + 'A');
			}
			cout << " ->//" << endl;
		}
	}
};

vector<int> root(grafo& g) {
	vector<int> d(g.n, 0);
	for (int i = 0;i < g.n;i++) {
		for (int x : g[i]) {
			d[x]++;
		}
	}
	return d;
}

void print(vector<int>& v) {
	for (int x : v) {
		cout << x << " ";
	}
	cout << endl;
}

int main() {
	grafo g(26);
	char x, y;
	while (scanf("Step %c must be finished before step %c can begin.\n", &x, &y) != -1) {
		g.addEdge((int)x - 'A', (int)y - 'A');
	}
	vector<int> r = root(g);
	string s = "";
	print(r);
	for (int i = 0;s.length() < 26;i++) {
		if (r[i] == 0) {
			s += (char)(i + 'A');
			r[i] = -1;
			for (int j : g[i]) {
				r[j]--;
			}
			print(r);
			i = -1;
		}
	}
	cout << s << endl;
	return 0;
} 
