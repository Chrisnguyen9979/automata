#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <algorithm>
#include <fstream>
#include <queue>

using namespace std;

int find_set(char s, vector<vector<char>> all);
vector<vector<char>> initialize(vector<char> state, vector<char> accept);
vector<vector<char>> divide(vector<char> state, vector<vector<char>> all, map<pair<char, char>, char> transmission, char c);
void update(vector<vector<char>> &all, map<pair<char, char>, char> transmission, vector<char> alphabet);

bool is_new(vector<vector<char>> divided);
void normalize(vector<vector<char>> &all);

vector<char> update_state(vector<vector<char>> all);
vector<char> update_accept(vector<vector<char>> all, vector<char> old_accept);
map<pair<char, char>, char> update_transmission(vector<vector<char>> all, map<pair<char, char>, char> old_transmission, vector<char> alphabet);

