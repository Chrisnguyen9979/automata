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

void update(vector<vector<char>> &all, map<pair<char, char>, char> transmission, vector<char> alphabet){
    vector<vector<char>> temp;

    for (int i = 0; i < all.size(); i++){
        if (all[i].size() == 1){
            continue;
        }
        bool isChanged = false;
        for (auto c : alphabet){
            temp = divide(all[i], all, transmission, c);
            if (is_new(temp)){
                isChanged = true;
                break;
            }
        }
        if (isChanged){
            all.erase(all.begin() + i);
            for (auto t : temp){
                if (t.size() > 0){
                    all.push_back(t);
                }
            }
            break;
        }
        
    }
}
void normalize(vector<vector<char>> &all){
    int start_index = -1;
    for (int i = 0; i < all.size(); i++){
        if (find(all[i].begin(), all[i].end(), '0') != all[i].end()){
            start_index = i;
            break;
        }
    }

    vector<char> temp(all[start_index].size());
    copy(all[start_index].begin(), all[start_index].end(), temp.begin());

    all.erase(all.begin() + start_index);
    all.insert(all.begin(), temp);
}
bool is_new(vector<vector<char>> divided){
    int cnt = 0;
    for (auto s : divided){
        if (s.size() > 0){
            cnt++;
        }
    }
    return cnt > 1;
}

vector<char> update_state(vector<vector<char>> all){
    vector<char> state;
    for (int i = 0; i < all.size(); i++){
        state.push_back((char)('0' + i));
    }
    return state;
}
vector<char> update_accept(vector<vector<char>> all, vector<char> old_accept){
    vector<char> accept;
    for (int i = 0; i < all.size(); i++){
        if (find(old_accept.begin(), old_accept.end(), all[i][0]) != old_accept.end()){
            accept.push_back((char)('0' + i));
        }
    }
    return accept;
}
map<pair<char, char>, char> update_transmission(vector<vector<char>> all, map<pair<char, char>, char> old_transmission, vector<char> alphabet){
    map<pair<char, char>, char> transmission;
    for (int i = 0; i < all.size(); i++){
        for (auto c : alphabet){
            char next_state = old_transmission[{all[i][0], c}];
            transmission[{(char)('0' + i), c}] = (char)('0' + find_set(next_state, all));
        }
    }
    return transmission;
}