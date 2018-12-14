#include <iostream>
#include <map>
#include <queue>
#include <utility>
#include <vector>

using namespace std;

typedef pair<int, int> coord;

struct trail {
  char c;
  vector<bool> dirs;

  trail() {}
  trail(char c, int a = 4, int b = 4) : c(c) {
    dirs.resize(4, a == 4);
    if (a != 4) {
      dirs[a] = dirs[b] = true;
    }
  }
};

map<coord, trail> mapa;
map<coord, bool> gps;
vector<coord> mov = {{0, -1}, {1, 0}, {0, 1}, {-1, 0}};

coord operator+(coord a, coord b) {
  coord x(a.first + b.first, a.second + b.second);
  return x;
}
void operator+=(coord& a, coord& b) {
  a.first += b.first;
  a.second += b.second;
}

struct car {
  coord pos;
  int dir, nextdir = -1;

  car(int x, int y, char c) : pos(coord(x, y)) {
    dir = c == '^' ? 0 : c == '>' ? 1 : c == 'v' ? 2 : 3;
    gps[pos] = true;
  }
  bool walk() {
    gps[pos] = false;
    auto t = mapa[pos];
    if (t.c == '+') {
      dir = (4 + dir + nextdir) % 4;
      nextdir = (nextdir + 2) % 3 - 1;
    }
    else if (t.c == '\\' || t.c == '/') {
      int p = dir % 2, i;
      for (i = 0;i < 4 && (i % 2 == p || !t.dirs[i]);i++);
      dir = i;
    }
    bool p = gps[pos + mov[dir]];
    pos += mov[dir];
    gps[pos] = true;
    return p;
  }
  bool operator<(const car& c) const {
    return pos.second < c.pos.second;
  }
};
ostream& operator<<(ostream& os, const car& c) {
  os << c.pos.first << " " << c.pos.second;
  return os;
}

bool iscar(char c) {
  return (c == '>' || c == '<' || c == 'v' || c == '^');
}

int main() {
  char c;
  int x = 0, y = 0;
  vector<priority_queue<car>> cars(150);
  while (scanf("%c", &c) != -1) {
    if (c == '\n') {
      x = -1;
      y++;
    }
    else {
      if (iscar(c)) {
        cars[y].push(car(x, y, c));
        c = (c == '>' || c == '<' ? '-' : '|');
      }
      if (c == '+') mapa[coord(x, y)] = trail(c);
      else if (c == '|') mapa[coord(x, y)] = trail(c, 0, 2);
      else if (c == '-') mapa[coord(x, y)] = trail(c, 1, 3);
      else if (c != ' ') {
        bool aux;
        try {
          coord p(x, y - 1);
          mapa.at(p);
          aux = mapa[p].dirs[2];
        }
        catch (exception& e) {aux = false;}

        if (c == '/') {
          mapa[coord(x, y)] = aux ? trail(c, 0, 3) : trail(c, 1, 2);
        }
        else {
          mapa[coord(x, y)] = aux ? trail(c, 0, 1) : trail(c, 2, 3);
        }
      }
    }
    x++;
  }
  bool collision = false;
  int cx, cy;
  while (!collision) {
    vector<priority_queue<car>> cars2(150);
    for (auto& q : cars) {
      while (!q.empty() && !collision) {
        car next = q.top();
        q.pop();
        collision = collision || next.walk();
        if (collision) {
          cx = next.pos.first;
          cy = next.pos.second;
        }
        cars2[next.pos.second].push(next);
        cout << next << endl;
      }
    }
    cout << endl;
    cars = cars2;
    cars2.clear();
  }
  cout << cx << " " << cy << endl;
  return 0;
}
