#include <iostream>
#include <vector>

using namespace std;

int diff(string a, string b) {
	int l = a.length();
	int id = 0, c = 0;
	for (int i = 0;i < l - 1;i++) {
		if (a[i] != b[i]) {
			c++;
			id = i;
		}
	}
	if (c == 1) return id;
	return -1;
}

string cut(string s, int id) {
	int l = s.length();
	string x = "";
	for (int i = 0; i < l;i++){
		if (i != id) {
			x += s[i];
		}
	}
	return x;
}

int main() {
	vector<string> ids;
	string s;
	while (cin >> s) {
		ids.push_back(s);
	}
	int l = ids.size();
	for (int i = 0;i < l - 1;i++) {
		for (int j = i + 1;j < l;j++) {
			int x = diff(ids[i], ids[j]);
			if (x != -1) {
				cout << cut(ids[i], x) << endl;
			}
		}
	}
	return 0;
}
