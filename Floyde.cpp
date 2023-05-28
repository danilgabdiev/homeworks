#include <iostream>
#include <vector>

class Graph {
 private:
  std::vector<std::vector<int>> vertexes_matrix_;
  size_t v_;

 public:
  explicit Graph(int n) {
    vertexes_matrix_.resize(n, std::vector<int>(n));
    v_ = n;
  }

  void FillWeights() {
    for (size_t i = 0; i < v_; ++i) {
      for (size_t j = 0; j < v_; ++j) {
        std::cin >> vertexes_matrix_[i][j];
      }
    }
  }

  void PrintMatrix() {
    for (size_t x = 0; x < v_; ++x) {
      for (size_t y = 0; y < v_; ++y) {
        std::cout << vertexes_matrix_[x][y] << " ";
      }
      std::cout << '\n';
    }
  }

  void FloydWarshall() {
    for (size_t k = 0; k < v_; ++k) {
      for (size_t x = 0; x < v_; ++x) {
        for (size_t y = 0; y < v_; ++y) {
          vertexes_matrix_[x][y] = std::min(vertexes_matrix_[x][y], vertexes_matrix_[x][k] + vertexes_matrix_[k][y]);
        }
      }
    }
  }
};

int main() {
  int n;
  std::cin >> n;
  Graph g(n);

  g.FillWeights();
  g.FloydWarshall();
  g.PrintMatrix();

  return 0;
}