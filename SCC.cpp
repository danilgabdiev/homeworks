#include <iostream>
#include <unordered_set>
#include <algorithm>
#include <vector>

enum Color { white, grey, black };

struct Graph {
  std::vector<std::unordered_set<int>> vertexes;
  std::vector<Color> colors;
  std::vector<int> top_sort;
  std::vector<int> vertex_components;
  int number_of_components = 0;

  explicit Graph(int n) {
    colors = std::vector<Color>(n, white);
    vertexes = std::vector<std::unordered_set<int>>(n);
    vertex_components = std::vector<int>(n);
  }

  void TopSortDFSVisit(int v) {
    colors[v] = grey;

    for (auto u : vertexes[v]) {
      if (colors[u] == 0) {
        TopSortDFSVisit(u);
      }
    }

    colors[v] = black;
    top_sort.push_back(v);
  }

  void TopSort() {
    for (size_t v = 0; v < vertexes.size(); ++v) {
      if (colors[v] == 0) {
        TopSortDFSVisit(v);
      }
    }

    reverse(top_sort.begin(), top_sort.end());
  }

  void Transpose() {
    std::vector<std::unordered_set<int>> transposed_vertexes(vertexes.size());
    for (size_t v = 0; v < vertexes.size(); ++v) {
      for (auto u : vertexes[v]) {
        transposed_vertexes[u].insert(v);
      }
    }

    vertexes.swap(transposed_vertexes);
  }

  void DFSVisit(int v) {
    colors[v] = grey;
    for (auto u : vertexes[v]) {
      if (colors[u] == 0) {
        DFSVisit(u);
      }
    }

    colors[v] = black;
    vertex_components[v] = number_of_components;
  }

  void DFS() {
    std::vector<Color>(vertexes.size(), white).swap(colors);
    for (auto v : top_sort) {
      if (colors[v] == white) {
        ++number_of_components;
        DFSVisit(v);
      }
    }
  }

  void Kosaraju() {
    TopSort();
    Transpose();
    DFS();
  }
};

int main() {
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int n, m;
  std::cin >> n >> m;

  Graph g(n);

  int a, b;
  for (int i = 0; i < m; ++i) {
    std::cin >> a >> b;
    --a, --b;
    g.vertexes[a].insert(b);
  }

  g.Kosaraju();

  std::cout << g.number_of_components << '\n';
  for (auto v : g.vertex_components) {
    std::cout << v << ' ';
  }

  return 0;
}