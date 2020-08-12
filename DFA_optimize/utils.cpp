#include "utils.h"

int find_set(int s, vector<vector<int>> all){
    int res = -1;
    for (int i = 0; i < all.size(); i++){
        if (find(all[i].begin(), all[i].end(), s) != all[i].end()){
            res = i;
            break;
        }
    }
    return res;
}
vector<vector<int>> initialize(vector<int> state, vector<int> accept){
    vector<vector<int>> all(2);

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
vector<vector<int>> divide(vector<int> state, vector<vector<int>> all, map<pair<int, char>, int> transmission, char c){
    vector<vector<int>> res(all.size());
    for (auto s : state){
        int next_state = transmission[{s, c}];

        int idx = find_set(next_state, all);
        res[idx].push_back(s);
    }
    return res;
}

void update(vector<vector<int>> &all, map<pair<int, char>, int> transmission, vector<char> alphabet){
    vector<vector<int>> temp;

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
void normalize(vector<vector<int>> &all){
    int start_index = -1;
    for (int i = 0; i < all.size(); i++){
        if (find(all[i].begin(), all[i].end(), 0) != all[i].end()){
            start_index = i;
            break;
        }
    }

    vector<int> temp(all[start_index].size());
    copy(all[start_index].begin(), all[start_index].end(), temp.begin());

    all.erase(all.begin() + start_index);
    all.insert(all.begin(), temp);
}
bool is_new(vector<vector<int>> divided){
    int cnt = 0;
    for (auto s : divided){
        if (s.size() > 0){
            cnt++;
        }
    }
    return cnt > 1;
}

vector<int> update_state(vector<vector<int>> all){
    vector<int> state;
    for (int i = 0; i < all.size(); i++){
        state.push_back(i);
    }
    return state;
}
vector<int> update_accept(vector<vector<int>> all, vector<int> old_accept){
    vector<int> accept;
    for (int i = 0; i < all.size(); i++){
        if (find(old_accept.begin(), old_accept.end(), all[i][0]) != old_accept.end()){
            accept.push_back(i);
        }
    }
    return accept;
}
map<pair<int, char>, int> update_transmission(vector<vector<int>> all, map<pair<int, char>, int> old_transmission, vector<char> alphabet){
    map<pair<int, char>, int> transmission;
    for (int i = 0; i < all.size(); i++){
        for (auto c : alphabet){
            int next_state = old_transmission[{all[i][0], c}];
            transmission[{i, c}] = find_set(next_state, all);
        }
    }
    return transmission;
}