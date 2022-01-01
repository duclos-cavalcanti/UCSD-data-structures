#include <iostream>
#include <string>
#include <vector>

using std::string;
typedef unsigned long long ull;

struct Data {
  string pattern;
  string text;
};

void printOccurrences(const std::vector<int>& output) {
    for (size_t i = 0; i < output.size(); ++i)
        std::cout << output[i] << " ";
    std::cout << "\n";
}

unsigned long long polyHash(const string& str, const long long prime, const long long x) {
  unsigned long long hash = 0;

  for (int i = static_cast<int> (str.size()) - 1; i >= 0; --i) {
    hash = (hash * x + str[i]) % prime;
  }
  return hash;
}

std::vector< unsigned long long > 
precomputeHashes(const string& T, const string& P, long long prime, long long x) {
  std::vector< unsigned long long > H(T.size() - P.size() + 1);
  std::string sub = T.substr(T.size() - P.size(),  P.size());

  H[T.size() - P.size()] = polyHash(sub, prime, x);
  unsigned long long y = 1;

  for (size_t i = 1; i <= P.size(); ++i) {
    y = (y * x) % prime;
  }

  for (int i = static_cast< int >(T.size() - P.size() - 1); i >= 0; --i) {
    // H[i] = ( ( x * H[i + 1] + T[i] - y * T[i + P.size()] ) % prime );
    H[i] = ( ( x * H[i + 1] + T[i] - ( y * T[i + P.size()] % prime ) ) + prime ) % prime;
  }
  
  return H;
}

// Robin Karp
std::vector<int> findSubstring(const Data& input) {
    const string& P = input.pattern;
    const string& T = input.text;
    long long prime = 1000000007;
    long long x = 236;
    std::vector<int> pos;
    unsigned long long  pattern_hash = polyHash(P, prime, x);
    std::vector< unsigned long long > substring_hashes = precomputeHashes(T, P, prime, x);

    for (size_t i = 0; i <= T.size() - P.size(); i++) {
        if (pattern_hash != substring_hashes[i])
            continue;
        
        string substr = T.substr(i, P.size());
        if (substr == P)
            pos.push_back(i);
    }
    

    return pos;
}

Data readInput() {
    Data data;
    std::cin >> data.pattern >> data.text;
    return data;
}

int main() {
    std::ios_base::sync_with_stdio(false);

    Data data = readInput();
    std::vector<int> positions = findSubstring(data);
    printOccurrences(positions);

    return 0;
}
