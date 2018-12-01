#include <iostream>
#include <map>
#include <vector>

using namespace std;

int main() {
	int s = 0;
	int n;
	bool p = false;
	map<int, int> c;
	vector<int> list;
	while (cin >> n) {
		s += n;
		list.push_back(n);
		c[s]++;
		if (c[s] == 2) {
			p = true;
			break;
		}
	}
	if (!p) {
		int size = list.size();
		for (int i = 0;c[s] != 2;i++) {
			i %= size;
			s += list[i];
			c[s]++;
		}
	}
	cout << s << endl;
	return 0;
}
