#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Offer Information
struct Offer {
    string name;
    int price, benefit;
    vector<string> features;
};

vector<Offer> offers = {
    {"Daily Data", 49, 45, {"Internet", "4G"}},
    {"Voice Pack", 59, 50, {"Voice", "Call"}},
    {"Combo Smart", 99, 90, {"Internet", "Voice", "SMS"}},
    {"Mega Combo", 199, 185, {"Internet", "Voice", "SMS", "Bonus"}},
    {"SMS Pack", 29, 25, {"SMS"}}
};

// 1. COIN CHANGE - DYNAMIC PROGRAMMING
void coinChange() {
    int coins[] = {10, 20, 50, 100, 200};
    int amount;

    cout << "\nEnter recharge amount: ";
    cin >> amount;

    if (amount < 0) {
        cout << "Invalid amount!\n";
        return;
    }

    vector<long long> dp(amount + 1, 0);
    dp[0] = 1;

    for (int i = 0; i < 5; i++) {
        for (int j = coins[i]; j <= amount; j++) {
            dp[j] += dp[j - coins[i]];
        }
    }

    cout << "Possible combinations: " << dp[amount] << endl;
}

// 2. FRACTIONAL KNAPSACK - GREEDY
struct Item {
    string name;
    double cost, benefit, ratio;
};

void fractionalKnapsack() {
    vector<Item> items = {
        {"Data Add-on", 30, 45, 0},
        {"Voice Add-on", 20, 26, 0},
        {"SMS Add-on", 10, 12, 0},
        {"Bonus Add-on", 40, 48, 0}
    };

    double budget;
    cout << "\nEnter budget: ";
    cin >> budget;

    if (budget < 0) {
        cout << "Invalid budget!\n";
        return;
    }

    for (int i = 0; i < items.size(); i++)
        items[i].ratio = items[i].benefit / items[i].cost;

    sort(items.begin(), items.end(),
         [](Item a, Item b) {
             return a.ratio > b.ratio;
         });

    double totalBenefit = 0;

    cout << "\nSelected Add-ons:\n";

    for (int i = 0; i < items.size(); i++) {
        if (budget <= 0) break;

        if (items[i].cost <= budget) {
            budget -= items[i].cost;
            totalBenefit += items[i].benefit;
            cout << items[i].name << " - Full\n";
        }
        else {
            double fraction = budget / items[i].cost;
            totalBenefit += items[i].benefit * fraction;
            cout << items[i].name << " - Partial\n";
            budget = 0;
        }
    }

    cout << "Total Benefit: " << totalBenefit << endl;
}

// 3. 0/1 KNAPSACK - DYNAMIC PROGRAMMING
void knapsack01() {
    int budget;
    cout << "\nEnter your budget: ";
    cin >> budget;

    if (budget < 0) {
        cout << "Invalid budget!\n";
        return;
    }

    int n = offers.size();

    vector<vector<int>> dp(n + 1,
        vector<int>(budget + 1, 0));

    for (int i = 1; i <= n; i++) {
        for (int w = 0; w <= budget; w++) {
            dp[i][w] = dp[i - 1][w];

            if (offers[i - 1].price <= w) {
                dp[i][w] = max(dp[i][w],
                    offers[i - 1].benefit +
                    dp[i - 1][w - offers[i - 1].price]);
            }
        }
    }

    cout << "Maximum Benefit: " << dp[n][budget] << endl;
    cout << "Selected Offers:\n";

    int w = budget;

    for (int i = n; i > 0; i--) {
        if (dp[i][w] != dp[i - 1][w]) {
            cout << offers[i - 1].name
                 << " - " << offers[i - 1].price << " Taka\n";

            w -= offers[i - 1].price;
        }
    }
}

// 4. LCS - LONGEST COMMON SUBSEQUENCE
void lcs() {
    cout << "\nAvailable Offers:\n";

    for (int i = 0; i < offers.size(); i++)
        cout << i + 1 << ". " << offers[i].name << endl;

    int first, second;

    cout << "Select first offer: ";
    cin >> first;

    cout << "Select second offer: ";
    cin >> second;

    if (first < 1 || first > offers.size() ||
        second < 1 || second > offers.size()) {
        cout << "Invalid selection!\n";
        return;
    }

    vector<string> a = offers[first - 1].features;
    vector<string> b = offers[second - 1].features;

    int m = a.size(), n = b.size();

    vector<vector<int>> dp(m + 1,
        vector<int>(n + 1, 0));

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (a[i - 1] == b[j - 1])
                dp[i][j] = 1 + dp[i - 1][j - 1];
            else
                dp[i][j] = max(dp[i - 1][j],
                               dp[i][j - 1]);
        }
    }

    vector<string> result;
    int i = m, j = n;

    while (i > 0 && j > 0) {
        if (a[i - 1] == b[j - 1]) {
            result.push_back(a[i - 1]);
            i--;
            j--;
        }
        else if (dp[i - 1][j] >= dp[i][j - 1])
            i--;
        else
            j--;
    }

    reverse(result.begin(), result.end());

    cout << "\nCommon Features:\n";
    for (string x : result)
        cout << x << endl;

    cout << "LCS Length: " << dp[m][n] << endl;
}

// MAIN FUNCTION
int main() {
    int choice;

    do {
        cout << "\n===== SMART MOBILE RECHARGE & OFFER PACK =====\n";
        cout << "1. Coin Change\n";
        cout << "2. Fractional Knapsack\n";
        cout << "3. 0/1 Knapsack\n";
        cout << "4. LCS\n";
        cout << "5. Exit\n";

        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: coinChange(); break;
            case 2: fractionalKnapsack(); break;
            case 3: knapsack01(); break;
            case 4: lcs(); break;
            case 5: break;
            default: cout << "Invalid choice!\n";
        }

    } while (choice != 5);

    return 0;
}
