#include <bits/stdc++.h>

using namespace std;

int sum(vector<int>& arr, int i, int j){
    int sum = 0;

    for(int k = i; k < j+1; k++){
        sum += arr[k];
    }

    return sum;
}

// Divide and Conquer Algorithm
bool left_most(vector<int>& arr, int i, int j){
    if (i == j){
        return true;
    }

    int leftSum = sum(arr, i, (i+j)/2);
    int rightSum = sum(arr, (i+j)/2 + 1, j);

    return (leftSum >= rightSum) && left_most(arr, i, (i+j)/2) && left_most(arr, (i+j)/2 + 1, j);
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

    cout << "Does the array satisfy the conditions? " << left_most(arr, 0, n-1) << "\n";
}