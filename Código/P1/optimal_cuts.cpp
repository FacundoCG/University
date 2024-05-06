#include <bits/stdc++.h>

using namespace std;

#include <vector>

class specialVector {
private:
    vector<bool> data;
    int falseCount;

public:
    specialVector(int size) : data(size, true), falseCount(0) {}

    // Function to set the value at index to false
    void setFalse(int index) {
        if (data[index]) {
            data[index] = false;
            falseCount++;
        }
    }

    // Function to set the value at index to true
    void setTrue(int index) {
        if (!data[index]) {
            data[index] = true;
            falseCount--;
        }
    }

    // Function to check if the value at index is false
    bool available(int index) const {
        return data[index];
    }

    // Function to get the number of false values
    int cutsUsed() const {
        return falseCount;
    }

    // Function to get the size of the vector
    int size() const {
        return data.size();
    }
};

// DP Algorithm with approach Top-Down
int optimal_cuts_TD(vector<int>& cuts, specialVector& availableCuts, vector<vector<int>>& memo, int i, int j){
	int n = cuts.size();

        if (n == 0){
                return 0;
        }

	if (availableCuts.cutsUsed() == n){
		return 0;
	}

	if (i > j){
		return INT_MAX;
	}

	if (memo[i][j] == INT_MAX){
		for (int k = 0; k < n; k++){
			if (availableCuts.available(k)){
				availableCuts.setFalse(k);
                                int leftHalf = optimal_cuts_TD(cuts, availableCuts, memo, i, cuts[k]);
                                int rightHalf = optimal_cuts_TD(cuts, availableCuts, memo, cuts[k], j);

                                if (leftHalf != INT_MAX && rightHalf != INT_MAX){
                                        memo[i][j] = min(memo[i][j], (j-i) + leftHalf + rightHalf);
                                } else if (leftHalf != INT_MAX){
                                        memo[i][j] = min(memo[i][j], (j-i) + leftHalf);
                                } else if (rightHalf != INT_MAX){
                                        memo[i][j] = min(memo[i][j], (j-i) + rightHalf);
                                }
				availableCuts.setTrue(k);
			}
		}
	}

	return memo[i][j];
}

int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);

    int l, n;
    cin >> l >> n;

    vector<int> cuts(n);
    vector<vector<int>> memo (l+1, vector<int>(l+1, INT_MAX));
    specialVector availableCuts = specialVector(n);

    for (int i = 0; i < n; i++) {
        int m;
        cin >> m;
        cuts[i] = m;
    }

    cout << optimal_cuts_TD(cuts, availableCuts, memo, 0, l) << "\n";
}