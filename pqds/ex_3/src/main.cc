#include <cstdio>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <iostream>

using std::cin;
using std::cout;
using std::endl;
using std::max;
using std::vector;

// table
struct DisjointSetsElement {
	int size, parent, rank;
	
	DisjointSetsElement(int size = 0, int parent = -1, int rank = 0):
	    size(size), 
			parent(parent), 
			rank(rank) 
	{}
};

// group of tables
struct DisjointSets {
	int size;
	int max_table_size;
	vector <DisjointSetsElement> sets;

	DisjointSets(int size): 
			size(size),
			max_table_size(0), 
			sets(size) {
		for (int i = 0; i < size; i++)
			MakeSet(i);
	}

	int getParent(int table) {
    return sets[table].parent;
	}

	// MakeSet
	void MakeSet(int i) {
		sets[i].parent = i;
		sets[i].rank = 0;
	}

	// Find: finds unique ID / Actual Table that symbolic links may refer to
	int Find(int i) {
		if(i != getParent(i))
			sets[i].parent = Find(getParent(i));
	
		return getParent(i);
	}

	// Union
	void Union(int destination, int source) {
    int realDestination = Find(destination);
    int realSource = Find(source);

		if (realDestination != realSource) {
			// merge two components using union by rank heuristic
			sets[realSource].parent = realDestination;
                        
			// update max_table_size
			sets[realDestination].size += sets[realSource].size;
			sets[realSource].size = 0;

			max_table_size = max(max_table_size, sets[realDestination].size);
		}		
	}

	// Union
	void merge(int destination, int source) {
		Union(destination, source);
	}
};

int main() {
	// initializing DS Tables
	int num_tables, num_queries;
	cin >> num_tables >> num_queries;

	DisjointSets tables(num_tables);

	// initializing number of rows (size) per table
	for (auto &table : tables.sets) {
		cin >> table.size; // initializes number of rows in the iterated table
		tables.max_table_size = max(tables.max_table_size, table.size);
	}

	for (int i = 0; i < num_queries; i++) {
		// get destination and source tables
		int dst, src;
		cin >> dst >> src;

		// follow up on merge query
		tables.merge(dst - 1, src - 1);
		cout << tables.max_table_size << endl;
	}

	return 0;
}

