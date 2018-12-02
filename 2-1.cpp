#include <iostream>
#include <map>

using namespace std;

int main() {
	string s;
	int two = 0, three = 0;
	while (cin >> s) {
		map<char, int> count;
		for (int i = 0;s[i] != '\0';i++) {
			count[s[i]]++;
		}
		bool d = false, t = false;
		for (map<char, int>::iterator it = count.begin();it!=count.end();it++){
			if (it->second == 2) d = true;
			if (it->second == 3) t = true;
		}
		if (d) two++;
		if (t) three++;
	}
	cout << two * three << endl;
	return 0;
}
