#include <iostream>
#include <vector>
#include <string>
#include <map>

using std::string;
using std::vector;
using std::cin;

struct Query {
  string type;
  string name;
  int number;
};

vector<Query> read_queries() {
  int n;
  cin >> n;
  vector<Query> queries(n);
  for (int i = 0; i < n; ++i) {
    cin >> queries[i].type;
    if (queries[i].type == "add")
      cin >> queries[i].number >> queries[i].name;
    else
      cin >> queries[i].number;
  }
  return queries;
}


vector<string> process_queries(const vector<Query>& queries) {
  vector<string> results;
  std::map<int, string> contacts;

  for (size_t i = 0; i < queries.size(); ++i) {
    int number = queries[i].number;

    if (queries[i].type == "add") { // add
      contacts[number] = queries[i].name;

    } else if (queries[i].type == "del") { // delete
      if (contacts.find(number) != contacts.end())
        contacts.erase(contacts.find(number));

    } else { // find
      if (contacts.find(number) != contacts.end()) {
        results.push_back(contacts[number]);
      } else {
        results.push_back("not found");
      }

    }
  }
  return results;
}

void write_results(const vector<string>& result) {
  for (size_t i = 0; i < result.size(); ++i)
    std::cout << result[i] << "\n";
}

int main() {
  vector<Query> queries = read_queries();
  vector<string> results = process_queries(queries);
  write_results(results);
  
  return 0;
}
