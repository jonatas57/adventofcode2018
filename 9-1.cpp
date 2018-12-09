#include <iostream>
#include <vector>

using namespace std;

struct clist {
	int data;
	clist *next, *prev;
};
clist* newNode(int m) {
	clist* x = new clist;
	x->data = m;
	x->next = x;
	x->prev = x;
	return x;
}
void insert(clist* prev, clist* ins) {
	ins->prev = prev;
	ins->next = prev->next;
	prev->next->prev = ins;
	prev->next = ins;
}
int remove(clist* rem) {
	rem->prev->next = rem->next;
	rem->next->prev = rem->prev;
	int x = rem->data;
	delete rem;
	return x;
}

int main() {
	int mb, pl;
	clist* circle = newNode(0);
	clist* cur = circle;
	scanf("%d players; last marble is worth %d points", &pl, &mb);
	vector<int> elfs(pl, 0);
	int win = 0;
	for (int i = 1, act = 0;i <= mb;i++, act = (act + 1) % pl) {
		if (i % 23 == 0) {
			for (int j = 0;j < 7;j++) cur = cur->prev;
			clist* aux = cur->next;
			int sc = remove(cur);
			cur = aux;
			elfs[act] += i + sc;
			if (elfs[act] > win) win = elfs[act];
		}
		else {
			clist* x = newNode(i);
			insert(cur->next, x);
			cur = x;
		}
	}
	cout << win << endl;
	return 0;
}
