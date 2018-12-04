#include <bits/stdc++.h>

using namespace std;

int last;

struct event {
  int dia, mes, ano, hora, min, id;
  bool dorm;
  string s;

  event(int d, int m, int a, int h, int min, string s) :
    dia(d), mes(m), ano(a), hora(h), min(min), s(s) {
  }

  void print() {
    printf("[%d-%02d-%02d %02d:%02d] %4d ", ano, mes, dia, hora, min, id);
    cout << s << endl;
  }
  void update() {
    if (s[0] == 'G') {
      sscanf(s.c_str(), "Guard #%d begins shift\n", &id);
      last = id;
      dorm = false;
      s = "entrou";
    }
    else {
      id = last;
      dorm = s[0] == 'f';
      s = dorm ? "dormiu" : "acordou";
    }
  }
  bool operator<(const event& x) {
    if (ano < x.ano) return true;
    if (ano == x.ano) {
      if (mes < x.mes) return true;
      if (mes == x.mes) {
        if (dia < x.dia) return true;
        if (dia == x.dia) {
          if (hora < x.hora) return true;
          if (hora == x.hora) {
            if (min < x.min) return true;
          }
        }
      }
    }
    return false;
  }
};

int main() {
  vector<event> evs;
  int d, m, a, h, min;
  string s;
  while (scanf("[%d-%d-%d %d:%d] ", &a, &m, &d, &h, &min) != EOF) {
    getline(cin, s);
    evs.push_back(event(d, m, a, h, min, s));
  }
  sort(evs.begin(), evs.end());
  for (event& x : evs) {
    x.update();
  }
  map<int, vector<int>> sleeps;
  int ini, fi;
  for (event& x: evs) {
    if (x.s != "entrou") {
      if (x.dorm) {
        ini = x.min;
      }
      else {
        fi = x.min;
        int id = x.id;
        try {
          sleeps.at(id);
        }
        catch (exception& e) {
          sleeps[id].resize(61, 0);
        }
        for (int i = ini;i < fi;i++) {
          sleeps[id][i]++;
          sleeps[id][60]++;
        }
      }
    }
  }
  for (auto& x : sleeps) {
    cout << x.first << " -> ";
    for (int k : x.second) {
      cout << k << " ";
    }
    cout << endl;
  }
  int maxs = -1, maxid;
  for (auto& x : sleeps) {
    if (maxs < x.second[60]) {
      maxs = x.second[60];
      maxid = x.first;
    }
  }
  int maxh = -1;
  for (auto& x : sleeps[maxid]) {
    cout << x << " ";
  }
  cout << endl;
  for (int z = 0;z < 60;z++) {
    if (sleeps[maxid][maxh] < sleeps[maxid][z]) {
      maxh = z;
    }
  }
  cout << maxh * maxid << endl;
  return 0;
}
