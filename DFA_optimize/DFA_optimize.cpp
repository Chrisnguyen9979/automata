#include "utils.h"

class DFA {
    private:
        vector<char> alphabet;
        vector<int> state;
        vector<int> accept;
        map<pair<int, char>, int> transmission;
    public:
        DFA() {};
        ~DFA() {};
        DFA(vector<char> in_alphabet, vector<int> in_state, vector<int> in_accept, map<pair<int, char>, int> in_transmission) {
            alphabet = in_alphabet;
            state = in_state;
            accept= in_accept;
            transmission = in_transmission;
        };
        void read(){
            ifstream in("config.txt");
            //Lưu lại đầu vào cũ
            streambuf *cinbuf = std::cin.rdbuf();
            //Chuyển hướng đầu vào từ file config
            cin.rdbuf(in.rdbuf());
            char temp;
            int temp_int;

            int n_char;
            cin >> n_char;
            for (int i = 0; i < n_char; i++){
                cin >> temp;
                alphabet.push_back(temp);
            }

            int n_state;
            cin >> n_state;
            for (int i = 0; i < n_state; i++){
                cin >> temp_int;
                state.push_back(temp_int);
            }

            int n_accept;
            cin >> n_accept;
            for (int i = 0; i < n_accept; i++){
                cin >> temp_int;
                accept.push_back(temp_int);
            }

            for (int i = 0; i < n_state; i++){
                for (int j = 0; j < n_char; j++){
                        cin >> temp_int;
                        transmission[{state[i], alphabet[j]}] = temp_int;
                }
            }
            //Chuyển hướng đầu vào lại như ban đầu
            cin.rdbuf(cinbuf);
        }
        void print(){
            // for (int i = 0; i < state.size(); i++){
            //     for (int j = 0; j < alphabet.size(); j++){
            //             cout << state[i] << " " << alphabet[j] << " " << transmission[{state[i], alphabet[j]}] << endl;
            //     }
            // }
            // cout << "Accept at ";
            // for (auto q : accept){
            //     cout << q << " ";
            // }
            // cout << endl;
            cout << alphabet.size() << endl;
            for (int i = 0; i < alphabet.size() - 1; i++){
                cout << (char)alphabet[i] << " "; 
            }
            cout << (char)alphabet[alphabet.size() - 1] << endl; 

            cout << state.size() << endl;
            for (int i = 0; i < state.size() - 1; i++){
                cout << state[i] << " "; 
            }
            cout << state[state.size() - 1] << endl; 

            cout << accept.size() << endl;
            for (int i = 0; i < accept.size() - 1; i++){
                cout << accept[i] << " "; 
            }
            cout << accept[accept.size() - 1] << endl; 

            for (int i = 0; i < state.size(); i++){
                for (int j = 0; j < alphabet.size() - 1; j++){
                        cout << transmission[{state[i], alphabet[j]}] << " ";
                }
                cout << transmission[{state[i], alphabet[alphabet.size() - 1]}] << endl;
            }
        }
        bool include(string s){
            int start = state[0];
            for (auto c : s){
                start = transmission[{start, c}];
            }
            if (find(accept.begin(), accept.end(), start) != accept.end()){
                return true;
            }
            return false;
        }
        DFA optimize(){
            vector<vector<int>> all = initialize(state, accept);
            
            int prev_size;
            int it = 0;
            do {
                prev_size = all.size();
                update(all, transmission, alphabet);
                it++;
            } while (it <= 10000 && all.size() != prev_size);

            
            normalize(all);

            cout << "Cac tap trang thai sau khi toi uu hoa: " << endl;
            for (auto it1 : all){
                for (auto it2 : it1){
                    cout << it2 << " ";
                }
                cout << endl;
            }
            return DFA(alphabet, update_state(all), update_accept(all, accept), update_transmission(all, transmission, alphabet));
        }
};

int main(){
    DFA dfa;
    dfa.read();
    DFA optimized_dfa = dfa.optimize();

    ofstream out("output.txt");
    cout.rdbuf(out.rdbuf());
    optimized_dfa.print();
    return 0;
}