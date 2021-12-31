#include <iostream>
#include <list>
#include <string>
#include <vector>
#include <algorithm>

using std::string;
using std::vector;
using std::cin;

struct Query {
  string type;
  string str;
  size_t ind;
};

class QueryProcessor {
  int bucket_count;
  vector< vector<string> > hash_table;

  size_t polyHash(const string& str) const {
    unsigned long long hash = 0;
    static const size_t multiplier = 263;
    static const size_t prime = 1000000007;

    for (int i = static_cast<int> (str.size()) - 1; i >= 0; --i) {
      hash = (hash * multiplier + str[i]) % prime;
    }
    hash %= bucket_count; // bucket_count is cardinality m
    return hash;
  }

  bool findString(string str) {
    int index = polyHash(str);
    for (int i = static_cast<int>(hash_table[index].size()) - 1; i >= 0; --i)
      if (hash_table[index][i] == str)
        return true;
    return false;
  }

  void insertString(string str) {
    if(!findString(str))
      hash_table[polyHash(str)].push_back(str);
  }

  void deleteString(string str) {
    int index = polyHash(str);
    for (int i = static_cast<int>(hash_table[index].size()) - 1; i >= 0; --i)
      if (hash_table[index][i] == str)
        hash_table[index].erase(hash_table[index].begin() + i);
  }

  void printHashTableEntry(int ind) {
    for (int i = static_cast<int>(hash_table[ind].size()) - 1; i >= 0; --i) {
      std::cout << hash_table[ind][i] << " ";
    }
    std::cout << "\n";
  }


public:
    explicit QueryProcessor() {
        int m;
        cin >> m;
        bucket_count = m;
        hash_table.resize(bucket_count);
      }

    void processQuery(const Query& query) {
      if (query.type == "check") {
        printHashTableEntry(query.ind);
      } else if (query.type == "find") {
        if(findString(query.str))
          std::cout << "yes\n";
        else
          std::cout << "no\n";
      } else if (query.type == "add") {
        insertString(query.str);
      } else if (query.type == "del") {
        deleteString(query.str);
      } else {
        std::invalid_argument("Improper query type processing, must be of types: add, find, del or check");
      }
    }

    Query readQuery() const {
      Query query;
      cin >> query.type;

      if (query.type == "add")
        cin >> query.str;
      else if (query.type == "find")
        cin >> query.str;
      else if (query.type == "del")
        cin >> query.str;
      else if (query.type == "check")
        cin >> query.ind;
      else
        std::invalid_argument("Improper query type reading, must be of types: add, find, del or check");

      return query;
    }

    void processQueries() {
      int num_queries;
      cin >> num_queries;
      for (int i = 0; i < num_queries; ++i) {
        processQuery(readQuery());
      }
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);

    QueryProcessor p;
    p.processQueries();

    return 0;
}
