#include <iostream>
#include <vector>

struct Node {
  int key;
  int priority;

  Node* left = nullptr;
  Node* right = nullptr;
  Node* parent = nullptr;
};

std::ostream& operator<<(std::ostream& os, Node* vertice) {
  if (vertice != nullptr) {
    std::cout << (vertice->parent != nullptr ? vertice->parent->key : 0) << ' ';
    std::cout << (vertice->left != nullptr ? vertice->left->key : 0) << ' ';
    std::cout << (vertice->right != nullptr ? vertice->right->key : 0) << '\n';
  }

  return os;
}

Node* Builder(std::vector<std::pair<int, int>>& values, Node** vertices) {
  Node* root = nullptr;
  Node* last_inserted = nullptr;

  for (size_t i = 0; i < values.size(); ++i) {
    std::pair<int, int> value = values[i];
    Node* new_node = new Node{ value.first, value.second };

    Node* curr = last_inserted;
    while (curr != nullptr && value.second < curr->priority) {
      curr = curr->parent;
    }

    if (curr == nullptr) {
      new_node->left = root;

      if (root != nullptr) {
        root->parent = new_node;
      }

      root = new_node;
    } else {
      new_node->left = curr->right;

      if (curr->right != nullptr) {
        curr->right->parent = new_node;
      }

      curr->right = new_node;
      new_node->parent = curr;
    }

    last_inserted = new_node;
    vertices[i] = new_node;
  }

  return root;
}

void InorderWalk(Node* x) {
  if (x != nullptr) {
    InorderWalk(x->left);
    std::cout << x;
    InorderWalk(x->right);
  }
}

int main() {
  int n;
  std::cin >> n;

  std::vector<std::pair<int, int>> values(n);
  Node** vertices = new Node * [n];

  for (int i = 0; i < n; ++i) {
    int a, b;
    std::cin >> a >> b;
    values[i] = std::make_pair(i + 1, b);
  }

  Node* treap = Builder(values, vertices);
  std::vector<std::pair<int, int>>().swap(values);
  values.clear();

  std::cout << "YES\n";
  InorderWalk(treap);

  for (int i = 0; i < n; ++i) {
    delete vertices[i];
  }
  delete[] vertices;

  return 0;
}