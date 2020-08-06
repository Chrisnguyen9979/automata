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