#include <iostream>
#include <map>

using namespace std;

map<int, bool> gone;

int main() {
	unsigned long long ini = 12772194;
	unsigned long long r1 = 0, r3, r4, maior = 16777216;
	for (int i = 0;;i++) {
		r4 = r1 | 65536;
		r1 = ini;
		r3 = r4 & 255;
		r1 += r3;
		r1 &= 16777215;
		r1 *= 65899;
		r1 &= 16777215;

		while (r4 >= 256) {
			r4 /= 256;
			r3 = r4 % 256;
			r1 += r3;
			r1 &= 16777215;
			r1 *= 65899;
			r1 &= 16777215;
			cerr << r1 << " "  << r3 << " " << r4 << endl;
		}
		cout << r1 << endl;
		if (gone[r1]) break;
		gone[r1] = true;
		maior = r1;
	}
	cout << "maior: " << maior << endl;
	return 0;
}
