#include <iostream>
#include <algorithm>
#include <list>
#include <map>
#include <queue>
#include <utility>
#include <vector>

using namespace std;

#define INF 0x3f3f3f3f

typedef pair<int, int> ii;

struct vert {
  ii pos;
  bool un, elf;

  vert(ii p = make_pair(-1, -1), bool u = false, bool e = false) : pos(p), un(u), elf(e) {}
  void print(ostream& os = cout) {
    os << (un ? (elf ? 'E' : 'G') : '.');
    os << "(" << pos.first << ", " << pos.second << ")";
  }

  bool operator<(const vert& v) const {
    if (pos.second < v.pos.second) return true;
    return pos.second == v.pos.second && pos.first < v.pos.first;
  }
  bool operator==(vert& v) {
    return pos == v.pos;
  }
};
vert nil;

struct grafo {
  map<ii, vert> verts;
  map<vert, list<ii>> adj;

  void addEdge(ii u, ii v) {
    if (u.first == -1 || v.first == -1) {return;}
    try {
      verts.at(u);
      verts.at(v);
    }
    catch (exception& e) {
      return;
    }
    adj[verts[u]].push_back(v);
    adj[verts[v]].push_back(u);
  };
  void addNode(vert& u) {
    if (u == nil) return;
    verts[u.pos] = u;
  }
  void print(ostream& os = cout) {
    for (auto& p : verts) {
      p.second.print(os);
      for (ii v : adj[p.second]) {
        os << " -> ";
        verts[v].print(os);
      }
      os << endl;
    }
  }

  vert& operator[](ii p) {
    try {
      return verts.at(p);
    }
    catch (exception& e) {
      return nil;
    }
  }
  list<ii>& operator[](vert& v) {
    return adj[v];
  }
} g;
vector<vert> reachable(vert& v, bool type, map<vert, int>& dist, map<vert, vert>& pred) {
  vector<vert> ans;
  map<vert, bool> visit;

  for (auto& p : g.verts) {
    visit[p.second] = false;
    dist[p.second] = INF;
    pred[p.second] = nil;
  }
  queue<vert> q;
  visit[v] = true;
  dist[v] = 0;
  q.push(v);
  while (!q.empty()) {
    vert x = q.front(); q.pop();
    bool add = false;
    for (ii& p : g[x]) {
      vert y = g[p];
      if (!visit[y]) {
        if (y.un) {
          if (y.elf != type && !add) {
            ans.push_back(x);
            add = true;
          }
        }
        else {
          visit[y] = true;
          dist[y] = min(dist[y], dist[x] + 1);
          pred[y] = x;
          q.push(y);
        }
      }
    }
  }
  return ans;
}
ii choose(vert& n, vert& v, map<vert, vert>& pred) {
  vert next = v;
  while (!(pred[next] == n)) {
    next = pred[next];
  }
  return next.pos;
}

struct unit {
  ii pos;
  int hp = 200, atk = 3;
  bool elf;

  unit() {}
  unit(ii p, bool e) : pos(p), elf(e) {}

  unit* adjEnemy();
  void attack(unit& u) {
    cout << "- ";
    g[pos].print();
    cout << " attacks ";
    g[u.pos].print();cout << endl;
    u.damage(atk);
  }
  void damage(int d) {
    hp -= d;
    cout << "-- ";
    g[pos].print();
    cout << " lost " << d << " hp" << endl;
    cout << "-- hp = " << hp << endl;
    if (hp < 0) die();
  }
  void die();
  void move(ii pos);
  void play();
  ~unit() {}

  bool operator!=(unit& u) {
    return pos != u.pos;
  }
};

map<ii, unit> gps;
vector<unit> units;
int qtde = 0, qtdg = 0;

