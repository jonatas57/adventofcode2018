#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void insertSpaces(vector<bool>& v, int& init, int& size) {
	if (v[0]) {
		v.insert(v.begin(), false);
		size++;init--;
	}
	if (v[1]) {
		v.insert(v.begin(), false);
		size++;init--;
	}
	if (v[size - 1]) {
		v.push_back(false);
		size++;
	}
	if (v[size - 2]) {
		v.push_back(false);
		size++;
	}
}

void removeSpaces(vector<bool>& v, int& init, int& size) {
	while (!v[2] && !v[1] && !v[0]) {
		v.erase(v.begin());
		init++;
		size--;
	}
	while (!v[size - 3] && !v[size - 2] && !v[size - 1]) {
		v.pop_back();
		size--;
	}
}

vector<bool> iterate(vector<bool>& pots, vector<bool>& pats, int& aux) {
	vector<bool> newp;
	int size = pots.size();
	for (int j = 0;j < size;j++) {
		if (j + 2 < size) aux += (pots[j + 2] ? 1 : 0);
		newp.push_back(pats[aux]);
		aux <<= 1;
		aux %= 32;
	}
	return newp;
}

void print(vector<bool>& v) {
	for (bool b : v) cout << (b ? '#' : '.');
	cout << endl;
}

int main() {
	string s;
	scanf("initial state:");
	cin >> s;
	int init = -2;
	vector<bool> pots(2, false);
	for (char c : s) {
		pots.push_back(c == '#' ? true : false);
	}
	pots.push_back(false);
	pots.push_back(false);
	int size = pots.size();
	cout<<size<<endl;
	vector<bool> pats(32);
	char *pat = new char[6], res;
	while (scanf("%s => %c\n", pat, &res) != -1) {
		int id = 0;
		for (int i = 0;i < 5;i++) {
			id = id << 1;
			if (pat[i] == '#') id += 1;
		}
		pats[id] = res == '#';
	}
	long long nit = 50000000000;
	cout << ".." << s << ".." << endl;
	long long it;
	for (it = 0;it < nit;it++) {
		int aux = 0;
		vector<bool>&& newp = iterate(pots, pats, aux);
		insertSpaces(newp, init, size);
		removeSpaces(newp, init, size);
		if (equal(newp.begin(), newp.end(), pots.begin())) {
			cout << "convergiu" << endl;
			break;
		}
		else pots = newp;
	}
	long long sum = 0, rest = nit - it - 1;
	cout << init << endl << rest << endl;
	for (int i = 0;i < size;i++) {
		sum += (pots[i] ? i + init + rest : 0);
	}
	cout << sum << endl;
	return 0;
}
