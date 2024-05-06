#include <bits/stdc++.h>

using namespace std;

bool mirror_index(vector<int>& arr, int i, int j){
    if (i > j){
        return false;
    }

    if (i == j){
        return arr[i] == i;
    }

    return (arr[i] == i || arr[j] == j) || mirror_index(arr, i+1, (i+j)/2) || mirror_index(arr, (i+j)/2, j-1);
}


int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;

    vector<int> arr (n);

    for (int i = 0; i < n; i++){
        int k;
        cin >> k;
        arr[i] = k;
    }

    cout << "Is there a mirror index? " << mirror_index(arr, 0, n-1) << "\n";
}