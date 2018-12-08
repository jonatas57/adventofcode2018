#include <iostream>
#include <cmath>
#include <map>
#include <set>
#include <vector>

using namespace std;

#define INF 0x3f3f3f3f

struct ponto {
	int x, y;

	ponto(int x=0, int y=0) : x(x), y(y) {}
	bool operator<(const ponto& p) const {
		if (x < p.x) return true;
		return (x == p.x && y < p.y);
	}
	bool operator==(const ponto& p) const {
		return (x == p.x && y == p.y);
	}
};

int mdist(ponto& p, ponto& q) {
	return abs(p.x - q.x) + abs(p.y - q.y);
}

int top = 1, lft = 1, bottom= 0, rgt = 1;

int main() {
	int x, y;
	int minx = INF, miny = INF, maxx = 0, maxy = 0;
	vector<ponto> ps;
	while (scanf("%d, %d", &x, &y) != -1) {
		ps.push_back(ponto(x, y));
		minx = min(x, minx);
		miny = min(y, miny);
		maxx = max(x, maxx);
		maxy = max(y, maxy);
	}
	set<ponto> borda;
	map<ponto, int> area;
	map<ponto, ponto> near;
	for (int i = minx - lft;i <= maxx + rgt;i++){
		for (int j = miny - top;j <= maxy + bottom;j++) {
			ponto q(i, j);
			set<ponto> aux;
			int mind = INF;
			for (ponto& p : ps) {
				int d = mdist(p, q);
				if (mind > d) {
					mind = d;
					aux.clear();
					aux.insert(p);
				}
				else if (mind == d) {
					aux.insert(p);
				}
			}
			if (aux.size() == 1) {
				area[*aux.begin()]++;
				near[q] = *aux.begin();
			}
			if (i == minx-lft||i==maxx+rgt||j==miny-top||j==maxy+bottom){
				borda.insert(near[q]);
			}
		}
	}
	ponto ans(0,0);
	int maxa = 0;
	for (ponto& p : ps) {
		cout << area[p] << endl;
		if (maxa < area[p] && borda.find(p) == borda.end()) {
			ans = p;
			maxa = area[p];
		}
	}
	cout << maxa << endl;
	cout << ans.x << ' ' << ans.y << endl;
	return 0;
}
