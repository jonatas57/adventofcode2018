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
	int areat = 10000;
	int area = 0;
	for (int i = minx;i <= maxx;i++){
		for (int j = miny;j <= maxy;j++) {
			ponto q(i, j);
			int sumd = 0;
			for (ponto& p : ps) {
				sumd += mdist(p, q);
			}
			if (sumd <= areat) {
				area++;
			}
		}
	}
	cout << area << endl;
	return 0;
}
