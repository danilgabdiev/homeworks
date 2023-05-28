#include <iostream>
#include <vector>
#include <unordered_set>

enum Color { white, grey, black };

struct Vertice {
  int index;
  int time_in;
  int time_up;
  Color color;

  explicit Vertice(int u) {
    time_in = 0;
    time_up = 0;
    color = white;
    index = u;
  }
};

struct Graph {
  std::vector<Vertice> vertices;
  std::vector<std::vector<int>> edges;
  std::vector<bool> articulation_points;
  int articulation_points_count;

  explicit Graph(int n) {
    for (int i = 0; i < n; ++i) {
      vertices.emplace_back(Vertice(i));
    }

    edges = std::vector<std::vector<int>>(n);
    articulation_points = std::vector<bool>(n, false);
    articulation_points_count = 0;
  }
};

void DFSVisit(Graph& g, Vertice& v, bool is_root, int& time) {
  v.color = grey;
  v.time_in = ++time;
  v.time_up = time;
  int children = 0;

  for (auto neighbors : g.edges[v.index]) {
    Vertice& u = g.vertices[neighbors];

    if (u.color == grey) {
      v.time_up = std::min(v.time_up, u.time_in);
    }

    if (u.color == white) {
      ++children;
      DFSVisit(g, u, false, time);
      v.time_up = std::min(v.time_up, u.time_up);

      if (!is_root && (v.time_in <= u.time_up) && !(g.articulation_points[v.index])) {
        g.articulation_points[v.index] = true;
        ++g.articulation_points_count;
      }
    }
  }

  if (is_root && children >= 2 && !(g.articulation_points[v.index])) {
    g.articulation_points[v.index] = true;
    ++g.articulation_points_count;
  }

  v.color = black;
}

int main() {
  int n, m;
  std::cin >> n >> m;

  Graph g(n);
  int time = 0;

  int a, b;
  for (int i = 0; i < m; ++i) {
    std::cin >> a >> b;
    --a, --b;

    g.edges[a].push_back(b);
    g.edges[b].push_back(a);
  }

  for (int i = 0; i < n; ++i) {
    if (g.vertices[i].color == 0) {
      DFSVisit(g, g.vertices[i], true, time);
    }
  }

  std::cout << g.articulation_points_count << '\n';
  for (int i = 0; i < n; ++i) {
    if (g.articulation_points[i]) {
      std::cout << i + 1 << '\n';
    }
  }

  return 0;
}