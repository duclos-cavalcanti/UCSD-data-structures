#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>

using std::vector;
using std::cin;
using std::cout;
using std::swap;
using std::pair;
using std::make_pair;

class Heap {
 private:
  vector<int> data_;
  vector< pair<int, int> > swaps_;

  void readData() {
    int n;
    cin >> n;
    data_.resize(n);
    for(int i = 0; i < n; ++i)
      cin >> data_[i];
  }

  void sortHeap() {
    swaps_.clear();
    int size = data_.size();
    for(int i = floor(size/2); i >= 0; i--) {
      siftDown(i);
    }
  }

  void siftUp(int i) {
    while (i > 1 && 
           data_[getParent(i)] > data_[i]) {
      swap(data_[getParent(i)], data_[i]);
      i = getParent(i);
    }
  }

  void siftDown(int i) {
    int minIndex = i;
    int left = getLeftChild(i);
    if (left < data_.size() &&
        data_[left] < data_[minIndex]) {
      minIndex = left;
    }

    int right = getRightChild(i);
    if (right < data_.size() && 
        data_[right] < data_[minIndex]) {
      minIndex = right;
    }

    if (i != minIndex) {
      swap(data_[i], data_[minIndex]);
      swaps_.push_back(make_pair(i, minIndex));
      siftDown(minIndex);
    }


  }

  int getParent(int i) {
    return (int) floor((i -1)/2);
  }

  int getLeftChild(int i) {
    return (2*i + 1);
  }

  int getRightChild(int i) {
    return (2*i + 2);
  }


 public:
  void build() {
    readData();
    sortHeap();
  }

  void dumpSwaps() const {
    cout << swaps_.size() << "\n";
    for (int i = 0; i < swaps_.size(); ++i) {
      cout << swaps_[i].first << " " << swaps_[i].second << "\n";
    }
  }

};

int main() {
  std::ios_base::sync_with_stdio(false);
  Heap min_heap;
  min_heap.build();
  min_heap.dumpSwaps();
  return 0;
}
