#include <iostream>
#include <map>

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
	while (scanf("#%d @ %d,%d: %dx%d\n", &id, &l, &t, &w, &h) != -1) {
		for (int i = t;i < t + h;i++) {
			for (int j = l;j < l + w;j++) {
				cont[ponto(i, j)]++;
			}
		}
	}
	int s = 0;
	for (map<ponto,int>::iterator i=cont.begin();i!=cont.end();i++) {
		if (i->second >= 2) s++;
	}
	cout << s << endl;
	return 0;
}
