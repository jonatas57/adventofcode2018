#include <bits/stdc++.h>

using namespace std;

int remove(string s, char r) {
	string x = "";
	int id = 0;
	x += s[0];
	for (int i = 1;s[i] != '\0';i++) {
		if (tolower(s[i]) == r) {
			continue;
		}
		else if (isupper(x[id]) == !isupper(s[i]) && abs((x[id] - s[i])) == 32) {
			x.erase(id);
			id--;
			if (id < 0) {
				x += s[i + 1];
				i++;
				id = 0;
			}
		}
		else {
			x += s[i];
			id++;
		}
	}
	int ans = x.length();
	if (tolower(x[0]) == r) ans--;
	return ans;
}

int main() {
	string s;
	cin >> s;
	int x = 0x3f3f3f3f;
	char c;
	for (char i = 'a';i <= 'z';i++) {
		int aux = remove(s, i);
		if (x > aux) {
			c = i;
			x = aux;
		}
		cout << aux << ' ' << i << endl;
	}
	cout << x << endl;
	cout << c << endl;
	return 0;
}
