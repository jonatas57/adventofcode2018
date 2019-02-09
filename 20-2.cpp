#include <iostream>
#include <map>
#include <queue>
#include <stack>
#include <set>
#include <vector>

using namespace std;

typedef pair<int, int> ii;
#define INF 0x3f3f3f3f
#define SIZE 401

struct room {
	ii pos;
	bool visit;
	int dist;
	room** adj;

	room(ii p) : pos(p), visit(false), dist(INF) {
		adj = new room*[4];
		memset(adj, 0, 4 * sizeof(room*));
	}
};
ii operator+(ii& a, ii& b) {
	return ii(a.first + b.first, a.second + b.second);
}

room*** mapa = new room**[SIZE];
room* newRoom(ii p) {
	room* r;
	if (mapa[p.first][p.second]) r = mapa[p.first][p.second];
	else r = new room(p);
	//cerr << r << endl;
	return r;
}

map<char, ii> dir = {{'N', ii(-1, 0)}, {'E', ii(0, 1)}, {'W', ii(0, -1)}, {'S', ii(1, 0)}};
map<char, int> num = {{'N', 0}, {'E', 1}, {'W', 3}, {'S', 2}};

int bfs(room* st) {
	st->visit = true;
	st->dist = 0;
	int d = 0;
	queue<room*> q;
	q.push(st);
	while (!q.empty()) {
		room *x = q.front(); q.pop();
		for (int i = 0;i < 4;i++) {
			room *y = x->adj[i];
			if (y) {
				if (!y->visit) {
					y->visit = true;
					q.push(y);
				}
				int aux = x->dist + 1;
				if (y->dist > aux) {
					bool p = y->dist >= 1000 && y->dist != INF;
					y->dist = aux;
					bool q = y->dist >= 1000;
					if (p && !q) d--;
					if (!p && q) d++;
				}
			}
		}
	}
	return d;
}

int main() {
	string s;
	for (int i = 0;i < SIZE;i++) {
		mapa[i] = new room*[SIZE];
		for (int j = 0;j < SIZE;j++) {
			mapa[i][j] = nullptr;
		}
	}
	cin >> s;

	int mid = SIZE / 2;
	room* start = mapa[mid][mid] = new room(ii(mid, mid));

	stack<set<room*>> tops, ends;
	set<room*> act;
	ends.push(act);
	act.insert(start);
	for (char c : s) {
		if (c == '(') {
			tops.push(act);
			ends.push(set<room*>());
		}
		else if (c == ')') {
			tops.pop();
			auto x = ends.top();
			x.insert(act.begin(), act.end());
			act = x;
			ends.pop();
		}
		else if (c == '|') {
			auto x = ends.top();
			x.insert(act.begin(), act.end());
			act = tops.top();
		}
		else if (c != '^' && c != '$') {
			set<room*> aux;
			for (auto& r : act) {
				ii npos = r->pos + dir[c];
				room* q = mapa[npos.first][npos.second] = newRoom(npos);
//				cout << q << " ";
				r->adj[num[c]] = q;
				q->adj[(num[c] + 2) % 4] = r;
				aux.insert(q);
			}
			act = aux;
		}
//			cout << endl;
	}
//	for (int i = 0;i < SIZE;i++) {
//		bool p = false, col;
//		for (int j = 0;j < SIZE;j++) {
//			if (i == j && i== SIZE/2) col= true; else col = false;
//			if (mapa[i][j]) {
//				p = true;
//				printf(col ? "\x1b[033m1\x1b[m" : "1");
//			}
//		}
//		if (p) cout << endl;
//	}
//	cout << mapa[mid][mid - 23] << endl << mapa[mid + 1][mid - 23] << endl;
  int maxd = bfs(start);
	cout << maxd << endl;
	return 0;
}
