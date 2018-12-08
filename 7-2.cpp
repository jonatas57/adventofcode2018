#include <iostream>
#include <vector>
#include <list>
#include <set>
#include <algorithm>

using namespace std;

int adt = 60;

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

struct worker {
	int task;
	int time;
	bool busy, done;

	worker() : busy(false) {}
	void assign(int t) {
		task = t + 1;
		time = adt + t +1;
		busy = true;
	}
	void update() {
		done = false;
		if (busy) {
			time--;
			if (!time) {
				done = true;
				busy = false;
			}
		}
	}
};

int main() {
	int n = 26, nw = 4;
	grafo g(n);
	char x, y;
	while (scanf("Step %c must be finished before step %c can begin.\n", &x, &y) != -1) {
		g.addEdge((int)x - 'A', (int)y - 'A');
	}
	vector<int> r = root(g);
	string s = "";
	set<int> able;
	int time = 0;
	for (int i = 0;i < n;i++) if (r[i] == 0) able.insert(i);
	vector<worker> elfs(nw, worker());
	while (s.length() < n) {
		for (worker& w : elfs) {
			if (!w.busy && !able.empty()) {
				w.assign(*able.begin());
				able.erase(able.begin());
			}
		}
		for (worker& w : elfs) {
			w.update();
			if (w.done) {
				s += (char)(w.task + 'A'-1);
				for (int e : g[w.task-1]) {
					r[e]--;
					if (r[e] == 0) {
						r[e] = -1;
						able.insert(e);
					}
				}
			}
		}
		time++;
	}
	cout << time << endl;
	return 0;
} 
