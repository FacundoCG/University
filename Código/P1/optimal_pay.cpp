#include <bits/stdc++.h>

using namespace std;

// Algorithms for a tuple<int,int>

tuple<int, int> sumTuple(tuple<int, int> a, tuple<int, int> b){
    tuple<int, int> res = {get<0>(a) + get<0>(b), get<1>(a) + get<1>(b)};
    return res;
}

tuple<int, int> minTuple (tuple<int, int> a, tuple<int, int> b){
    if (get<0>(a) < get<0>(b)){
        return a;
    } else if (get<0>(b) < get<0>(a)){
        return b;
    } 

    if (get<1>(a) < get<1>(b)){
        return a;
    } else {
        return b;
    }
}

// Backtracking algorithm
tuple<int, int> optimal_pay_BT(vector<int>& money, int i, int c){
	if (i == -1 && c > 0){
		return {INT_MAX, INT_MAX};
	}

	if (c <= 0){
		return {abs(c), 0};
	}

	return minTuple(optimal_pay_BT(money,i-1,c), sumTuple(optimal_pay_BT(money,i-1, c-money[i]), {0,1}));
}

// DP Algorithm with Top-Down approach
tuple<int,int> optimal_pay_TD (vector<int>& money, vector<vector<tuple<int,int>>>& memo, int i, int c){
	if (i == -1 && c > 0){
		return {INT_MAX, INT_MAX};
	}

	if (c <= 0){
		return {abs(c), 0};
	}

	if (get<0>(memo[i][c]) == INT_MIN){
		memo[i][c] = minTuple(optimal_pay_TD(money,memo,i-1,c), sumTuple(optimal_pay_TD(money,memo,i-1, c-money[i]), {0,1}));
	}

	return memo[i][c];
}

// DP Algorithm with Bottom-Up approach
// This algoritm has a space complexity of O(n*c)
tuple<int,int> optimal_pay_BU (vector<int>& money, int c){
	int n = money.size();
	vector<vector<tuple<int,int>>> memo (n+1, vector<tuple<int,int>>(c+1, {INT_MAX, INT_MAX}));
	memo[0][0] = {0, 0};

	for (int i = 1; i<n+1; i++){
		for (int j = 0; j<c+1; j++){
			if (j - money[i-1] >= 0){
				memo[i][j] = minTuple(memo[i-1][j], sumTuple(memo[i-1][j-money[i-1]],{0,1}));
			} else {
				memo[i][j] = minTuple(memo[i-1][j], sumTuple({abs(j-money[i-1]), 0},{0,1}));
			}
		}
	}

	return memo[n][c];
}

// This algoritm has a space complexity of O(c)
tuple<int,int> optimal_pay_BU_V2 (vector<int>& money, int c){
	int n = money.size();
	vector<tuple<int,int>> memo (c+1, {INT_MAX, INT_MAX});
	memo[0] = {0, 0};

	for (int i = 1; i<n+1; i++){
		for (int j = c; j > -1; j--){ // It is important to understand that the order of the iteration matters. If you start from j = 0, the answers will be wrong because you could be using updated elements from the vector
			if (j - money[i-1] >= 0){
				memo[j] = minTuple(memo[j], sumTuple(memo[j-money[i-1]],{0,1}));
			} else {
				memo[j] = minTuple(memo[j], sumTuple({abs(j-money[i-1]), 0},{0,1}));
			}
		}
	}

	return memo[c];
}

int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);

    int cost, n;
    cin >> cost >> n;

    vector<int> money(n);
    vector<vector<tuple<int, int>>> memoTD(n+1, vector<tuple<int, int>>(cost+1, {INT_MIN,INT_MIN}));

    for (int i = 0; i < n; i++) {
        int m;
        cin >> m;
        money[i] = m;
    }

    auto result1 = optimal_pay_BT(money, n-1, cost);
	auto result2 = optimal_pay_TD(money, memoTD, n-1, cost);
	auto result3 = optimal_pay_BU_V2(money, cost);

    cout << "I paid " << get<0>(result1) << " extra and I used " << get<1>(result1) << " tickets" << "\n";
	cout << "I paid " << get<0>(result2) << " extra and I used " << get<1>(result2) << " tickets" << "\n";
	cout << "I paid " << get<0>(result3) << " extra and I used " << get<1>(result3) << " tickets" << "\n";
}