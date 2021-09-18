#include <iostream>
#include <stack>
#include <string>

#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>

#if defined(__unix__) || defined(__APPLE__)
#include <sys/resource.h>
#endif

class Node;

int root_key = 0;
std::vector<int> leaves;

class Node {
public:
    int key;
    int depth;
    Node *parent;
    std::vector<Node *> children;

    Node() {
      this->parent = NULL;
      this->children.resize(0);
    }

    void setParent(Node *theParent) {
      parent = theParent;
      parent->children.push_back(this);
    }
};

void shaveLeaf(int target) {
  for (int i = 0; i < leaves.size(); i++) {
   if (leaves.at(i) == target)
     leaves.erase(leaves.begin() + i);
  }
}

void populateLeaves(std::vector<int> *leaves) {
  int size = leaves->size();
  for (int i = 0; i < size; i++) {
    leaves->at(i) = i;
  }
}

int findLeafDepth(Node *leaf, std::vector<int> *paths) {
  int diff;
  int height = 1;
  std::stack<int> st;
  for (Node* it=leaf->parent; it!=NULL; it=it->parent) {
    diff = paths->at(it->key);
    if (diff > 0) {
      height += diff;
      return height;
    } else {
      ++height;
      if (it->parent != NULL) {
        paths->at(it->key) = height;
        st.push(it->key);
      }
    }
  }

  int inc = 1;
  while (!st.empty()) {
   int val = st.top() ;
   st.pop();
   ++inc;
   paths->at(val) = inc;
  }
  return height;
}

int recreateTree(std::vector<Node>& nodes) {
  int n;
  std::ios_base::sync_with_stdio(0);
  std::cin >> n; // number of nodes in tree

  nodes.resize(n);
  leaves.resize(n);
  populateLeaves(&leaves);
  for (int child_index = 0; child_index < n; child_index++) {
    int parent_index;
    std::cin >> parent_index;
    if (parent_index >= 0) {
      nodes[child_index].setParent(&nodes[parent_index]);
      if (parent_index < leaves.size())
        shaveLeaf(parent_index);
    } else {
      root_key = child_index;
      shaveLeaf(child_index);
    }
    nodes[child_index].key = child_index;
  }

  return n;
}

int findTreeHeight() {
  int height, maxHeight = 0;
  std::vector<int> parents;
  std::vector<Node> nodes;

  int n = recreateTree(nodes);

  std::vector<int> paths(n, -1);
  for (int it=0; it<leaves.size(); ++it) {
    height = findLeafDepth(&nodes.at(leaves.at(it)), &paths);
    maxHeight = std::max(maxHeight, height);
  }

  std::cout << maxHeight << std::endl;
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
  return findTreeHeight();
}

