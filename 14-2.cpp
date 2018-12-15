#include <iostream>
#include <list>
#include <vector>
#include <cmath>

using namespace std;

bool comp(vector<int>& ans, list<int>& rec) {
  int s = ans.size();
  bool p = true;
  auto it = rec.begin();
  for (int i = 0;i < s && p;i++, it++) {
    p = p & (ans[i] == *it);
  }
  return p;
}

vector<int> newans(int in, int s) {
  vector<int> x(s, 0);
  for (int i = s - 1;i >= 0;i--) {
    x[i] = in % 10;
    in /= 10;
  }
  return x;
}
void iterate(list<int>& b, int x) {
  b.pop_front();
  b.push_back(x);
}

int main() {
  int qtd = 2, in, e1 = 0, e2 = 1;
  cin >> in;
  int s = log10(in) + 1;
  vector<int> ans = newans(in, s);
  list<int> rec(s - 2, 0);
  rec.push_back(3);
  rec.push_back(7);
  in += 10;

  vector<int> recipes(100 * in);
  recipes[0] = 3;
  recipes[1] = 7;
  while (!comp(ans, rec)) {
    int x = recipes[e1] + recipes[e2];
    if (x >= 10) {
      recipes[qtd++] = x / 10;
      iterate(rec, x / 10);
      x %= 10;
      if (comp(ans, rec)) break;
    }
    recipes[qtd++] = x;
    e1 = (e1 + 1 + recipes[e1]) % qtd;
    e2 = (e2 + 1 + recipes[e2]) % qtd;
    iterate(rec, x);
  }
  cout << qtd - ans.size() << endl;
  return 0;
}
