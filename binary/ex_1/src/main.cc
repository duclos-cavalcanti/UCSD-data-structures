#include <iostream>
#include <vector>
#include <algorithm>
#if defined(__unix__) || defined(__APPLE__)
#include <sys/resource.h>
#endif

using std::vector;
using std::ios_base;
using std::cin;
using std::cout;

class BinaryTree {
  int n;
  vector <int> key;
  vector <int> left;
  vector <int> right;

private:
  int getRoot() {
    return 0;
  }

  int getRightNode(int i) {
    return right[i];
  }

  int getLeftNode(int i) {
    return left[i];
  }

  int getKey(int i) {
    return key[i];
  }

  void inOrderTraversal(int i, vector<int>& result) {
    if (i < 0)
      return;

    inOrderTraversal(getLeftNode(i), result);
    result.push_back(getKey(i));
    inOrderTraversal(getRightNode(i), result);
    return;
  }

  void preOrderTraversal(int i, vector<int>& result) {
    if (i < 0)
      return;

    result.push_back(getKey(i));
    preOrderTraversal(getLeftNode(i), result);
    preOrderTraversal(getRightNode(i), result);
    return;
  }

  void postOrderTraversal(int i, vector<int>& result) {
    if (i < 0)
      return;

    postOrderTraversal(getLeftNode(i), result);
    postOrderTraversal(getRightNode(i), result);
    result.push_back(getKey(i));
    return;
  }

public:
  BinaryTree() {
    cin >> n;
    key.resize(n);
    left.resize(n);
    right.resize(n);

    for (int i = 0; i < n; i++) {
      cin >> key[i] >> left[i] >> right[i];
    }
  }

  vector <int> in_order() {
    vector<int> result;
    inOrderTraversal(getRoot(), result);

    return result;
  }

  vector <int> pre_order() {
    vector<int> result;    
    preOrderTraversal(getRoot(), result);
    
    return result;
  }

  vector <int> post_order() {
    vector<int> result;
    postOrderTraversal(getRoot(), result);
    
    return result;
  }
};

void print(vector <int> a) {
  for (size_t i = 0; i < a.size(); i++) {
    if (i > 0) {
      cout << ' ';
    }
    cout << a[i];
  }
  cout << '\n';
}

int main_with_large_stack_space() {
  ios_base::sync_with_stdio(0);

  BinaryTree t;

  print(t.in_order());
  print(t.pre_order());
  print(t.post_order());

  return 0;
}

int main (int argc, char **argv)
{
#if defined(__unix__) || defined(__APPLE__)
  // Allow larger stack space
  const rlim_t kStackSize = 16 * 1024 * 1024;   // min stack size = 16 MB
  struct rlimit rl;
  int result;

  result = getrlimit(RLIMIT_STACK, &rl);
  if (result == 0) {
      if (rl.rlim_cur < kStackSize) {
          rl.rlim_cur = kStackSize;
          result = setrlimit(RLIMIT_STACK, &rl);
          if (result != 0) {
              std::cerr << "setrlimit returned result = " << result << std::endl;
          }
      }
  }
#endif

  return main_with_large_stack_space();
}

