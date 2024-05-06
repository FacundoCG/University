#include <bits/stdc++.h>

using namespace std;
using building = tuple<int, int>;

tuple<int, int> sumTuples(const tuple<int, int>& a, const tuple<int, int>& b){
    int x = get<0>(a) + get<0>(b);
    int y = get<1>(a) + get<1>(b);

    return {x, y};
}

tuple<int, int> maxTuple(tuple<int, int>& a, tuple<int, int>& b){
    if (get<1>(a) > get<1>(b)){
        return a;
    } else if (get<1>(a) < get<1>(b)){
        return b;
    } else {
        if (get<0>(a) > get<0>(b)){
            return a;
        } else {
            return b;
        }
    }
} 

tuple<int, int> LIS(vector<building>& skylines, vector<vector<tuple<int, int>>>& memo, int i, int j){
    if (i == -1){
        return {0, 0};
    }

    int n = skylines.size();
    
    if (get<0>(memo[i][j]) != -1){
        return memo[i][j];
    }

    if (j != n && get<0>(skylines[i]) >= get<0>(skylines[j])){
        memo[i][j] = LIS(skylines, memo, i-1, j);
    } else {
        tuple<int, int> extra = {1, get<1>(skylines[i])};
        tuple<int, int> ignoreBuilding = LIS(skylines, memo, i-1, j);
        tuple<int, int> useBuilding = sumTuples(LIS(skylines, memo, i-1, i), extra); 
        memo[i][j] = maxTuple(ignoreBuilding, useBuilding);
    }

    return memo[i][j];
}

tuple<int, int> LDS(vector<building>& skylines, vector<vector<tuple<int, int>>>& memo, int i, int j){
    if (i == -1){
        return {0, 0};
    }

    int n = skylines.size();
    
    if (get<0>(memo[i][j]) != -1){
        return memo[i][j];
    }

    if (j != n && get<0>(skylines[i]) <= get<0>(skylines[j])){
        memo[i][j] = LDS(skylines, memo, i-1, j);
    } else {
        tuple<int, int> extra = {1, get<1>(skylines[i])};
        tuple<int, int> ignoreBuilding = LDS(skylines, memo, i-1, j);
        tuple<int, int> useBuilding = sumTuples(LDS(skylines, memo, i-1, i), extra); 
        memo[i][j] = maxTuple(ignoreBuilding, useBuilding);
    }

    return memo[i][j];
}

int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;

    for (int i = 1; i <= t; i++) {
        int n;
        cin >> n;
        vector<building> skyline(n);
        vector<vector<tuple<int, int>>> memo1(n, vector<tuple<int, int>>(n+1, {-1, 0}));
        vector<vector<tuple<int, int>>> memo2(n, vector<tuple<int, int>>(n+1, {-1, 0}));


        for (int j = 0; j < n; j++) {
            int height;
            cin >> height;
            skyline[j] = {height, 0};
        }

        for (int j = 0; j < n; j++) {
            int width;
            cin >> width;
            skyline[j] = {get<0>(skyline[j]), width};
        }

        int increasing = get<1>(LIS(skyline, memo1, n-1, n));
        int decreasing = get<1>(LDS(skyline, memo2, n-1, n));

        cout << "Case " << i << ". ";

        if (increasing >= decreasing) {
            cout << "Increasing (" << increasing << "). ";
            cout << "Decreasing (" << decreasing << ")." << "\n";
        } else {
            cout << "Decreasing (" << decreasing << "). ";
            cout << "Increasing (" << increasing << ")." << "\n";
        }
    }
}