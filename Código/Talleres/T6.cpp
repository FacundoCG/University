#include <bits/stdc++.h>
using namespace std;

int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);

    string s1, s2;
    cin >> s1 >> s2;

    int n = s1.size();
    int a1 = 0;
    int a2 = 0;
    int b1 = 0;
    int b2 = 0;

    for (int i = 0; i < n; i++) {
        if (s1[i] == 'a'){
            a1++;
        } else {
            b1++;
        }

        if (s2[i] == 'a'){
            a2++;
        } else {
            b2++;
        }
    }

    if (a1 != a2 || b1 != b2) {
        cout << -1 << "\n";
    } else {

    }
}