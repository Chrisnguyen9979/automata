# automata
Coding exercise of Automata and Formal Language

input file:
+ First line includes an interger n.
+ Next n lines, each line include a string to test.
output:
+ n lines.
+ line ith includes 1 if string ith in input file is accepted by DFA else 0.
config:
+ First line include an  interger n_char, number of characters in alphabet
+ Second line include n_char value in char type

+ Third line include an interger n_state, number of state in dfa
+ Fourth line include n_state value as name for each state in char type

+ Fifth line include an interger n_accept, number of accepted state in dfa (n_accept <= n_state)
+ Fourth line include n_accept value as name for each accepted state in char type (accepted states set is subset of states)

+ n_state line, each line include n_char names of states:
  - ith value in jth line: result of state j with ith character as input.
  - example:
    alphabet a, b
    1 0 #delta(q0, a) = q1, delta(q0, b) = q0
    2 0 #delta(q1, a) = q2, delta(q1, b) = q0
    2 3 #delta(q2, a) = q2, delta(q2, b) = q3
    2 4 #delta(q3, a) = q2, delta(q3, b) = q4
    4 4 #delta(q4, a) = q4, delta(q4, b) = q4
    
