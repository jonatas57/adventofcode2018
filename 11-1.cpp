#include <iostream>
#include <vector>

using namespace std;

int f(int inp, int x, int y) {
	int id = x + 11;
	int r = id;
	r *= y + 1;
	r += inp;
	r *= id;
	r = (r % 1000 - r % 100) / 100;
	r -= 5;
	return r;
}

int main() {
	int dim = 300, inp;
	cin >> inp;
	vector<vector<int>> grid(dim, vector<int>(dim, 0));
	for (int i = 0;i < dim;i++) {
		for (int j = 0;j < dim;j++) {
			grid[i][j] = f(inp, i, j);
		}
	}
	int maxs = -0x3f3f3f3f, mi, mj;
	for (int i = 0;i < dim - 2;i++) {
		for (int j = 0;j < dim - 2;j++) {
			int sum = 0;
			for (int k = 0;k < 9;k++) {
				sum += grid[i + k / 3][j + k % 3];
			}
			if (sum > maxs) {
				maxs = sum;
				mi = i;
				mj = j;
			}
		}
	}
	cout << mi+1 << " " << mj+1 << endl;
	return 0;
}
