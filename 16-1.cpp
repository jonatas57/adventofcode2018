#include <iostream>
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

int main() {
	char ch;
	int ans = 0;
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
		
		int n = 0;
		for (int i = 0;i < 16;i++) {
			reg = bef;
			func[i](a, b, c);
			if (comp(reg, aft)) n++;
		}
		if (n >= 3) ans++;
	}
	cout << ans << endl;
	return 0;
}
