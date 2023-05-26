#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <unordered_set>

class Graph {
private:
  std::vector<std::unordered_set<int>> vertexes_;
  std::vector<int> dist_;
  std::vector<int> parents_;

public:
  explicit Graph(int n) {
    vertexes_ = std::vector<std::unordered_set<int>>(n);
    dist_ = std::vector<int>(n, std::numeric_limits<int>::max());
    parents_ = std::vector<int>(n, -1);
  }

  friend std::istream& operator>>(std::istream& is, Graph& g);

  void BFS(int s);

  void PrintMinWay(int a, int b) {
    if (a == b) {
      std::cout << 0 << '\n' << b + 1;
      return;
    }

    if (dist_[b] == std::numeric_limits<int>::max()) {
      std::cout << -1;
      return;
    }

    std::cout << dist_[b] << '\n';

    auto min_way = new int[dist_[b] + 1];

    int i = b, j = 0;
    while (i != -1) {
      min_way[j] = i;
      ++j;
      i = parents_[i];
    }

    for (int i = dist_[b]; i >= 0; --i) {
      std::cout << min_way[i] + 1 << ' ';
    }

    delete[] min_way;
  }
};

void Graph::BFS(int s) {
  dist_[s] = 0;
  std::queue<int> queue;
  queue.push(s);

  while (!queue.empty()) {
    int v = queue.front();
    queue.pop();

    for (auto u : vertexes_[v]) {
      if (dist_[u] > dist_[v] + 1) {
        dist_[u] = dist_[v] + 1;
        parents_[u] = v;
        queue.push(u);
      }
    }
  }
}

std::istream& operator>>(std::istream& is, Graph& g) {
  int v, u;
  is >> v >> u;
  --v, --u;

  g.vertexes_[v].insert(u);
  g.vertexes_[u].insert(v);

  return is;
}

int main() {
  int n, m;
  std::cin >> n >> m;
  Graph g(n);

  int a, b;
  std::cin >> a >> b;
  --a, --b;

  for (int i = 0; i < m; ++i) {
    std::cin >> g;
  }

  g.BFS(a);
  g.PrintMinWay(a, b);

  return 0;
}