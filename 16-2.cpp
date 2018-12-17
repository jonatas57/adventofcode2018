#include <iostream>
#include <queue>
#include <vector>

using namespace std;

vector<int> reg(4, 0);

void addr(int a, int b, int c) {
	reg[c] = reg[a] + reg[b];
}
void addi(int a, int b, int c) {
	if (b > 3) return;
	reg[c] = reg[a] + b;
}
void mulr(int a, int b, int c) {
	reg[c] = reg[a] * reg[b];
}
void muli(int a, int b, int c) {
	if (b > 3) return;
	reg[c] = reg[a] * b;
}
void banr(int a, int b, int c) {
	reg[c] = reg[a] & reg[b];
}
void bani(int a, int b, int c) {
	if (b > 3) return;
	reg[c] = reg[a] & b;
}
void borr(int a, int b, int c) {
	reg[c] = reg[a] | reg[b];
}
void bori(int a, int b, int c) {
	if (b > 3) return;
	reg[c] = reg[a] | b;
}
void setr(int a, int b, int c) {
	reg[c] = reg[a];
}
void seti(int a, int b, int c) {
	reg[c] = a;
}
void gtir(int a, int b, int c) {
	if (a > 3) return;
	reg[c] = a > reg[b];
}
void gtri(int a, int b, int c) {
	if (b > 3) return;
	reg[c] = reg[a] > b;
}
void gtrr(int a, int b, int c) {
	reg[c] = reg[a] > reg[b];
}
void eqir(int a, int b, int c) {
	if (a > 3) return;
	reg[c] = a == reg[b];
}
void eqri(int a, int b, int c) {
	if (b > 3) return;
	reg[c] = reg[a] == b;
}
void eqrr(int a, int b, int c) {
	reg[c] = reg[a] == reg[b];
}

typedef void (*fn)(int, int, int);

fn func[16] = {addr, addi, mulr, muli, banr, bani, borr, bori, setr, seti, gtir, gtri, gtrr, eqir, eqri, eqrr};

bool comp(vector<int>& r, vector<int>& a) {
	bool p = true;
	for (int i = 0;i < 4 && p;i++) {
		p = p && (r[i] == a[i]);
	}
	return p;
}

vector<int> intersection(vector<int>& u, vector<int>& v) {
	vector<int> inter;
	int a = u.size(), b = v.size();
	for (int i = 0, j = 0;i < a && j < b;)  {
		if (u[i] == v[j]) {
			inter.push_back(u[i]);
			i++;j++;
		}
		else if (u[i] < v[j]) {
			i++;
		}
		else {
			j++;
		}
	}
	return inter;
}

int main() {
	char ch;
	vector<vector<int>> fs(16);
	while ((ch = getchar()) && ch == 'B') {
		for (int i = 0;i < 8;i++) getchar();
		vector<int> bef(4), aft(4);
		for (int i = 0;i < 4;i++) {
			cin >> bef[i];
			getchar();
		}
		getchar();
		int op, a, b, c;
		cin >> op >> a >> b >> c;
		for (int i = 0;i < 10;i++) getchar();
		for (int i = 0;i < 4;i++) {
			cin >> aft[i];
			getchar();
		}
		getchar();getchar();
		
		vector<int> aux;
		for (int i = 0;i < 16;i++) {
			reg = bef;
			func[i](a, b, c);
			if (comp(reg, aft)) {
				aux.push_back(i);
			}
		}
		if (fs[op].empty()) fs[op] = aux;
		else if (fs[op].size() > 1) {
			fs[op] = intersection(fs[op], aux);
		}
	}
	vector<int> funcs(16);
	int uno = 0;
	queue<int> unos;
	vector<bool> visit(16, false);
	while (uno < 16) {
		cout << "procurando" << endl << uno << endl;;
		for (int i = 0;i < 16;i++) {
			if (fs[i].size() == 1 && !visit[i]) {
				uno++;
				unos.push(fs[i][0]);
				visit[i] = true;
			}
		}
		while (!unos.empty()) {
			cout << "retirando" <<endl;
			int x = unos.front();unos.pop();
			for (vector<int>& v : fs) {
				if (v.size() > 1) {
					for (auto it = v.begin();it != v.end();it++) {
						if (*it == x) {
							v.erase(it);
							break;
						}
					}
				}
			}
		}
	}

	for (int i = 0;i < 16;i++) {
		funcs[i] = fs[i][0];
		for (int x : fs[i]) {
			cout << x << " ";
		}
		cout << endl;
	}
	cout << endl;
	getchar();
	int x, y, z, w;
	reg.clear();
	reg.resize(4, 0);
	while (cin >> x >> y >> z >> w) {
		cout << x << " " << y << " " << z << " " << w << endl;
		func[funcs[x]](y, z, w);
		for (int j : reg) {
			cout << j << " ";
		}
		cout << endl << endl;
	}
	cout << reg[0] << endl;
	return 0;
}
