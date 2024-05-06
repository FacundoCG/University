#include <bits/stdc++.h>

using namespace std;

// DP Algorithm with Top-Down approach
int life_journey_TD(vector<vector<int>>& grid, vector<vector<int>>& memo, int i, int j){
    int m = grid.size();
    int n = grid[0].size();

    if (i == m - 1 && j == n - 1){
        return abs(min(grid[i][j], 0)) + 1;
    }

    if (memo[i][j] == -1){
        int minLife = 0;

        if (i == m - 1 && j < n - 1){
            minLife = life_journey_TD(grid, memo, i, j+1);
        }

        if (i < m - 1 && j == n - 1){
            minLife = life_journey_TD(grid, memo, i+1, j);
        }

        if (i < m - 1 && j < n - 1){
            minLife = min(life_journey_TD(grid, memo, i+1, j), life_journey_TD(grid, memo, i, j+1));
        }

        if (grid[i][j] >= 0 && grid[i][j] >= minLife){
                memo[i][j] = 1;
            } else if (grid[i][j] >= 0 && grid[i][j] < minLife){
                memo[i][j] = minLife - grid[i][j];
            } else {
                memo[i][j] = minLife + abs(grid[i][j]);
            }
    }

    return memo[i][j];
}

int life_journey_BU(vector<vector<int>>& grid){
    int m = grid.size();
    int n = grid[0].size();
    vector<vector<int>> memo (m, vector<int>(n, -1));

    for (int i = m - 1; i >= 0; i--){
        for (int j = n - 1; j >= 0; j--){
            int minLife = 0;

            if (i == m - 1 && j < n - 1){
                minLife = memo[i][j+1];
            } else if (i < m - 1 && j == n - 1){
                minLife = memo[i+1][j];
            } else if (i < m - 1 && j < n - 1){
                minLife = min(memo[i+1][j], memo[i][j+1]);
            }

            if (i == m - 1 && j == n - 1){
                memo[i][j] = abs(min(grid[i][j], 0)) + 1;
            } else if (grid[i][j] >= 0 && grid[i][j] >= minLife){
                memo[i][j] = 1;
            } else if (grid[i][j] >= 0 && grid[i][j] < minLife){
                memo[i][j] = minLife - grid[i][j];
            } else {
                memo[i][j] = minLife + abs(grid[i][j]);
            }
        }
    }

    return memo[0][0];
}


int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);

    int m, n;
    cin >> m >> n;

    vector<vector<int>> grid (m, vector<int>(n, 0));
    vector<vector<int>> memoTD(m, vector<int>(n,-1));

    for (int i = 0; i < m; i++){
        for (int j = 0; j < n; j++){
            int k;
            cin >> k;
            grid[i][j] = k;
        }
    }

    //cout << "The miminum life to travel for the grid is: " << life_journey_TD(grid, memoTD, 0, 0) << "\n";
    cout << "The miminum life to travel for the grid is: " << life_journey_BU(grid) << "\n";
}