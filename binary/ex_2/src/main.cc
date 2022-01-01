#include <algorithm>
#include <iostream>
#include <vector>
#include <stack>
#include <queue>

using std::cin;
using std::cout;
using std::endl;
using std::vector;


struct Node {
  int key;
  int left;
  int right;

  Node() : key(0), left(-1), right(-1) {}
  Node(int key_, int left_, int right_) : key(key_), left(left_), right(right_) {}
};

class BinaryTree {
  std::vector< Node > nodes;

private:
  int getRoot() {
    return 0;
  }

  int getRightNode(int i) {
    return nodes[i].right;
  }

  int getLeftNode(int i) {
    return nodes[i].left;
  }

  int getKey(int i) {
    return nodes[i].key;
  }

  bool isLeaf(Node n) {
    return ((n.left < 0) && (n.right < 0));
  }

  void inOrderTraversal(int root, std::vector< int >& traversal) {
    if (root == -1)
      return;

    inOrderTraversal(getLeftNode(root), traversal);
    traversal.push_back(getKey(root));
    inOrderTraversal(getRightNode(root), traversal);
    return;
  }


public:
  BinaryTree() {
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
      int key, left, right;
      cin >> key >> left >> right;
      nodes.push_back(Node(key, left, right));
    }
  
  }

  bool IsBinarySearchTree(void) {
    if (nodes.size() == 0)
      return true;

    std::vector< int > traversal;
    inOrderTraversal(getRoot(), traversal);

    for (int i = 1; i < traversal.size(); i++) {
      if (traversal[i] < traversal[i - 1])
        return false;
    }
  
    return true;
  }

};

int main() {
  BinaryTree t;

  if (t.IsBinarySearchTree()) {
    cout << "CORRECT" << endl;
  } else {
    cout << "INCORRECT" << endl;
  }
  return 0;
}
