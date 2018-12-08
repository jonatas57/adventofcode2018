#include <iostream>
#include <vector>

using namespace std;

struct tree {
	int id, value = -1, ch = 0;
	vector<int>  md;
	vector<tree*> childs;

	tree(int x) : id(x) {}
};

int index = 0;

tree* readinput() {
	tree* t = new tree(index++);
	int a, b;
	cin >> a >> b;
	t->ch = a;
	for (int i = 0;i < a;i++) {
		tree* c = readinput();
		t->childs.push_back(c);
	}
	t->md.resize(b);
	t->ch = t->childs.size();
	for (int i = 0;i < b;i++) {
		cin >> t->md[i];
	}
	return t;
}

void test(tree* t, int a) {
	for (int i = 0;i < a;i++) cout << "-";
	printf("%d, childs=%d, metadata=", t->id, t->ch);
	for (int i : t->md) cout << " " << i;
	cout << endl;
	for (tree* ptr : t->childs) test(ptr, a+1);
}

int mdsum(tree *t) {
	int ans = 0;
	for (int x : t->md) ans += x;
	for (tree* p : t->childs) ans += mdsum(p);
	return ans;
}

int eval(tree *t) {
	if (t->value >= 0) return t->value;
	if (t->ch == 0) {
		int v = 0;
		for (int x : t->md) v += x;
		t->value = v;
		return v;
	}
	int v = 0;
	for (int x : t->md) {
		if (x > 0 && x <= t->ch) {
			v += eval(t->childs[x - 1]);
		}
	}
	t->value = v;
	return v;
}

int main() {
	tree* t = readinput();
	int ans = eval(t);
	cout << ans << endl;
	return 0;
}
