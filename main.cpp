#include <bits/stdc++.h>
#include "DFA.cpp"
using namespace std;

ifstream in("date.in");

DFA Complementary(const DFA& other) {
    DFA ans = other;
    ans.finalStates.clear();

    vector< bool > isFinal(other.size());
    for(auto state: other.finalStates) {
        isFinal[state] = true;
    }

    for(int i = 0; i < ans.size(); ++i) {
        if(!isFinal[i]) {
            ans.finalStates.push_back(i);
        }
    }

    return ans;
}

DFA Intersection(const DFA& firstDFA, const DFA& secondDFA) {
    DFA ans(firstDFA.size() * secondDFA.size());

    cout <<firstDFA << "\n" << secondDFA << "\n";


    for(int i = 0; i < firstDFA.size(); ++i) {
        for(int j = 0; j < secondDFA.size(); ++j) {
            for(int k = 0; k < 26; ++k) {
                int tempState1 = firstDFA.GetNextState(i, char('a' + k));
                int tempState2 = secondDFA.GetNextState(j, char('a' + k));

                if(tempState1 == -1 || tempState2 == -1) {
                    continue;
                }

                ans.transitions[i * firstDFA.size() + j].push_back({tempState1 * firstDFA.size() + tempState2, char('a' + k)});
            }
        }
    }

    vector< bool > isFinal1(firstDFA.size());
    for(auto state: firstDFA.finalStates) {
        isFinal1[state] = true;
    }

    vector< bool > isFinal2(secondDFA.size());
    for(auto state: secondDFA.finalStates) {
        isFinal2[state] = true;
    }

    ans.initialState = firstDFA.initialState * firstDFA.size() + secondDFA.initialState;
    for(int i = 0; i < firstDFA.size(); ++i) {
        for(int j = 0; j < secondDFA.size(); ++j) {
            if(isFinal1[i] && isFinal2[j]) {
                ans.finalStates.push_back(i * firstDFA.size() + j);
            }
        }
    }

    return ans;
}

bool isEmpty(const DFA& other) {
    vector< bool > isFinal(other.size());
    vector< bool > inQueue(other.size());

    for(auto state: other.finalStates) {
        isFinal[state] = true;
    }

    stack< int > s;
    s.push(other.initialState);

    while(!s.empty()) {
        int temp = s.top(); s.pop();

        if(isFinal[temp]) {
            return false;
        }

        for(auto it: other.transitions[temp]) {
            if(!inQueue[it.first]) {
                s.push(it.first);
                inQueue[it.first] = true;
            }
        }
    }

    return true;
}

int main() {

    DFA firstDFA, secondDFA;
    in >> firstDFA >> secondDFA;

    if(isEmpty(Intersection(firstDFA, Complementary(secondDFA))) && isEmpty(Intersection(Complementary(firstDFA), secondDFA))) {
        cout << "Automatele accepta acelasi limbaj!\n";
    } else {
        cout << "Automatele nu accepta acelasi limbaj!\n";
    }

    return 0;
}