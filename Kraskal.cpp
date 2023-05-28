#include <iostream>
#include <vector>

struct Edge {
  int u;
  int v;
  int w;

  Edge(int u, int v, int w) : u(u), v(v), w(w) {
  }
};

class DSU {
private:
  std::vector<int> p_;
  std::vector<int> r_;

public:
  explicit DSU(size_t n) {
    r_ = std::vector<int>(n, 0);
    p_ = std::vector<int>(n);

    for (size_t i = 0; i < n; ++i) {
      p_[i] = i;
    }
  }

  int FindSet(int x) {
    if (x == p_[x]) {
      return x;
    }

    return (p_[x] = FindSet(p_[x]));
  }

  void Union(int x, int y) {
    x = FindSet(x);
    y = FindSet(y);

    if (r_[x] < r_[y]) {
      p_[x] = y;
    } else if (r_[x] > r_[y]) {
      p_[y] = x;
    } else {
      p_[x] = y;
      r_[y] += 1;
    }
  }

  int Kruskal(std::vector<Edge> sorted_edges) {
    int mst_size = 0;
    for (auto vu : sorted_edges) {
      if (FindSet(vu.v) != FindSet(vu.u)) {
        Union(vu.v, vu.u);
        mst_size += vu.w;
      }

      if (FindSet(vu.u) != FindSet(vu.v)) {
        Union(vu.u, vu.v);
        mst_size += vu.w;
      }
    }

    return mst_size;
  }
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, m;
  std::cin >> n >> m;

  DSU dsu(n);

  std::vector<Edge> sorted_edges;
  for (int i = 0; i < m; ++i) {
    int v, u, w;
    std::cin >> v >> u >> w;
    sorted_edges.emplace_back(Edge(v - 1, u - 1, w));
  }

  std::cout << dsu.Kruskal(sorted_edges);

  return 0;
}