#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <algorithm>
#include <fstream>

using namespace std;

class DFA {
    private:
        vector<char> alphabet;
        vector<char> state;
        vector<char> accept;
        map<pair<char, char>, char> transmission;
    public:
        DFA() {};
        ~DFA() {};
        void read(){
            ifstream in("config.txt");
            //Lưu lại đầu vào cũ
            streambuf *cinbuf = std::cin.rdbuf();
            //Chuyển hướng đầu vào từ file config
            cin.rdbuf(in.rdbuf());
            char temp;
            int n_char;
            cin >> n_char;
            for (int i = 0; i < n_char; i++){
                cin >> temp;
                alphabet.push_back(temp);
            }
            int n_state;
            cin >> n_state;
            for (int i = 0; i < n_state; i++){
                cin >> temp;
                state.push_back(temp);
            }
            int n_accept;
            cin >> n_accept;
            for (int i = 0; i < n_accept; i++){
                cin >> temp;
                accept.push_back(temp);
            }
            for (int i = 0; i < n_state; i++){
                for (int j = 0; j < n_char; j++){
                        cin >> temp;
                        transmission[{state[i], alphabet[j]}] = temp;
                }
            }
            //Chuyển hướng đầu vào lại như ban đầu
            cin.rdbuf(cinbuf);
        }
        void print(){
            for (int i = 0; i < state.size(); i++){
                for (int j = 0; j < alphabet.size(); j++){
                        cout << state[i] << " " << alphabet[j] << " " << transmission[{state[i], alphabet[j]}] << endl;
                }
            }
            cout << "Accept at ";
            for (auto q : accept){
                cout << q << " ";
            }
            cout << endl;
        }
        bool include(string s){
            char start = state[0];
            for (auto c : s){
                start = transmission[{start, c}];
            }
            if (find(accept.begin(), accept.end(), start) != accept.end()){
                return true;
            }
            return false;
        }
};

int main(){
    DFA dfa;
    dfa.read();

    int tc = 0;
    cin >> tc; getchar();
    while (tc--){
        string a;
        
        getline(cin, a);
        cout << dfa.include(a) << endl;
    }
    return 0;
}