bool bestAtk(ii& u, ii& v) {
    if (gps.at(u).hp < gps.at(v).hp) return true;
    return (gps.at(u).hp == gps.at(v).hp && u < v && u != ii(-1, -1));
}
unit* unit::adjEnemy() {
  cout << "- searching enemy..." << endl;
  list<ii> adj = g[g[pos]];
  vector<ii> enemies;
  for (ii& p : adj) {
    vert u = g[p];
    cout << "-- ";
    u.print();
    if (u.un && u.elf != this->elf) {
      cout << " ok";
      enemies.push_back(u.pos);
    }
    cout << endl;
  }
  if (enemies.size() > 0) {
    sort(enemies.begin(), enemies.end(), bestAtk);
    return &gps.at(enemies[0]);
  }
  cout << "- enemy not found" << endl;
  return nullptr;
}
void unit::die() {
  gps.erase(this->pos);
  g[this->pos].un = g[this->pos].elf = false;
  auto it = units.begin();
  for (;it != units.end() && *it != *this;it++);
  units.erase(it);
  if (this->elf) qtde--; else qtdg--;
  cout << "- ";
  g[pos].print();cout << " elimined" << endl;

  this->~unit();
}
void unit::move(ii pos) {
  gps.erase(this->pos);
  g.verts[this->pos].un = false;
  g.verts[this->pos].elf = false;

  this->pos = pos;

  gps.insert(pair<ii, unit>(pos, *this));
  g[pos].un = true;
  g[pos].elf = this->elf;
}
void unit::play() {
  g[pos].print();
  cout << " turn:" << endl;
  unit *en = adjEnemy();
  if (!en) {
    map<vert, int> dist;
    map<vert, vert> pred;
    cout << "- searching reachable:" << endl;
    vector<vert> reach = reachable(g[pos], elf, dist, pred);
    for (vert& v : reach) {
      cout << "-- ";
      v.print();
      cout << endl;
    }
    if (reach.size() > 0) {
      int mindist = dist[reach[0]];
      vert near = reach[0];
      for (vert& v : reach) {
        if (dist[v] == mindist && v < near) {
          near = v;
        }
      }
      cout << "-- nearest: ";
      near.print();cout << endl;
      ii next = choose(g[pos], near, pred);
      cout << "- moving to " << next.first << ", " << next.second << endl;
      move(next);
      en = adjEnemy();
    }
    else {cout << "- reachable not found\n";}
  }
  if (en) {
    cout << "adjacent enemy = ";
    g[en->pos].print();
    cout << endl;
    attack(*en);
  }
  cout << "end turn" << endl << endl;
}

void printMap(int x, int y, ostream& os = cout) {
  for (int j = 0;j < y;j++) {
    for (int i = 0;i < x;i++) {
      ii pos(i, j);
      try {
        vert v = g.verts.at(pos);
        cout << (v.un ? (v.elf ? "E" : "G") : ".");
      }
      catch (exception& e) {
        cout << "#";
      }
    }
    cout << endl;
  }
}

int main() {
  char ch;
  int x = 0, y = 0, maxx = 0;
  while ((ch = getchar()) && ch != EOF) {
    // cout << ch;
    if (ch == '\n') {
      maxx = max(x, maxx);
      x = -1;
      y++;
    }
    else if (ch != '#') {
      ii here(x, y);
      vert v(here, ch != '.', ch == 'E');
      g.addNode(v);
      if (ch != '.') {
        unit u(here, ch == 'E');
        gps.insert(pair<ii, unit>(here, u));
        units.push_back(u);
        if (ch == 'E') qtde++; else qtdg++;
      }
      g.addEdge(here, ii(x, y - 1));
      g.addEdge(here, ii(x - 1, y));
    }
    x++;
  }
  int round = 0;
  while (qtde > 0 && qtdg > 0) {
    for (unit& u : units) {
      u.play();
    }
  //   break;
  //   cout << endl;
  //   printMap(x - 1, y);
    round++;
    cout << "------------------------------------------------------\n";
    for (auto& us : gps) {
      unit *u = &us.second;
      cout << u << ": "<< u->hp << " ";
    }
    cout << "\n------------------------------------------------------\n";
  }
  // cout << x << y << endl;
  printMap(maxx, y);
  int sum = 0;
  for (auto& us : gps) {
    unit u = us.second;
    cout << u.hp << " ";
    sum += u.hp;
  }
  cout << endl << round << endl;
  cout << round * sum << endl;
  return 0;
}
