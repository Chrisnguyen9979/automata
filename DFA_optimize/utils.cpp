#include "utils.h"

int find_set(char s, vector<vector<char>> all){
    int res = -1;
    for (int i = 0; i < all.size(); i++){
        if (find(all[i].begin(), all[i].end(), s) != all[i].end()){
            res = i;
            break;
        }
    }
    return res;
}
vector<vector<char>> initialize(vector<char> state, vector<char> accept){
    vector<vector<char>> all(2);

    for (auto s : state){
        if (find(accept.begin(), accept.end(), s) == accept.end()){
            all[0].push_back(s);
        }
        else {
            all[1].push_back(s);
        }
    }
    return all;
}
vector<vector<char>> divide(vector<char> state, vector<vector<char>> all, map<pair<char, char>, char> transmission, char c){
    vector<vector<char>> res(all.size());
    for (auto s : state){
        char next_state = transmission[{s, c}];

        int idx = find_set(next_state, all);
        res[idx].push_back(s);
    }
    return res;
}