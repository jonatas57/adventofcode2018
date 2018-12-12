#include <iostream>
#include <vector>

using namespace std;

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
	int size = pots.size() - 4;
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
	int nit = 20;
	cout <<".."<<s<<".."<<endl;
	for (int i = 0;i < nit;i++) {
		int aux = 0;
		for (int j = 0;j < size + 4;j++) {
			if (j < size + 4) aux += (pots[j + 2] ? 1 : 0);
			pots[j] = pats[aux];
			aux <<= 1;
			aux %= 32;
		}
		if (pots[0]) {
			pots.insert(pots.begin(), false);
			size++;init--;
		}
		if (pots[1]) {
			pots.insert(pots.begin(), false);
			size++;init--;
		}
		if (pots[size + 3]) {
			pots.push_back(false);
			size++;
		}
		if (pots[size + 2]) {
			pots.push_back(false);
			size++;
		}
		for (bool b : pots) cout << (b ? '#' : '.');
		cout << endl;
	}
	int sum = 0;
	for (int i = init;i < size - init;i++) {
		sum += (pots[i - init] ? i : 0);
	}
	cout << sum << endl;
	return 0;
}
