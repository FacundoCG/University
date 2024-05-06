#include <bits/stdc++.h>
using namespace std;

bool areEqual(string& a, string& b, int i, int j, int x, int y){
    bool res = true;
    
    for(int k = i; k <= j; k++){
        if (a[k] != b[x]){
            res = false;
            break;
        } else {
            x++;
        }
    }

    return res;
}

bool areEquivalents(string& a, string& b, int i, int j, int x, int y) {
    if (i == j || x == y){
        return a[i] == b[x];
    }

    if (areEqual(a, b, i, j, x, y)){
        return true;
    }

    if ((j - i + 1) % 2 != 0 || (y - x + 1) % 2 != 0) {
        return false;
    }

    int firstMid = (i+j)/2;
    int secondMid = (x+y)/2;

    bool firstCombination = areEquivalents(a, b, i, firstMid, x, secondMid) && areEquivalents(a, b, firstMid + 1, j, secondMid + 1, y);
    
    if (firstCombination){
        return true;
    }

    bool secondCombination = areEquivalents(a, b, i, firstMid, secondMid + 1, y) && areEquivalents(a, b, firstMid + 1, j, x, secondMid);

    return secondCombination;
}


int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);

    string s1, s2;
    cin >> s1 >> s2;

    int n = s1.size();
    
    bool flag = areEquivalents(s1, s2, 0, n-1, 0, n-1);

    if (flag) {
        cout << "YES" << "\n";
    } else {
        cout << "NO" << "\n";
    } 
}