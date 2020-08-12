#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <algorithm>
#include <fstream>
#include <queue>

using namespace std;

int find_set(int s, vector<vector<int>> all);
vector<vector<int>> initialize(vector<int> state, vector<int> accept);
vector<vector<int>> divide(vector<int> state, vector<vector<int>> all, map<pair<int, char>, int> transmission, char c);

void update(vector<vector<int>> &all, map<pair<int, char>, int> transmission, vector<char> alphabet);
bool is_new(vector<vector<int>> divided);
void normalize(vector<vector<int>> &all);

vector<int> update_state(vector<vector<int>> all);
vector<int> update_accept(vector<vector<int>> all, vector<int> old_accept);
map<pair<int, char>, int> update_transmission(vector<vector<int>> all, map<pair<int, char>, int> old_transmission, vector<char> alphabet);

