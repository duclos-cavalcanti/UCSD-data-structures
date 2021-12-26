#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
#if defined(__unix__) || defined(__APPLE__)
#include <sys/resource.h>
#endif

class Node;

class Node {
public:
  int key;
  Node *parent;
  std::vector<Node *> children;

  Node() {
    this->parent = NULL;
  }

  void setParent(Node *theParent) {
    parent = theParent;
    parent->children.push_back(this);
  }
};


std::queue<Node> q;
Node* root;

std::vector<Node> createTree(int size) {
  std::vector<Node> nodes;
  nodes.resize(size);
  for (int child_index = 0; child_index < size; child_index++) {
    int parent_index;
    std::cin >> parent_index;
    if (parent_index >= 0)
      nodes[child_index].setParent(&nodes[parent_index]);
    else
      root = &nodes[child_index];


    nodes[child_index].key = child_index;
  }

  return nodes;

}

bool hasKeyBeenMapped(std::vector<int>& heightsMap, int key) {
  return (heightsMap.at(key) > 0);
}

int computeTreeHeight(std::vector<Node>& nodes) {
  int maxHeight = 0;
  int height = 0;
  std::vector<int> heightsMap(0);
  std::vector<int> heights(0);
  heightsMap.resize(nodes.size());

  if (root == NULL)
    return 0;

  q.push(*root);
  heightsMap.at(root->key) = 1;

  while(!q.empty()) {
    Node n = q.front();
    q.pop();

    if (!hasKeyBeenMapped(heightsMap, n.key)) {
      heightsMap.at(n.key) = 1 + heightsMap.at(n.parent->key);
    }

    if (n.children.size() > 0) { // not leaf node
      for (int child_index = 0; child_index < n.children.size(); child_index++ ) {
        q.push(*n.children.at(child_index));
      }
    } else { // leaf node
      heights.push_back(heightsMap.at(n.key));
    }

  }

  maxHeight = *std::max_element(heights.begin(), heights.end());
  return maxHeight;
}

int main_with_large_stack_space() {
  std::ios_base::sync_with_stdio(0);
  int n;
  std::cin >> n;
  std::vector<Node> nodes = createTree(n);

  int maxHeight = computeTreeHeight(nodes);
    
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
  if (result == 0)
  {
      if (rl.rlim_cur < kStackSize)
      {
          rl.rlim_cur = kStackSize;
          result = setrlimit(RLIMIT_STACK, &rl);
          if (result != 0)
          {
              std::cerr << "setrlimit returned result = " << result << std::endl;
          }
      }
  }

#endif
  return main_with_large_stack_space();
}
