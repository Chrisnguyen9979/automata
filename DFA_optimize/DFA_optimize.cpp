#include "utils.h"

class DFA {
    private:
        vector<char> alphabet;
        vector<char> state;
        vector<char> accept;
        map<pair<char, char>, char> transmission;
    public:
        DFA() {};
        DFA(vector<char> in_alphabet, vector<char> in_state, vector<char> in_accept, map<pair<char, char>, char> in_transmission) {
            alphabet = in_alphabet;
            state = in_state;
            accept= in_accept;
            transmission = in_transmission;
        };
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
                        cout << transmission[{state[i], alphabet[j]}] << " ";
                }
                cout << endl;
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
        DFA optimize(){
            vector<vector<char>> all = initialize(state, accept);
            
            int prev_size;
            int it = 0;
            do {
                prev_size = all.size();
                update(all, transmission, alphabet);
                it++;
            } while (it <= 10000 && all.size() != prev_size);
            normalize(all);
            return DFA(alphabet, update_state(all), update_accept(all, accept), update_transmission(all, transmission, alphabet));
        } 
};

int main(){
    DFA dfa;
    dfa.read();
    DFA optimized_dfa = dfa.optimize();

    optimized_dfa.print();
    return 0;
}