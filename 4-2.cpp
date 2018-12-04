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
  int maxmin = -1, maxid;
  for (auto& i : sleeps) {
    for (int j = 0;j < 60;j++) {
      if (maxmin == -1 || sleeps[maxid][maxmin] < i.second[j]) {
        maxmin = j;
        maxid = i.first;
      }
    }
  }
  cout << maxid << " " << maxmin << endl;
  cout << maxid * maxmin << endl;
  return 0;
}
