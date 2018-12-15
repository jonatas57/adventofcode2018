#include <iostream>
#include <ios>
#include <vector>

using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  int qtd = 2, in, e1 = 0, e2 = 1;
  cin >> in;
  in += 10;
  vector<int> recipes(in);
  recipes[0] = 3;
  recipes[1] = 7;
  while (qtd < in) {
    int x = recipes[e1] + recipes[e2];
    if (x >= 10) {
      recipes[qtd++] = x / 10;
      x %= 10;
    }
    recipes[qtd++] = x;
    e1 = (e1 + 1 + recipes[e1]) % qtd;
    e2 = (e2 + 1 + recipes[e2]) % qtd;
  }
  for (int i = in - 10;i < qtd;i++) {
    cout << recipes[i];
  }
  cout << endl;
  return 0;
}
