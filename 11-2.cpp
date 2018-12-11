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
	cout << "ok" << endl;
	vector<vector<int>> sat(dim + 1, vector<int>(dim + 1, 0));
	sat[0][0] = grid[0][0];
	for (int i = 1;i < dim;i++) {
		sat[0][i] = sat[i][0] = 0;
	}
	for (int i = 1;i <= dim;i++) {
		for (int j = 1;j <= dim;j++) {
			sat[i][j] = grid[i-1][j-1] + sat[i - 1][j] + sat[i][j - 1] - sat[i - 1][j - 1];
		}
	}
	cout << "ok" << endl;
	int maxs = -0x3f3f3f3f, mi, mj, md;
	for (int x0 = 0;x0 < dim;x0++) {
		for (int y0 = 0;y0 < dim;y0++) {
			for (int k = 1;x0 + k <= dim && y0 + k <= dim;k++) {
				int s = sat[x0][y0] + sat[x0+k][y0+k] - sat[x0+k][y0] - sat[x0][y0+k];
				if (s > maxs) {
					maxs = s;
					mi = x0;
					mj = y0;
					md = k;
				}
			}
		}
	}
	cout << mi+1 << " " << mj+1 << " " << md << endl;
	return 0;
}
