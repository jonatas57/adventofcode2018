#include <iostream>
#include <map>
#include <queue>
#include <utility>
#include <vector>

using namespace std;

typedef pair<int, int> ii;
typedef pair<int, ii> line;
#define INF 0x3f3f3f3f

bool c = true;

struct node {
  char ch;
  bool rest;
  // int dir;
  vector<node*> adj;

  node(char c) : ch(c), rest(false)/*, dir(-1)*/ {
    adj.resize(4, nullptr);
  }
  void operator=(char c) {
    ch = c;
  }
};
ostream& operator<<(ostream& os, node& n) {
  string color;
  if (n.ch == '#') color = "\x1b[90m";
  else color = "\x1b[93m";
  if (c)os << color << n.ch << "\x1b[m";
  else os << n.ch;
  return os;
}
typedef void (*fn)(node*);

vector<vector<node>> mapa;

struct oper {
  string op;
  node* n;
  int prior;

  oper() {}
  oper(string o, node* n) : op(o), n(n) {
  	prior = (o == "down" ? 4 : (o == "left" || o == "right" ? 3 : (o.size() == 7 ? 2 : 1 )));
  }
  bool operator<(const oper& o) const {
	  return prior < o.prior;
  }
};

int total;
priority_queue<oper> ops;
queue<oper> ups;

bool isblocked(char c) {
  return c == '#' || c == '~';
}

void up(node *n) {
  ops.push(oper("right", n->adj[0]));
  ops.push(oper("left", n->adj[0]));
}
void down(node *n) {
  node *d = n->adj[2];
  if (n->ch == ' ') {
    total++;
    n->ch = '|';
  }
  if (d) {
    if (d->ch == ' ') {
      ops.push(oper("down", d));
    }
    else if (isblocked(d->ch)) {
      ops.push(oper("right", n));
      ops.push(oper("left", n));
    }
  }
}
void sides(node *n, int dir) {
  node *d = n->adj[dir];
  if (d->ch == ' ') {
    total++;
    d->ch = '|';
    ops.push(oper("down", d));
  }
  else if (isblocked(d->ch)) {
    ops.push(oper((dir == 1 ? "restesq" : "restdir"), n));
  }
}
void rest(node *n, int dir) {
  node *d = n->adj[dir];
  if (n->rest) {
    n->ch = '~';
    if (n->adj[0] && (n->adj[0]->ch == '|' || n->adj[0]->ch == '-')) {
      ups.push(oper("up", n));
    }
  }
  else {
    if (n->ch == '|') {
      n->rest = true;
      n->ch = '-';
    }
  }
  if (d && !isblocked(d->ch)) {
    ops.push(oper((dir == 1 ? "restdir" : "restesq"), d));
  }
  if (d && d->ch == '-') ops.push(oper((dir == 1 ? "restesq" : "restdir"), n));
}

void right(node *n) {
  sides(n, 1);
}
void left(node *n) {
  sides(n, 3);
}
void restdir(node *n) {
  rest(n, 1);
}
void restesq(node *n) {
  rest(n, 3);
}

map<string, fn> mapop = {{"up", up}, {"right", right}, {"down", down},
{"left", left}, {"restdir", restdir}, {"restesq", restesq}};

void print(ostream& os = cout) {
  for (auto& l : mapa) {
    for (auto& c : l) {
      os << c;
    }
    os << endl;
  }
}

int main() {
  int a, b, c;
  char ch1, ch2;
  vector<line> vert, horiz;
  int minx = INF, miny = INF, maxx = 500, maxy = INF;

  while (scanf("%c=%d, %c=%d..%d\n", &ch1, &a, &ch2, &b, &c) != -1) {
    line l = line(a, ii(b, c));
    if (ch1 == 'x') {
      vert.push_back(l);
      minx = min(a, minx);
      miny = min(b, miny);
      maxx = max(a, maxx);
      maxy = (maxy == INF ? c : max(c, maxy));
    }
    else {
      horiz.push_back(l);
      minx = min(b, minx);
      miny = min(a, miny);
      maxx = max(c, maxx);
      maxy = (maxy == INF ? a : max(a, maxy));
    }
  }

  minx--;maxx++;
  int delx = maxx - minx + 1, dely = maxy - miny + 1;
  mapa.resize(dely, vector<node>(delx, node(' ')));
  for (int i = 0;i < dely;i++) {
    for (int j = 0;j < delx;j++) {
      if (i > 0) {
        mapa[i][j].adj[0] = &mapa[i - 1][j];
        mapa[i - 1][j].adj[2] = &mapa[i][j];
      }
      if (j > 0) {
        mapa[i][j - 1].adj[1] = &mapa[i][j];
        mapa[i][j].adj[3] = &mapa[i][j - 1];
      }
    }
  }

  for (line& l : vert) {
    for (int i = l.second.first;i <= l.second.second;i++) {
      mapa[i - miny][l.first - minx] = '#';
    }
  }
  for (line& l : horiz) {
    for (int i = l.second.first;i <= l.second.second;i++) {
      mapa[l.first - miny][i - minx] = '#';
    }
  }
  int fonte = 500 - minx;
  ops.push(oper("down", &mapa[0][fonte]));

  int sys;
  bool takeup = false;
  while (!ops.empty() || !ups.empty()) {
    // sys = system("clear");
    oper x;
    if (ops.empty()) {
      takeup = true;
    }
    if (ups.empty()) {
      takeup = false;
    }
    if (takeup) {
      x = ups.front();ups.pop();
    }
    else {
      x = ops.top();ops.pop();
    }
    mapop[x.op](x.n);
    // print();
    // cout << total << endl;
    // sys = system("sleep 0.5");
  }
  sys += system("clear");
  print();
  cout << endl << total << endl;
  return 0;
}
