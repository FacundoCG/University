#include <bits/stdc++.h>

using namespace std;
using player = tuple<string, int, int>;

bool isGreater(player& b, player& a){
    bool p1 = get<1>(b) > get<1>(a);
    bool p2 = (get<1>(b) == get<1>(a)) && (get<2>(b) < get<2>(a));
    bool p3 = (get<1>(b) == get<1>(a)) && (get<2>(b) == get<2>(a)) && (get<0>(b) < get<0>(a));

    return p1 || p2 || p3;
}

vector<player> mergeVectors(vector<player>& arr1, vector<player>& arr2){
    int n = arr1.size();
    int m = arr2.size();
    int t = n + m;
    vector<player> res(t);

    int j = 0;
    int h = 0;

    for (int i = 0; i < t; i++){
        if (j < n && h < m){
            if (isGreater(arr2[h],arr1[j])){
                res[i] = arr1[j];
                j++;
            } else {
                res[i] = arr2[h];
                h++;
            }
        } else if (j < n){
            res[i] = arr1[j];
            j++;
        } else {
            res[i] = arr2[h];
            h++;
        }
    }

    return res;
}

vector<player> mergeSort (vector<player>& arr){
    int n = arr.size();

    if (n <= 1){
        return arr;
    }

    int mid = n / 2;

    vector<player> leftHalf, rightHalf;

    for (int i = 0; i < mid; i++){
        leftHalf.push_back(arr[i]);
    }

    for (int i = mid; i < n; i++){
        rightHalf.push_back(arr[i]);
    }

    vector<player> res1 = mergeSort(leftHalf);
    vector<player> res2 = mergeSort(rightHalf);

    return mergeVectors(res1, res2);
}


int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;

    for (int i = 1; i <= t; i++) {
        vector<player> players(10);

        for (int j = 0; j < 10; j++){
            string name;
            int attack, defense;

            cin >> name >> attack >> defense;
            players[j] = {name, attack, defense};
        }

        vector<player> sortedPlayers = mergeSort(players);
        vector<string> attackers (5);
        vector<string> defensors (5);

        for (int j = 0; j < 5; j++){
            defensors[j] = get<0>(sortedPlayers[j]);
        }

        for (int j = 0; j < 5; j++){
            attackers[j] = get<0>(sortedPlayers[j+5]);
        }

        sort(attackers.begin(), attackers.end());
        sort(defensors.begin(), defensors.end());

        cout << "Case " << i << ":" << "\n";
        cout << "(";
        for (int j = 0; j < 5; j++){
            if (j == 4){
                cout << attackers[j] << ")" << "\n";

            } else {
                cout << attackers[j] << ", ";
            }
        }

        cout << "(";
        for (int j = 0; j < 5; j++){
            if (j == 4){
                cout << defensors[j] << ")" << "\n";

            } else {
                cout << defensors[j] << ", ";
            }
        }
    }
}