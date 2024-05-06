#include <bits/stdc++.h>

using namespace std;

// Divide and Conquer algorithm
int logarithmic_power(int a, int b){
    if (b == 1){
        return a;
    }

    return logarithmic_power(a, b/2) * logarithmic_power(a, b - b/2);
}

int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);

    int a, b;
    cin >> a >> b;

    cout << "The result of " << a << " elevated to " << b << " is: " << logarithmic_power(a, b) << "\n";
}