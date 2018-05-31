#include <bits/stdc++.h>
using namespace std;

class DFA {
    public:
        int nrStates, nrLetters, initialState;
        vector< int > finalStates;
        vector< char > alfabet;
        vector< vector< pair< int, char > > > transitions;

        DFA() {}
        DFA(int _size) {
            nrStates = _size;
            transitions.resize(2 * _size);
        }

        int size() const {
            return nrStates;
        }

        int GetNextState(int actualState, char c) const {
            for(auto it: transitions[actualState]) {
                if(it.second == c) {
                    return it.first;
                }
            }

            return -1;
        }

        DFA(const DFA& other) {
           nrStates = other.nrStates;
           nrLetters = other.nrLetters;
           initialState = other.initialState;
           finalStates = other.finalStates;
           alfabet = other.alfabet;
           transitions = other.transitions; 
        }

        friend istream& operator >> (istream& in, DFA& other) {
            in >> other.nrStates; other.transitions.resize(2 * other.size());

            map< int, int > states;
            vector< int > values(2 * other.size());

            for(int i = 0; i < other.size(); ++i) {
                int stateValue; in >> stateValue;
                states[stateValue] = i;
                values[i] = stateValue;
            }

            in >> other.nrLetters; other.alfabet.resize(other.nrLetters);
            for(auto &letter: other.alfabet) {
                in >> letter;
            }

            in >> other.initialState; other.initialState = states[other.initialState];

            int nrFinalStates; in >> nrFinalStates;
            for(int i = 0; i < nrFinalStates; ++i) {
                int state; in >> state;
                other.finalStates.push_back(states[state]);
            }

            int nrTransitions; in >> nrTransitions;
            for(int i = 1; i <= nrTransitions; ++i) {
                int x, y;
                char c;
                in >> x >> c >> y;

                other.transitions[states[x]].push_back({states[y], c});
            }

            return in;
        }
        
        friend ostream& operator << (ostream& out, const DFA& other) {
            out << other.nrStates << '\n';
            out << other.initialState << '\n';

            for(auto it: other.finalStates) {
                out << it << " ";
            } out << '\n';

            for(int i = 0; i < other.size(); ++i) {
                for(auto it: other.transitions[i]) {
                    out << i << " " << it.first << " -> " << it.second << '\n';
                }
            }

            return out;
        }
};