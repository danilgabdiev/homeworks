#include <iostream>
#include <vector>
#include <unordered_set>

enum Color { white, grey, black};

struct Graph {
  std::vector<std::unordered_set<int>> vertexes;
  std::vector<Color> colors;
  std::vector<int> parents;
  int cycle_start;
  int cycle_end;
  bool has_cycle;

  explicit Graph(int n) {
    vertexes = std::vector<std::unordered_set<int>>(n);
    colors = std::vector<Color>(n, white);
    parents = std::vector<int>(n, -1);
    cycle_start = -1;
    cycle_end = -1;
    has_cycle = false;
  }

  bool DFSVisit(int v) {
    colors[v] = grey;

    for (auto u : vertexes[v]) {
      if (colors[u] == 0) {
        parents[u] = v;
        DFSVisit(u);
      } else if (colors[u] == 1) {
        cycle_start = v;
        cycle_end = u;
        has_cycle = true;
        return true;
      }
    }

    colors[v] = black;
    return false;
  }

  bool DFS() {
    for (size_t i = 0; i < vertexes.size(); ++i) {
      if (colors[i] != black) {
        DFSVisit(i);

        if (has_cycle) {
          return true;
        }
      }
    }

    return false;
  }
};

int main() {
  int n, m;
  std::cin >> n >> m;
  Graph g(n);

  int a, b;
  for (int i = 0; i < m; ++i) {
    std::cin >> a >> b;
    --a, --b;
    g.vertexes[a].insert(b);
  }

  std::vector<int> cycle;

  if (g.DFS()) {
    std::cout << "YES" << '\n';

    if (g.cycle_start == g.cycle_end) {
      cycle.push_back(g.cycle_start);
    }

    int i = g.cycle_start;
    while (i != g.cycle_end) {
      cycle.push_back(i);
      i = g.parents[i];

      if (i == -1) {
        break;
      }
    }
    cycle.push_back(g.cycle_end);
  } else {
    std::cout << "NO";
  }

  for (auto it = cycle.rbegin(); it != cycle.rend(); ++it) {
    std::cout << *it + 1 << ' ';
  }

  return 0;
}