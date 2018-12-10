#include <iostream>
#include <vector>
#include <cstdlib>
#include <string>

using namespace std;

typedef struct ponto {
	int x, y;

	ponto(int x, int y) : x(x), y(y) {}
	void operator+=(ponto& p) {
		x += p.x;
		y += p.y;
	}
} vetor;

struct light {
	ponto pos;
	vetor vel;

	light(ponto p, vetor v) : pos(p), vel(v) {}
	void update() {
		pos += vel;
	}
	void rupdate() {
		vetor rvel = vetor(-vel.x, -vel.y);
		pos += rvel;
	}
};

int hscwid=45;

int* minimax(vector<light>& ls) {
	int maxh = -0x3f3f3f3f, minh = 0x3f3f3f3f;
	int maxw = -0x3f3f3f3f, minw = 0x3f3f3f3f;
	for (light& l : ls) {
		maxh = max(l.pos.y, maxh);
		minh = min(l.pos.y, minh);
		maxw = max(l.pos.x, maxw);
		minw = min(l.pos.x, minw);
	}
	int *x = new int[4]{minh, maxh, minw, maxw};
	return x;
}

void print(vector<light>& ls, int* x) {
	string ss[x[0]];
	for (int i = 0;i < x[0];i++) ss[i] = string(x[1], ' ');
	int *mm = minimax(ls);
	for (light& l : ls) {
		ss[l.pos.y - mm[0]][l.pos.x - mm[2]] = '#';
	}
	for (string& s : ss) cout << s << endl;
}

int* dim(vector<light>& ls) {
	int *mm = minimax(ls);
	int *x = new int[2] {mm[1] - mm[0] + 1, mm[3] - mm[2] + 1};
	return x;
}

int main() {
	vector<light> ls;
	int rx, ry, vx, vy;
	while (scanf("position=<%d, %d> velocity=<%d, %d>\n", &rx, &ry, &vx, &vy) != -1) {
		ls.push_back(light(ponto(rx, ry), vetor(vx, vy)));
	}
	int h = 0x3f3f3f3f;
	int acth = dim(ls)[0];
	while (h > acth) {
		h = acth;
		for (light& l : ls) l.update();
		acth = dim(ls)[0];
	}
	for(light& l : ls) l.rupdate();
	int* x = dim(ls);
	print(ls, x);
	return 0;
}
