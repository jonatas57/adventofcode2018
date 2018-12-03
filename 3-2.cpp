#include <iostream>
#include <map>
#include <vector>

using namespace std;

struct ponto {
	int x, y;
	ponto (int x, int y) : x(x), y(y) {}
	bool operator<(const ponto& p) const {
		if (x < p.x) return true;
		if (x == p.x && y < p.y) return true;
		return false;
	}
};

int main() {
	int id, t, l, w, h;
	map<ponto, int> cont;
	vector<bool> ids(10000, 0);
	while (scanf("#%d @ %d,%d: %dx%d\n", &id, &l, &t, &w, &h) != -1) {
		ids[id] = true;
		for (int i = t;i < t + h;i++) {
			for (int j = l;j < l + w;j++) {
				ponto p(i,j);
				try {
					int y = cont.at(p);
					if (y != -1) {
						ids[y] = false;
					}
					ids[id] = false;
					cont[p] = -1;
				}
				catch (exception& e) {
					cont[ponto(i, j)] = id;
				}
			}
		}
	}
	for (int i = 0;i < 10000;i++) {
		if (ids[i])	{
			cout << i << endl;
		}
	}
	return 0;
}
