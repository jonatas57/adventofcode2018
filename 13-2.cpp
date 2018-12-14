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
  int id, dir, nextdir = -1;

  car(int id, int x, int y, char c);
  bool walk();
  bool operator==(car& c) {
    return id == c.id;
  }
  // bool operator!=(car& c) {
  //   return id != c.id;
  // }
};
map<coord, car*> gps;
car::car(int id, int x, int y, char c) : pos(coord(x, y)), id(id) {
  dir = c == '^' ? 0 : c == '>' ? 1 : c == 'v' ? 2 : 3;
  gps[pos] = this;
}
bool car::walk() {
  gps[pos] = nullptr;
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
  car* p = gps[pos + mov[dir]];
  pos += mov[dir];
  if (!p) {
    gps[pos] = this;
  }
  return p != nullptr;
}

ostream& operator<<(ostream& os, const car& c) {
  os << c.id << ": " << c.pos.first << " " << c.pos.second;
  return os;
}

bool iscar(char c) {
  return (c == '>' || c == '<' || c == 'v' || c == '^');
}

void remove(auto& q, car* c) {
  if (q.empty()) return;
  car* x = q.top();
  q.pop();
  if (x != c) {
    remove(q, c);
    q.push(x);
  }
}
auto find(const vector<car*>& v, car* c) {
  auto it = v.begin();
  for (;it != v.end() && *it != c;it++);
  return it;
}

class comp {
public:
  bool operator()(car* d, car* c) {
    return d->pos.first > c->pos.first;
  }
};

int main() {
  char c;
  int x = 0, y = 0, qtd = 0, id = 1;
  vector<priority_queue<car*, vector<car*>, comp>> cars(150);
  vector<car*> remaining;
  while (scanf("%c", &c) != -1) {
    if (c == '\n') {
      x = -1;
      y++;
    }
    else {
      if (iscar(c)) {
        car *newcar = new car(id++, x, y, c);
        cars[y].push(newcar);
        qtd++;
        remaining.push_back(newcar);
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
  while (qtd > 1) {
    vector<priority_queue<car*, vector<car*>, comp>> cars2(150);
    for (auto& q : cars) {
      while (!q.empty()) {
        car *next = q.top();
        cout << *next << endl;
        q.pop();
        collision = collision || next->walk();
        if (collision) {
          car* crashed = gps[next->pos];
          gps[next->pos] = nullptr;
          remaining.erase(find(remaining, next));
          remaining.erase(find(remaining, crashed));
          qtd -= 2;
          remove(cars2[next->pos.second], crashed);
          remove(cars[next->pos.second], crashed);
          delete next;
          delete crashed;
          collision = false;
        }
        else cars2[next->pos.second].push(next);
      }
    }
    cout << endl;
    cars = cars2;
    cars2.clear();
  }
  cout << *remaining[0] << endl;
  return 0;
}
