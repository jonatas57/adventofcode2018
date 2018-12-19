#include <iostream>
#include <map>
#include <vector>

using namespace std;

vector<int> reg(6, 0);

void addr(int a, int b, int c) {
	reg[c] = reg[a] + reg[b];
}
void addi(int a, int b, int c) {
	reg[c] = reg[a] + b;
}
void mulr(int a, int b, int c) {
	reg[c] = reg[a] * reg[b];
}
void muli(int a, int b, int c) {
	reg[c] = reg[a] * b;
}
void banr(int a, int b, int c) {
	reg[c] = reg[a] & reg[b];
}
void bani(int a, int b, int c) {
	reg[c] = reg[a] & b;
}
void borr(int a, int b, int c) {
	reg[c] = reg[a] | reg[b];
}
void bori(int a, int b, int c) {
	reg[c] = reg[a] | b;
}
void setr(int a, int b, int c) {
	reg[c] = reg[a];
}
void seti(int a, int b, int c) {
	reg[c] = a;
}
void gtir(int a, int b, int c) {
	reg[c] = a > reg[b];
}
void gtri(int a, int b, int c) {
	reg[c] = reg[a] > b;
}
void gtrr(int a, int b, int c) {
	reg[c] = reg[a] > reg[b];
}
void eqir(int a, int b, int c) {
	reg[c] = a == reg[b];
}
void eqri(int a, int b, int c) {
	reg[c] = reg[a] == b;
}
void eqrr(int a, int b, int c) {
	reg[c] = reg[a] == reg[b];
}

typedef void (*fn)(int, int, int);

map<string, fn> func = {
  {"addr", addr}, {"addi", addi}, {"mulr", mulr}, {"muli",muli},
{"banr", banr}, {"banr", banr}, {"borr", borr}, {"bori", bori}, {"setr", setr}, {"seti",seti},
 {"gtir", gtir}, {"gtri", gtri}, {"gtrr", gtrr}, {"eqir", eqir}, {"eqri", eqri}, {"eqrr", eqrr}};

bool comp(vector<int>& r, vector<int>& a) {
	bool p = true;
	for (int i = 0;i < 4 && p;i++) {
		p = p && (r[i] == a[i]);
	}
	return p;
}

struct inst {
  string op;
  int a, b, c;

  inst(string o, int a, int b, int c) : op(o), a(a), b(b), c(c) {}
  void operator()() {
    func[op](a, b, c);
  }
};

void print(vector<int>& v) {
  for (int x : v) {
    cout << x << " ";
  }
  cout << endl;
}

int main() {
  int ipreg;
  scanf("#ip %d\n", &ipreg);
  int a, b, c;
  string op;
  vector<inst> insts;
  while (cin >> op >> a >> b >> c) {
    insts.push_back(inst(op, a, b, c));
  }
  int l = insts.size();
  // print(reg);
  for (reg[ipreg] = 0;reg[ipreg] < l;reg[ipreg]++) {
    insts[reg[ipreg]]();
    // print(reg);
  }
  cout << reg[0] << endl;
  return 0;
}
