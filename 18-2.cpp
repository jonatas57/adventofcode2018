#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

int total = 1000000000;

int main() {
	int z;
	string s;
	vector<string> forest;
	bool check = false;
	int gap, last, loop;
	vector<int> values;
	map<int, int> lasts;
	for (z = 0;z < total;z++) {
		for (int i = 0;cin >> s;i++) {
			forest.push_back(s);
		}
		int x = forest[0].length(), y = forest.size();
		vector<string> newf(y, string(x, ' '));
		for (int j = 0;j < y;j++) {
			for (int i = 0;i < x;i++) {
				int lumb = 0, open = 0, tree = 0;
				for (int k = 0;k < 9;k++) {
					if (k != 4) {
						try {
							char c = forest[j + (k / 3) - 1][i + (k % 3) -1];
							if (c == '.') open++;
							else if (c == '|') tree++;
							else if (c == '#') lumb++;
						}
						catch (exception& e) {
							continue;
						}
					}
				}
				char n;
				if (forest[j][i] == '.') n = (tree >= 3 ? '|' : '.');
				else if (forest[j][i] == '|') n = (lumb >= 3 ? '#' : '|');
				else n = (tree >= 1 && lumb >= 1 ? '#' : '.');
				newf[j][i] = n;
			}
		}
		forest = newf;
		int l = 0, t = 0;
		for (string s : forest) {
			for (char c : s) {
				if (c == '|') t++;
				else if (c == '#') l++;
			}
		}
		int ans = l * t;
		values.push_back(ans);
		if (check) {
			try {
				if (ans == values[last + 1]) {
					gap--;
					last++;
					if (gap == 0) { break; }
				}
				else {
					check = false;
				}
			}
			catch (exception& e) {}
		}
		else {
			try {
				last = lasts.at(ans);
				loop = gap = z - last;
				check = true;
			}
			catch (exception& e) {}
		}
		lasts[ans] = z;
	}
	int rest = total - values.size();
	rest %= loop;
	z = z - loop + rest;
	cout << values[z] << endl;
	return 0;
}
