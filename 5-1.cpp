#include <bits/stdc++.h>

using namespace std;

int main() {
	string s;
	cin >> s;
	string x = "";
	int id = 0;
	x += s[0];
	for (int i = 1;s[i] != '\0';i++) {
		if (isupper(x[id]) == !isupper(s[i]) && abs((x[id] - s[i])) == 32) {
			printf("remove %c %c\n", x[id], s[i]);
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
	cout << x.length() << endl;
	return 0;
}
